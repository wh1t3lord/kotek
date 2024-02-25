#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_std_string.h>
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <filesystem>
#else
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 260
	#define KOTEK_DEF_OS_PATH_SEPARATOR "\\"
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
	#define KOTEK_DEF_OS_PATH_SEPARATOR "/"
#elif defined(KOTEK_USE_PLATFORM_MAC)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
	#define KOTEK_DEF_OS_PATH_SEPARATOR "/"
#else
	#error undefined platform
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <size_t Size>
class static_path
{
public:
	static_path();
	~static_path();

private:

};
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK