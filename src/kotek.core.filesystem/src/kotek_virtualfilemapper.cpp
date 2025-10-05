#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileSystem_VFM::ktkFileSystem_VFM(void)
{
	// todo: for dyn and hyb KOTEK_USE_LIBRARY_TYPE you need to call resize
	// because we need to use lookup approach for accessing data from m_mappings

#if defined(KOTEK_USE_LIBRARY_TYPE_DYN) || defined(KOTEK_USE_LIBRARY_TYPE_HYB)
	#error provide implementation for dynamic and hybrid containers, see todo above
#endif
}

ktkFileSystem_VFM::~ktkFileSystem_VFM(void) {}

void ktkFileSystem_VFM::Initialize() {}

void ktkFileSystem_VFM::Shutdown()
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS

	for (auto& handle : this->m_mappings)
	{
		KOTEK_ASSERT(handle.p_fmh,
			"must be valid otherwise it means that you didn't update data "
			"properly from this cache (m_mappings)");
		KOTEK_ASSERT(handle.p_data,
			"must be valid otherwise virtual file mapping doesn't support on "
			"Windows NT OS. Check the hardware requirements of WinAPI "
			"callings...");

		if (handle.p_data)
		{
	#ifdef KOTEK_DEBUG
			char buf[32];
			constexpr unsigned char _kBufSize = sizeof(buf) / sizeof(buf[0]);
			std::memcpy(buf, handle.p_data,
				std::min(handle.file_size,
					static_cast<decltype(handle.file_size)>(_kBufSize)));

			KOTEK_MESSAGE("unmapped file: {} ...", buf);
	#endif
			UnmapViewOfFile(handle.p_data);
		}

		if (handle.p_fmh)
		{
			CloseHandle(handle.p_fmh);
		}
	}

	this->m_mappings.clear();
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

	#ifdef KOTEK_DEBUG
	ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH> szPathToFile;

	DWORD dwRet = GetFinalPathNameByHandleA(hFile, szPathToFile.begin(),
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH, FILE_NAME_NORMALIZED);

	KOTEK_ASSERT(dwRet > 0 && dwRet < KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"failed to obtain file path from file handle!");

	KOTEK_ASSERT(hMap != INVALID_HANDLE_VALUE && hMap != nullptr,
		"failed to CreateFileMapping for {}", szPathToFile);
	#else
	KOTEK_ASSERT(hMap != INVALID_HANDLE_VALUE && hMap != nullptr,
		"failed to CreateFileMapping!");
	#endif

	if (hMap == INVALID_HANDLE_VALUE || !hMap)
	{
		KOTEK_MESSAGE_WARNING(
			"CreateFileMapping = last error: {}", GetLastError());
		return status;
	}

	void* pMapped = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

	KOTEK_ASSERT(pMapped, "failed to map the file!");

	if (!pMapped)
	{
		KOTEK_MESSAGE_WARNING("MapViewOfFile = last error: {}", GetLastError());
		return status;
	}

	// we try to use free ids and then if there's no any available we do insert
	// to mappings for dynamic and hybrid (if hybrid supports reallocation) will
	// create new memory, but if you don't want to it is preferably to use
	// static or hybrid without reallocation due to fact of physical persistent
	// preallocated memory and lookup accessing
	if (this->m_free_ids.empty())
	{
		vfm_handle_t data;

		data.p_data = pMapped;
		data.p_fmh = hMap;
		data.file_size = liFileSize.QuadPart;

		this->m_mappings.emplace_back(std::move(data));
	}
	else
	{
		id_type free_id = this->m_free_ids.back();

		vfm_handle_t& data = this->m_mappings[free_id];

		data.p_data = pMapped;
		data.p_fmh = hMap;
		data.file_size = liFileSize.QuadPart;

		this->m_free_ids.pop();
	}

	status = static_cast<id_type>(this->m_mappings.size() - 1);

	return status;
#else
	#error unknown platform
#endif
}

void ktkFileSystem_VFM::UnMapFile(id_type file_id)
{
	KOTEK_ASSERT(file_id < this->m_mappings.max_size(), "out of range!");

	if (file_id < this->m_mappings.max_size())
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		vfm_handle_t& data = this->m_mappings[file_id];

		KOTEK_ASSERT(data.p_data, "must be valid!");
		KOTEK_ASSERT(data.p_fmh, "must be valid!");

		if (data.p_data)
		{
			BOOL nStatusUnmapViewOfFile = UnmapViewOfFile(data.p_data);
			KOTEK_ASSERT(nStatusUnmapViewOfFile != 0,
				"UnmapViewOfFile = last error: {}", GetLastError());
		}

		if (data.p_fmh)
		{
			BOOL nStatusCloseHandle = CloseHandle(data.p_fmh);
			KOTEK_ASSERT(nStatusCloseHandle != 0,
				"CloseHandle = last error: {}", GetLastError());
		}

	#if defined(KOTEK_USE_LIBRARY_TYPE_EMB)
		this->m_mappings.erase(this->m_mappings.begin() + file_id);
	#else
			// todo: we don't need to call erase, but technically we can handle
			// hybrid containers as emb but after exceeding preallocated size we
			// need to manually 'invalidate' data without clearing memory

			// why we don't need to erase? Because we want to keep memory low as
			// possible but without loosing pure O(1) by speed accessing because
			// unoredered_map is slow compared to lookup, it makes things easier
			// but def not faster

		#error provide implementation, see todo
	#endif

		this->m_free_ids.push(file_id);

	#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("unmapped file: {}", file_id);
	#endif

#else
	#error unknown platform
#endif
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK