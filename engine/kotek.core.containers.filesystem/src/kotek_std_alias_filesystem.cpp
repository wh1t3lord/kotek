#include "../include/kotek_std_alias_filesystem.h"

#include <kotek.core.os/include/kotek_core_os.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
namespace filesystem
{
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
} // namespace filesystem
#endif
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK