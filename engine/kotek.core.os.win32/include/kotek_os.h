#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#include <ShellScalingApi.h>
	#include <dwmapi.h>
	#include <windows.h>

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
		#include <GLFW/glfw3.h>
	#endif
#endif