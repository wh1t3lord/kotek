#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.render/include/kotek_core_defines_render.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH

#include "imgui.h"

#ifdef KOTEK_USE_OPENGL
	#if (KOTEK_USE_OPENGL_MODERN_VERSION > 1)
		#include "imgui_impl_opengl2.h"
	#endif

	#if (KOTEK_USE_OPENGL_MODERN_VERSION > 2)
		#include "imgui_impl_opengl3.h"
	#endif

	#if (KOTEK_USE_OPENGL_MODERN_VERSION > 3)

	#endif

#endif

#ifdef KOTEK_USE_VULKAN
	#include "imgui_impl_vulkan.h"
#endif

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_USE_DIRECTX
		#if (KOTEK_USE_DIRECTX_VERSION > 11)
			#include "imgui_impl_dx12.h"
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 10)
			#include "imgui_impl_dx11.h"
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 9)
			#include "imgui_impl_dx10.h"
		#endif

		#if (KOTEK_USE_DIRECTX_VERSION > 8)
			#include "imgui_impl_dx9.h"
		#endif
	#endif

	#include "imgui_impl_win32.h"
#endif

// TODO: add for SDL
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	#include "imgui_impl_glfw.h"
#elif defined(KOTEK_USE_WINDOW_LIBRARY_WIN32)
	// the own Win32 window backend (task K17) pairs with imgui's official
	// win32 platform binding (already included above for the DX paths;
	// its include guard makes this a no-op then)
	#include "imgui_impl_win32.h"
#else
	#error "unsupported window library for the imgui platform backend (GLFW and WIN32 are implemented)"
	// TODO: imgui does not have any native support for linux and other
	// systems, be careful here
#endif

KOTEK_CPP_DISABLE_ALL_WARNINGS_POP

#include "kotek_ui_imgui_wrapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI_IMGUI(Core::ktkMainManager*);
bool ShutdownModule_UI_IMGUI(Core::ktkMainManager*);
bool SerializeModule_UI_IMGUI(Core::ktkMainManager*);
bool DeserializeModule_UI_IMGUI(Core::ktkMainManager*);

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
