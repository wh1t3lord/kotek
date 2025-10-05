#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileSystem_VFM::ktkFileSystem_VFM(void) {}

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

kun_ktk uint32_t ktkFileSystem_VFM::MapFile(FILE* p_file)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	kun_ktk uint32_t status = decltype(status)(-1);

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

	vfm_handle_t data;

	data.p_data = pMapped;
	data.p_fmh = hMap;
	data.file_size = liFileSize.QuadPart;

	this->m_mappings.emplace_back(std::move(data));

	status = this->m_mappings.size() - 1;

	return status;
#else
	#error unknown platform
#endif
}

void ktkFileSystem_VFM::UnMapFile(kun_ktk uint32_t file_id)
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

		this->m_mappings.erase(this->m_mappings.begin() + file_id);

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