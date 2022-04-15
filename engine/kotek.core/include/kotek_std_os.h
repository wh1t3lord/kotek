#pragma once

#include "kotek_std_preprocessors.h"

#ifdef KOTEK_PLATFORM_WINDOWS
	#define VK_USE_PLATFORM_WIN32_KHR
#elif KOTEK_PLATFORM_LINUX
	#define VK_USE_PLATFORM_XLIB_KHR
	#define VK_USE_PLATFORM_XCB_KHR
#endif

#include <vulkan/vulkan.h>

#ifdef KOTEK_PLATFORM_WINDOWS

	#ifdef KOTEK_DEBUG
		#include <DXGIDebug.h>
	#endif

	#include <D3Dcompiler.h>
	#include <d3d12.h>
	#include <dxgi1_4.h>
#elif defined(KOTEK_PLATFORM_LINUX)
#endif

#include <kotek.engine.window/include/kotek_engine_window_impl.h>

// TODO: think about choosing glad through cmake argument like OpenGL=3 or OpenGL=4
#include "../glad3/glad.h"

#pragma region GLFW

#include <GLFW/glfw3.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include <GLFW/glfw3native.h>
#elif KOTEK_PLATFORM_LINUX
	#define GLFW_EXPOSE_NATIVE_X11
	#include <GLFW/glfw3native.h>
#endif

#pragma endregion

#include <oneapi/tbb.h>
