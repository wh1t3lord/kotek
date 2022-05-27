#pragma once

#ifdef KOTEK_USE_UNICODE

	#ifdef KOTEK_PLATFORM_WINDOWS

		#define KOTEK_TEXT(x) L##x

	#elif defined(KOTEK_PLATFORM_LINUX)

		#define KOTEK_TEXT(x) U##x

	#endif

#else

	#define KOTEK_TEXT(x) x

#endif