#include "../include/kotek_std_alias_filesystem.h"

#include <kotek.core.os/include/kotek_core_os.h>

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#pragma comment(lib, "shlwapi.lib")
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

// todo: add preprocessors for hybrid containers
#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
KOTEK_BEGIN_NAMESPACE_FILESYSTEM
ktk_filesystem_path current_path()
{
	#ifdef KOTEK_USE_PLATFORM_WINDOWS
	char buffer[MAX_PATH]{};

	GetCurrentDirectoryA(MAX_PATH, buffer);

	return buffer;
	#elif defined(KOTEK_USE_PLATFORM_LINUX)
		#error todo: implement
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
		#error todo: implement
	#else
		#error unknown platform
	#endif
}

bool exists(const ktk_filesystem_path& path)
{
	bool result{};

	if (path.empty())
		return result;

	#ifdef KOTEK_USE_PLATFORM_WINDOWS

	auto status = PathFileExistsA(path.c_str());

	if (status == TRUE)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	#elif defined(KOTEK_USE_PLATFORM_LINUX)
		#error todo: implement
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
		#error todo: implement
	#else
		#error unknown platform
	#endif

	return result;
}

bool create_directory(const ktk_filesystem_path& path)
{
	bool result{};

	if (path.empty())
		return result;

	auto status = CreateDirectoryA(path.c_str(), NULL);

	if (status == TRUE)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

bool remove(const ktk_filesystem_path& path)
{
	bool result{};

	#ifdef KOTEK_USE_PLATFORM_WINDOWS
	auto cstr = path.c_str();
	DWORD attr = GetFileAttributesA(cstr);
	bool is_valid{true};
	if (attr == INVALID_FILE_ATTRIBUTES)
	{
		auto error = ::GetLastError();
		if (error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND)
		{
			is_valid = false;
		}
	}
	else if (attr & FILE_ATTRIBUTE_READONLY)
	{
		auto new_attr = attr & ~static_cast<DWORD>(FILE_ATTRIBUTE_READONLY);
		if (!SetFileAttributesA(cstr, new_attr))
		{
			is_valid = false;
		}
	}
	if (is_valid)
	{
		if (attr & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!RemoveDirectoryA(cstr))
			{
				result = true;
			}
		}
		else
		{
			if (!DeleteFileA(cstr))
			{
				result = true;
			}
		}
	}
	#elif defined(KOTEK_USE_PLATFORM_LINUX)
		#error todo: implement
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
		#error todo: implement
	#else
		#error unknown platform
	#endif

	return result;
}
KOTEK_END_NAMESPACE_FILESYSTEM
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK