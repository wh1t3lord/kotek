#include "../include/kotek_virtualfilemapper.h"

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	// _get_osfhandle / _fileno: this TU always relied on a transitive
	// include (it rode in on spdlog's headers; kotek's own CUSTOM logging
	// backend removed that accident — own the include)
	#include <io.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileSystem_VFM::ktkFileSystem_VFM(void)
{
	// todo: for dyn and hyb KOTEK_USE_LIBRARY_TYPE you need to call resize
	// because we need to use lookup approach for accessing data from m_mappings

	// HYB takes the EMB path: the container API (emplace_back/operator[]/
	// erase/push/pop) that the hybrid vector/queue provide is used
	// unchanged; the lookup redesign in the todo above stays open for the
	// owner, DYN remains unimplemented
#if defined(KOTEK_USE_LIBRARY_TYPE_DYN)
	#error provide implementation for dynamic containers, see todo above
#endif
}

ktkFileSystem_VFM::~ktkFileSystem_VFM(void) {}

void ktkFileSystem_VFM::Initialize() {}

void ktkFileSystem_VFM::Shutdown()
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS

	// unmap everything still live; free slots carry p_data == nullptr
	// (with the B1 map→copy→unmap contract nothing should outlive its
	// read — a nonzero remainder here means a leaked UnMapFile)
	for (id_type i = 0; i < static_cast<id_type>(this->m_mappings.size());
	     ++i)
	{
		if (this->m_mappings[i].p_data)
		{
			this->UnMapFile(i);
		}
	}

	this->m_mappings.clear();

	while (this->m_free_ids.empty() == false)
	{
		this->m_free_ids.pop();
	}

	KOTEK_MESSAGE(
		"vfm shutdown: {} mapped, {} unmapped", this->m_stat_map_count,
		this->m_stat_unmap_count);
#else
	#error unknown platform
#endif
}

ktkFileSystem_VFM::id_type ktkFileSystem_VFM::MapFile(FILE* p_file)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	id_type status = id_type(-1);

	if (p_file == nullptr)
		return status;

	KOTEK_ASSERT(p_file, "must be valid");

	int fd = _fileno(p_file);
	KOTEK_ASSERT(fd != -1, "failed to get file descriptor!");

	if (fd == -1)
	{
		KOTEK_MESSAGE_WARNING("_fileno = last error: {}", GetLastError());
		return status;
	}

	HANDLE hFile = reinterpret_cast<HANDLE>(_get_osfhandle(fd));

	KOTEK_ASSERT(hFile != INVALID_HANDLE_VALUE && hFile != nullptr,
		"failed to get file handle");

	if (hFile == INVALID_HANDLE_VALUE || !hFile)
	{
		KOTEK_MESSAGE_WARNING(
			"_get_osfhandle = last error: {}", GetLastError());
		return status;
	}

	LARGE_INTEGER liFileSize;
	BOOL nStatusGetFileSizeEx = GetFileSizeEx(hFile, &liFileSize);

	KOTEK_ASSERT(nStatusGetFileSizeEx != 0, "failed to obtain file size!");

	if (nStatusGetFileSizeEx == 0)
	{
		KOTEK_MESSAGE_WARNING("GetFileSizeEx = last error: {}", GetLastError());
		return status;
	}

	HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY,
		liFileSize.HighPart, liFileSize.LowPart, NULL);

	if (hMap == INVALID_HANDLE_VALUE || !hMap)
	{
		// an existing file that can't be mapped is user data (B1
		// contract) — warn and let the caller degrade to the CRT read,
		// never a hard error (a 0-byte file also lands here on Win32:
		// MapFileForRead detects that case BEFORE calling us, so this
		// branch means a genuine mapping failure)
		KOTEK_MESSAGE_WARNING(
			"CreateFileMapping = last error: {}", GetLastError());
		return status;
	}

	#ifdef KOTEK_DEBUG
	ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH> szPathToFile;

	DWORD dwRet = GetFinalPathNameByHandleA(hFile, szPathToFile.data(),
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH, FILE_NAME_NORMALIZED);

	KOTEK_ASSERT(dwRet > 0 && dwRet < KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"failed to obtain file path from file handle!");
	#endif

	void* pMapped = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

	if (!pMapped)
	{
		// same user-data contract as the CreateFileMapping branch
		// above — the mapping handle must not leak on the way out
		KOTEK_MESSAGE_WARNING("MapViewOfFile = last error: {}", GetLastError());
		CloseHandle(hMap);
		return status;
	}

	// we try to use free ids and then if there's no any available we do insert
	// to mappings for dynamic and hybrid (if hybrid supports reallocation) will
	// create new memory, but if you don't want to it is preferably to use
	// static or hybrid without reallocation due to fact of physical persistent
	// preallocated memory and lookup accessing
	id_type result_id;

	if (this->m_free_ids.empty())
	{
		vfm_handle_t data;

		data.p_data = pMapped;
		data.p_fmh = hMap;
		data.file_size = liFileSize.QuadPart;

		this->m_mappings.emplace_back(std::move(data));

		result_id = static_cast<id_type>(this->m_mappings.size() - 1);
	}
	else
	{
		// slot reuse fills the popped id's OLD slot: UnMapFile marks
		// slots free instead of erasing, so positions never shift under
		// a live id (the pre-B1 code returned size()-1 here — wrong
		// whenever a reused slot wasn't the last one)
		result_id = this->m_free_ids.front();
		this->m_free_ids.pop();

		vfm_handle_t& data = this->m_mappings[result_id];

		data.p_data = pMapped;
		data.p_fmh = hMap;
		data.file_size = liFileSize.QuadPart;
	}

	++this->m_stat_map_count;

	status = result_id;

	return status;
#else
	#error unknown platform
#endif
}

void ktkFileSystem_VFM::UnMapFile(id_type file_id)
{
	KOTEK_ASSERT(file_id < this->m_mappings.size(), "out of range!");

	if (file_id < this->m_mappings.size())
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		vfm_handle_t& data = this->m_mappings[file_id];

		if (data.p_data == nullptr)
		{
			// a free slot being unmapped again is a caller logic slip,
			// not user data
			KOTEK_ASSERT(false, "double unmap of vfm id={}", file_id);
			return;
		}

		BOOL nStatusUnmapViewOfFile = UnmapViewOfFile(data.p_data);
		KOTEK_ASSERT(nStatusUnmapViewOfFile != 0,
			"UnmapViewOfFile = last error: {}", GetLastError());

		if (data.p_fmh)
		{
			BOOL nStatusCloseHandle = CloseHandle(data.p_fmh);
			KOTEK_ASSERT(nStatusCloseHandle != 0,
				"CloseHandle = last error: {}", GetLastError());
		}

		// mark the slot free — NO erase: positions of the other live
		// ids must stay stable under ids already handed out
		data.p_data = nullptr;
		data.p_fmh = HANDLE(0);
		data.file_size = 0;

		this->m_free_ids.push(file_id);

		++this->m_stat_unmap_count;
#else
	#error unknown platform
#endif
	}
}

eVFMMapFileResult ktkFileSystem_VFM::MapFileForRead(
	const ktk_filesystem_path& absolute_path, id_type& out_mapping_id,
	kun_ktk size_t& out_file_size)
{
	out_mapping_id = id_type(-1);
	out_file_size = 0;

	KOTEK_ASSERT(
		absolute_path.empty() == false, "you can't pass empty path!");

	if (absolute_path.empty())
	{
		return eVFMMapFileResult::kMissingFile;
	}

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	FILE* p_file = fopen(absolute_path.c_str(), "rb");

	if (p_file == nullptr)
	{
		// user data, not a programmer error — the ONE warning for this
		// miss; the caller must not re-warn through the CRT fallback
		KOTEK_MESSAGE_WARNING(
			"failed to open file for reading: {} (GetLastError={})",
			absolute_path, GetLastError());
		return eVFMMapFileResult::kMissingFile;
	}

	// a 0-byte file can't be mapped on Win32 (CreateFileMapping rejects
	// size 0) — detect it explicitly and report a successful empty read
	// instead of a misleading mapping failure
	auto status_fseek = fseek(p_file, 0, SEEK_END);
	long file_size_signed = ftell(p_file);

	if (status_fseek != 0 || file_size_signed < 0)
	{
		KOTEK_MESSAGE_WARNING(
			"failed to query size of file for mapping: {} "
			"(GetLastError={})",
			absolute_path, GetLastError());
		fclose(p_file);
		return eVFMMapFileResult::kMappingFailed;
	}

	if (file_size_signed == 0)
	{
		fclose(p_file);
		return eVFMMapFileResult::kEmptyFile;
	}

	id_type mapping_id = this->MapFile(p_file);

	// the view survives closing the CRT handle (the mapping keeps the
	// file alive) — no FILE* is retained
	fclose(p_file);

	if (mapping_id == id_type(-1))
	{
		// MapFile already warned with the GetLastError details — the
		// caller degrades to the CRT read
		return eVFMMapFileResult::kMappingFailed;
	}

	out_mapping_id = mapping_id;
	out_file_size = this->m_mappings[mapping_id].file_size;

	return eVFMMapFileResult::kSuccess;
#else
	#error unknown platform
#endif
}

const void* ktkFileSystem_VFM::Get_MappedData(id_type file_id) const
{
	KOTEK_ASSERT(file_id < this->m_mappings.size(), "out of range!");

	if (file_id < this->m_mappings.size())
	{
		return this->m_mappings[file_id].p_data;
	}

	return nullptr;
}

kun_ktk size_t ktkFileSystem_VFM::Get_MappedSize(id_type file_id) const
{
	KOTEK_ASSERT(file_id < this->m_mappings.size(), "out of range!");

	if (file_id < this->m_mappings.size())
	{
		return this->m_mappings[file_id].file_size;
	}

	return 0;
}

kun_ktk uint32_t ktkFileSystem_VFM::Get_StatMapCount(void) const noexcept
{
	return this->m_stat_map_count;
}

kun_ktk uint32_t ktkFileSystem_VFM::Get_StatUnmapCount(void) const noexcept
{
	return this->m_stat_unmap_count;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
