#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

#ifdef KOTEK_USE_UNICODE

	#ifdef KOTEK_PLATFORM_WINDOWS

		#define KOTEK_TEXT(x) L##x

	#elif defined(KOTEK_PLATFORM_LINUX)

		#define KOTEK_TEXT(x) U##x

	#endif

#else

	#define KOTEK_TEXT(x) x

#endif