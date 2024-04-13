#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.render/include/kotek_core_defines_render.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#include <ShellScalingApi.h>
	#include <dwmapi.h>
	#include <windows.h>
	#include <commdlg.h>
	#include <Shlwapi.h>
	#include <winioctl.h>

	#ifdef KOTEK_USE_VULKAN
		#define VK_USE_PLATFORM_WIN32_KHR
		#include <vulkan/vulkan.h>
	#endif

	#ifdef KOTEK_USE_DIRECTX
		#ifdef KOTEK_DEBUG
			#include <dxgidebug.h>
		#else
			#include <dxgi.h>
		#endif

		#include <d3dcompiler.h>

		#if (KOTEK_USE_DIRECTX_VERSION > 11)
			#include <d3d12.h>
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 10)
			#include <d3d11_4.h>
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 9)
			#include <d3d10.h>
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 8)
			#include <d3d9.h>
		#endif
	#endif

	#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
		#define GLFW_INCLUDE_NONE
		#include <GLFW/glfw3.h>

		#define GLFW_EXPOSE_NATIVE_WIN32
		#include <GLFW/glfw3native.h>
	#endif

	#ifdef KOTEK_USE_OPENGL
	// glad uses only in private form, like you initialize in appropriate
	// kotek.render.glx.x version
	#endif
#endif