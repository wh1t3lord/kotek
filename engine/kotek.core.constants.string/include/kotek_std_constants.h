#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>

/**
 * 
 */
namespace Kotek
{
	/**
	 * Use these path's separator only if you don't use boost or std otherwise
	 * use std::filesystem::path::preferred_separator
	 */
#ifdef KOTEK_PLATFORM_WINDOWS
	constexpr ktk::tchar kPathSeparator = KOTEK_TEXT('\\');
#else
	constexpr tchar kPathSeparator = KOTEK_TEXT('/');
#endif

	/**
	 * Constant expresses in string that it is OpenGL version 3.3
	 */
	constexpr const ktk::tchar* kRenderer_OpenGL3_3_Name =
		KOTEK_TEXT("OpenGL 3.3");

	/**
	 * Constant expresses in string that it is OpenGL version 2.0
	 */
	constexpr const ktk::tchar* kRenderer_OpenGL2_0_Name =
		KOTEK_TEXT("OpenGL 2.0");

	/**
	 * Constant expresses in string that it is OpenGL version 4.6
	 */
	constexpr const ktk::tchar* kRenderer_OpenGL4_6_Name =
		KOTEK_TEXT("OpenGL 4.6");

	/**
	 * Constant expresses in string that it is DirectX 7
	 */
	constexpr const ktk::tchar* kRenderer_DirectX_7_Name =
		KOTEK_TEXT("DirectX 7");

	/**
	 * Constant expresses in string that it is DirectX 8
	 */
	constexpr const ktk::tchar* kRenderer_DirectX_8_Name =
		KOTEK_TEXT("DirectX 8");

	/**
	 * Constant expresses in string that it is DirectX 9
	 */
	constexpr const ktk::tchar* kRenderer_DirectX_9_Name =
		KOTEK_TEXT("DirectX 9");

	/**
	 * Constant expresses in string that it is DirectX 10
	 */
	constexpr const ktk::tchar* kRenderer_DirectX_10_Name =
		KOTEK_TEXT("DirectX 10");

	/**
	 * Constant expresses in string that it is DirectX 11
	 */
	constexpr const ktk::tchar* kRenderer_DirectX_11_Name =
		KOTEK_TEXT("DirectX 11");

	/**
	 * Constant expresses in string that it is DirectX 12
	 */
	constexpr const ktk::tchar* kRenderer_DirectX_12_Name =
		KOTEK_TEXT("DirectX 12");

	/**
	 * Constant expresses in string that it is Vulkan
	 */
	constexpr const ktk::tchar* kRenderer_Vulkan_Name = KOTEK_TEXT("Vulkan");

	/**
	 * Constant expresses in string that it is a flag used in application
	 * command argument list. Meaning is we use SDK. There's a difference
	 * between SDK and SDK ImGui. If we say just SDK it means we use static
	 * application based on OS buttons and UI and etc, but if we say SDK ImGui
	 * its UI rendering based on concept of immediate GUI. In our case we use
	 * ImGui library for implementing a such UI.
	 *
	 * It doesn't require to pass anything like logical true or false
	 * (yes/no;on/off) (using whitespace). So it forces to use SDK.
	 *
	 * Syntax: --editor
	 *
	 * @attention if engine was built without SDK the flag doesn't have any
	 * power.
	 *
	 * @code
	 * "--editor"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Editor =
		KOTEK_TEXT("--editor");

	/**
	 * Constant expresses that we specify width for our executable.
	 *
	 * Syntax: --width your_string_value
	 *
	 * @code
	 * "--width 1920"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Width =
		KOTEK_TEXT("--width");

	/**
	 * Constant expresses that we specify height for our executable.
	 *
	 * Syntax: --height your_string_value
	 *
	 * @code
	 * "--height 1080"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Height =
		KOTEK_TEXT("--height");

	/**
	 * Constant expresses that we specify what renderer the engine will use. If
	 * you passed this argument engine will force run with OpenGL renderer
	 * version 3.3.
	 *
	 * Syntax: --render_gl3_3
	 *
	 * @attention if the engine doesn't support the chosen renderer or engine
	 * wasn't compiled with a such sources it means the flag doesn't have any
	 * power.
	 *
	 * @code
	 * "--render_gl3_3"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Render_OpenGL3_3 =
		KOTEK_TEXT("--render_gl3_3");

	/**
	 * Constant expresses that we specify what renderer the engine will use. If
	 * you passed this argument engine will force run with OpenGL renderer
	 * version 4.6.
	 *
	 * Syntax: --render_gl4_6
	 *
	 * @attention if the engine doesn't support the chosen renderer or engine
	 * wasn't compiled with a such sources it means the flag doesn't have any
	 * power.
	 *
	 * @code
	 * "--render_gl4_6"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Render_OpenGL4_6 =
		KOTEK_TEXT("--render_gl4_6");

	/**
	 * Constant expresses that we specify what renderer the engine will use. If
	 * you passed this argument engine will force run with Vulkan renderer.
	 *
	 * Syntax: --render_vk
	 *
	 * @attention if the engine doesn't support the chosen renderer or engine
	 * wasn't compiled with a such sources it means the flag doesn't have any
	 * power.
	 *
	 * @code
	 * "--render_vk"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Render_Vulkan =
		KOTEK_TEXT("--render_vk");

	/**
	 * Constant expresses that we specify what renderer the engine will use. If you passed this argument engine will force run with DirectX 7 renderer.
	 * 
	 * Syntax: --render_dx_7
	 * 
	 * @attention if the engine doesn't support the chosen renderer or engine
	 * wasn't compiled with a such sources it means the flag doesn't have any
	 * power.
	 * 
	 * @code
	 * "--render_dx_7"
	 * @endcode
	 */
	constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX7 =
		KOTEK_TEXT("--render_dx_7");


	constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX8 =
		KOTEK_TEXT("--render_dx_8");


	constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX9 =
		KOTEK_TEXT("--render_dx_9");


	constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX11 =
		KOTEK_TEXT("--render_dx_11");


	constexpr const ktk::tchar* kConsoleCommandArg_Render_DirectX12 =
		KOTEK_TEXT("--render_dx_12");
} // namespace Kotek