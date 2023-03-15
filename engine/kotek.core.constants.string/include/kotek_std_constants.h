#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>

/**
 * This section stands for all string constants that could be used by engine
 */
KOTEK_BEGIN_NAMESPACE_KOTEK
/**
 * Use these path's separator only if you don't use boost or std otherwise
 * use std::filesystem::path::preferred_separator
 */
#ifdef KOTEK_PLATFORM_WINDOWS
constexpr char kPathSeparator = '\\';
#else
constexpr char kPathSeparator = '/';
#endif

constexpr const char* kRenderer_OpenGLES_3_Name = "OpenGL ES 3";

/**
 * Constant expresses in string that it is OpenGL version 3.3
 */
constexpr const char* kRenderer_OpenGL3_3_Name = "OpenGL 3.3";

/**
 * Constant expresses in string that it is OpenGL version 2.0
 */
constexpr const char* kRenderer_OpenGL2_0_Name = "OpenGL 2.0";

/**
 * Constant expresses in string that it is OpenGL version 4.6
 */
constexpr const char* kRenderer_OpenGL4_6_Name = "OpenGL 4.6";

/**
 * Constant expresses in string that it is DirectX 7
 */
constexpr const char* kRenderer_DirectX_7_Name = "DirectX 7";

/**
 * Constant expresses in string that it is DirectX 8
 */
constexpr const char* kRenderer_DirectX_8_Name = "DirectX 8";

/**
 * Constant expresses in string that it is DirectX 9
 */
constexpr const char* kRenderer_DirectX_9_Name = "DirectX 9";

/**
 * Constant expresses in string that it is DirectX 10
 */
constexpr const char* kRenderer_DirectX_10_Name =
    "DirectX 10";

/**
 * Constant expresses in string that it is DirectX 11
 */
constexpr const char* kRenderer_DirectX_11_Name =
    "DirectX 11";

/**
 * Constant expresses in string that it is DirectX 12
 */
constexpr const char* kRenderer_DirectX_12_Name =
    "DirectX 12";

/**
 * Constant expresses in string that it is Vulkan
 */
constexpr const char* kRenderer_Vulkan_Name = "Vulkan";

/**
 * Constant expresses in string that it is Software renderer
 */
constexpr const char* kRenderer_Software_Name = "Software";

constexpr const char* kRenderer_Unknown_Name =
    "RENDERER_UNKNOWN";

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
 * @attention if engine was built without KOTEK_USE_SDK the flag doesn't
 * have any power.
 *
 * @code
 * "--editor"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Editor = "--editor";

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
 * Syntax: --editor_imgui
 *
 * @attention if engine was built without KOTEK_USE_SDK_IMGUI the flag
 * doesn't have any power.
 *
 * @code
 * "--editor_imgui"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Editor_ImGui =
    "--editor_imgui";

/**
 * Constant expresses that we specify width for our executable.
 *
 * Syntax: --width your_string_value
 *
 * @code
 * "--width 1920"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Width = "--width";

/**
 * Constant expresses that we specify height for our executable.
 *
 * Syntax: --height your_string_value
 *
 * @code
 * "--height 1080"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Height = "--height";

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
constexpr const char* kConsoleCommandArg_Render_OpenGL3_3 =
    "--render_gl3_3";

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
constexpr const char* kConsoleCommandArg_Render_OpenGL4_6 =
    "--render_gl4_6";

constexpr const char* kConsoleCommandArg_Render_OpenGL_Latest =
    "--render_gl_latest";

constexpr const char* kConsoleCommandArg_Render_OpenGLES1_0 =
	"--render_gles1_0";
constexpr const char* kConsoleCommandArg_Render_OpenGLES2_0 =
	"--render_gles2_0";
constexpr const char* kConsoleCommandArg_Render_OpenGLES3_0 =
	"--render_gles3_0";
constexpr const char* kConsoleCommandArg_Render_OpenGLES3_1 =
	"--render_gles3_1";
constexpr const char* kConsoleCommandArg_Render_OpenGLES3_2 =
	"--render_gles3_2";
constexpr const char* kConsoleCommandArg_Render_OpenGLES_Latest =
	"--render_gles_latest";

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
constexpr const char* kConsoleCommandArg_Render_Vulkan1_0 =
    "--render_vk1_0";

constexpr const char* kConsoleCommandArg_Render_Vulkan1_1 =
    "--render_vk1_1";

constexpr const char* kConsoleCommandArg_Render_Vulkan1_2 =
    "--render_vk1_2";

constexpr const char* kConsoleCommandArg_Render_Vulkan1_3 =
    "--render_vk1_3";

constexpr const char* kConsoleCommandArg_Render_Vulkan_Latest =
    "--render_vk_latest";

/**
 * Constant expresses that we specify what renderer the engine will use. If
 * you passed this argument engine will force run with DirectX 7 renderer.
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
constexpr const char* kConsoleCommandArg_Render_DirectX7 =
    "--render_dx_7";

/**
 * Constant expresses that we specify what renderer the engine will use. If
 * you passed this argument engine will force run with DirectX 8 renderer.
 *
 * Syntax: --render_dx_8
 *
 * @attention if the engine doesn't support the chosen renderer or engine
 * wasn't compiled with a such sources it means the flag doesn't have any
 * power.
 *
 * @code
 * "--render_dx_8"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Render_DirectX8 =
    "--render_dx_8";

/**
 * Constant expresses that we specify what renderer the engine will use. If
 * you passed this argument engine will force run with DirectX 9 renderer.
 *
 * Syntax: --render_dx_9
 *
 * @attention if the engine doesn't support the chosen renderer or engine
 * wasn't compiled with a such sources it means the flag doesn't have any
 * power.
 *
 * @code
 * "--render_dx_9"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Render_DirectX9 =
    "--render_dx_9";

/**
 * Constant expresses that we specify what renderer the engine will use. If
 * you passed this argument engine will force run with DirectX 10 renderer.
 *
 * Syntax: --render_dx_10
 *
 * @attention if the engine doesn't support the chosen renderer or engine
 * wasn't compiled with a such sources it means the flag doesn't have any
 * power.
 *
 * @code
 * "--render_dx_10"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Render_DirectX10 =
    "--render_dx_10";

/**
 * Constant expresses that we specify what renderer the engine will use. If
 * you passed this argument engine will force run with DirectX 11 renderer.
 *
 * Syntax: --render_dx_11
 *
 * @attention if the engine doesn't support the chosen renderer or engine
 * wasn't compiled with a such sources it means the flag doesn't have any
 * power.
 *
 * @code
 * "--render_dx_11"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Render_DirectX11 =
    "--render_dx_11";

/**
 * Constant expresses that we specify what renderer the engine will use. If
 * you passed this argument engine will force run with DirectX 12 renderer.
 *
 * Syntax: --render_dx_12
 *
 * @attention if the engine doesn't support the chosen renderer or engine
 * wasn't compiled with a such sources it means the flag doesn't have any
 * power.
 *
 * @code
 * "--render_dx_12"
 * @endcode
 */
constexpr const char* kConsoleCommandArg_Render_DirectX12 =
    "--render_dx_12";

constexpr const char* kConsoleCommandArg_Render_DirectX_Latest =
    "--render_dx_latest";

KOTEK_END_NAMESPACE_KOTEK
