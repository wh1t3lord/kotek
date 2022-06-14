#pragma once

#include <kotek.core/include/kotek_core.h>

#pragma region UI

#pragma region ImGui
#include <kotek.ui.imgui/include/imgui.h>
#include <kotek.ui.imgui/include/imgui_impl_opengl3.h>
#include <kotek.ui.imgui/include/imgui_impl_vulkan.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_USE_DIRECTX
		#if (KOTEK_USE_DIRECTX_VERSION > 11)
			#include <kotek.ui.imgui/include/imgui_impl_dx12.h>
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 10)
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 9)
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 8)
			#include <kotek.ui.imgui/include/imgui_impl_dx9.h>
		#endif
	#endif

	#include <kotek.ui.imgui/include/imgui_impl_win32.h>
#endif

#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	#include <kotek.ui.imgui/include/imgui_impl_glfw.h>
#else
// TODO: imgui doesn't have any native support for linux and other system, be
// careful here
#endif

#pragma endregion

#pragma endregion