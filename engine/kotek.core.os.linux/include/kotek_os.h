#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.render/include/kotek_core_defines_render.h>

#ifdef KOTEK_PLATFORM_LINUX
	#define VK_USE_PLATFORM_XLIB_KHR
	#define VK_USE_PLATFORM_XCB_KHR
	#include <vulkan/vulkan.h>

	#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
		#include <GLFW/glfw3.h>

		#define GLFW_EXPOSE_NATIVE_X11
		#include <GLFW/glfw3native.h>
	#endif

	#undef None
	#undef Always
#endif
