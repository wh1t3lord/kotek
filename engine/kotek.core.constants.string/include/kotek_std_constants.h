#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_PLATFORM_WINDOWS
		constexpr tchar kPathSeparator = KOTEK_TEXT('\\');
#else
		constexpr tchar kPathSeparator = KOTEK_TEXT('/');
#endif

		constexpr const tchar* kRenderer_OpenGL3_3_Name =
			KOTEK_TEXT("OpenGL 3.3");
		constexpr const tchar* kRenderer_OpenGL4_6_Name =
			KOTEK_TEXT("OpenGL 4.6");

		constexpr const tchar* kRenderer_DirectX_7_Name =
			KOTEK_TEXT("DirectX 7");
		constexpr const tchar* kRenderer_DirectX_8_Name =
			KOTEK_TEXT("DirectX 8");
		constexpr const tchar* kRenderer_DirectX_9_Name =
			KOTEK_TEXT("DirectX 9");
		constexpr const tchar* kRenderer_DirectX_10_Name =
			KOTEK_TEXT("DirectX 10");
		constexpr const tchar* kRenderer_DirectX_11_Name =
			KOTEK_TEXT("DirectX 11");
		constexpr const tchar* kRenderer_DirectX_12_Name =
			KOTEK_TEXT("DirectX 12");

		constexpr const tchar* kRenderer_Vulkan_Name = KOTEK_TEXT("Vulkan");
	} // namespace ktk
} // namespace Kotek