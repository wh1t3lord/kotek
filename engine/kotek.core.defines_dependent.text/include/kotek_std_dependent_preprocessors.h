#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

#ifdef KOTEK_USE_UNICODE
    #define KOTEK_TEXT(x) reinterpret_cast<const char*>(u8##x)
    #define KOTEK_T(x) u8##x
#else
    #define KOTEK_T(x) x
	#define KOTEK_TEXT(x) x
#endif
