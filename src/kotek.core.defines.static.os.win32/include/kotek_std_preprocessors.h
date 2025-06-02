#pragma once

	#if defined(_WIN32) || defined(_WIN64)
                #define KOTEK_USE_PLATFORM_WINDOWS
		#define WIN32_LEAN_AND_MEAN

		#ifdef KOTEK_WINDOW_LIBRARY_GLFW
			#define KOTEK_USE_WINDOW_LIBRARY_GLFW
		#endif

		#ifdef KOTEK_WINDOW_LIBRARY_SDL
			#define KOTEK_USE_WINDOW_LIBRARY_SDL
			#error TODO connect sdl to project and add switching between libraries
		#endif

		#define KOTEK_WINDOW_LIBRARY_NAME GLFW
		#define VK_USE_PLATFORM_WIN32_KHR
	#endif
	