#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_std_string.h>
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <filesystem>
#else
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS
// todo: provide overriding through cmake this length
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
	// todo: provide support of switching strings what user wants
	static_cstring<Size> m_buffer;
};
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_filesystem_path                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
	#define ktkFileSystemPath                             \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
	#define KTK_FILESYSTEM_PATH                           \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK \
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>
#else
	#define ktk_array \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK filesystem::path
	#define ktkFileSystemPath \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK filesystem::path
	#define KTK_FILESYSTEM_PATH \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK filesystem::path
#endif