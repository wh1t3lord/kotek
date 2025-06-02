#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

#ifdef KOTEK_USE_UNICODE
	#define KOTEK_TEXT(x) reinterpret_cast<const char*>(u8##x)

	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
		#define KOTEK_T(x) u8##x
	#else
		#if KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER == 1
			#define KOTEK_T(x) x
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER == 8
			#define KOTEK_T(x) u8##x
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER == 16
			#define KOTEK_T(x) u##x
		#elif KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE_AS_NUMBER == 32
			#define KOTEK_T(x) U##x
		#endif
	#endif

	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
		#define KOTEK_TEXTU(x) KOTEK_TEXT(x)
	#else
		#define KOTEK_TEXTU(x) KOTEK_T(x)
	#endif
#else
	#define KOTEK_T(x) x
	#define KOTEK_TEXT(x) x
	#define KOTEK_TEXTU(x) x
#endif
