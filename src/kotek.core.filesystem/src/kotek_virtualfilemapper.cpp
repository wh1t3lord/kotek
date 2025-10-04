#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkFileSystem_VFM::ktkFileSystem_VFM(void) {}

ktkFileSystem_VFM::~ktkFileSystem_VFM(void) {}

void ktkFileSystem_VFM::Initialize() {}

void ktkFileSystem_VFM::Shutdown()
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	for (auto& pair : this->m_mappings)
	{
		auto& handle = pair.second;

		KOTEK_ASSERT(handle.p_fmh,
			"must be valid otherwise it means that you didn't update data "
			"properly from this cache (m_mappings)");
		KOTEK_ASSERT(handle.p_data,
			"must be valid otherwise virtual file mapping doesn't support on "
			"Windows NT OS. Check the hardware requirements of WinAPI "
			"callings...");

		if (handle.p_data)
		{
			UnmapViewOfFile(handle.p_data);
		}

		if (handle.p_fmh)
		{
			CloseHandle(handle.p_fmh);
		}

	#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("unmapped file: {}", pair.first);
	#endif
	}

	this->m_mappings.clear();
#else
	#error unknown platform
#endif
}

bool ktkFileSystem_VFM::MapFile(ktkFileHandleType file_id,
	kun_ktk fstream& file, const ktk_cstring_view& path_to_file)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	bool status = false;

	if (this->m_mappings.find(path_to_file.data()) != this->m_mappings.end())
		return status;

	KOTEK_ASSERT(
		path_to_file.empty() == false, "don't pass empty pathes, can't be!");

	int fd = _fileno(reinterpret_cast<FILE*>(file.rdbuf()));
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

	KOTEK_ASSERT(hMap != INVALID_HANDLE_VALUE && hMap != nullptr,
		"failed to CreateFileMapping for {}", path_to_file);

	if (hMap == INVALID_HANDLE_VALUE || !hMap)
	{
		KOTEK_MESSAGE_WARNING(
			"CreateFileMapping = last error: {}", GetLastError());
		return status;
	}

	void* pMapped = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

	KOTEK_ASSERT(pMapped, "failed to map the file {}!", path_to_file);

	if (!pMapped)
	{
		KOTEK_MESSAGE_WARNING("MapViewOfFile = last error: {}", GetLastError());
		return status;
	}

	vfm_handle_t& data = this->m_mappings[path_to_file.data()];

	data.file_id = file_id;
	data.p_data = pMapped;
	data.p_fmh = hMap;
	status = true;

	return status;
#else
	#error unknown platform
#endif
}

void ktkFileSystem_VFM::UnMapFile(const ktk_cstring_view& path_to_file)
{
	if (this->m_mappings.find(path_to_file.data()) != this->m_mappings.end())
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		vfm_handle_t& data = this->m_mappings[path_to_file.data()];

		KOTEK_ASSERT(data.p_data, "must be valid!");
		KOTEK_ASSERT(data.p_fmh, "must be valid!");

		if (data.p_data)
		{
			UnmapViewOfFile(data.p_data);
		}

		if (data.p_fmh)
		{
			CloseHandle(data.p_fmh);
		}

		this->m_mappings.erase(path_to_file.data());

	#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("unmapped file: {}", path_to_file);
	#endif

#else
	#error unknown platform
#endif
	}
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK