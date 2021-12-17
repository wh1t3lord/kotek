#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define KOTEK_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
#elif __linux__
	#define KOTEK_PLATFORM_LINUX
#endif

#ifdef KOTEK_UNICODE
	#define KOTEK_USE_UNICODE
#endif

#ifdef KOTEK_SDK
	#define KOTEK_USE_SDK
#endif

#ifdef KOTEK_TESTS
	#define KOTEK_USE_TESTS
#endif

#ifdef KOTEK_TESTS_RUNTIME
	#define KOTEK_USE_TESTS_RUNTIME
#endif

#ifdef KOTEK_CPU_PROFILER
	#define KOTEK_USE_CPU_PROFILER
#endif

#ifdef KOTEK_GPU_PROFILER
	#define KOTEK_USE_GPU_PROFILER
#endif

#ifdef KOTEK_MATH_LIBRARY_GLM
	#define KOTEK_USE_MATH_LIBRARY_GLM
#endif

#ifdef KOTEK_USE_UNICODE

	#ifdef KOTEK_PLATFORM_WINDOWS

		#define KOTEK_TEXT(x) L##x

	#elif defined(KOTEK_PLATFORM_LINUX)

		#define KOTEK_TEXT(x) U##x

	#endif

#else

	#define KOTEK_TEXT(x) x

#endif