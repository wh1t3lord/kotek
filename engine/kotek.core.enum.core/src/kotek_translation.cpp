#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
	ktk::cstring Translate_FolderIndex(eFolderIndex type)
	{
		switch (type)
		{
		case eFolderIndex::kFolderIndex_Root:
		{
			return KOTEK_TEXTU("Root");
		}
		case eFolderIndex::kFolderIndex_Gamedata:
		{
			return KOTEK_TEXTU("Gamedata");
		}
		case eFolderIndex::kFolderIndex_Configs:
		{
			return KOTEK_TEXTU("Configs");
		}
		case eFolderIndex::kFolderIndex_Models:
		{
			return KOTEK_TEXTU("Models");
		}
		case eFolderIndex::kFolderIndex_Scripts:
		{
			return KOTEK_TEXTU("Scripts");
		}
		case eFolderIndex::kFolderIndex_Shaders:
		{
			return KOTEK_TEXTU("Shaders");
		}
		case eFolderIndex::kFolderIndex_Sounds:
		{
			return KOTEK_TEXTU("Sounds");
		}
		case eFolderIndex::kFolderIndex_Textures:
		{
			return KOTEK_TEXTU("Textures");
		}
		case eFolderIndex::kFolderIndex_Levels:
		{
			return KOTEK_TEXTU("Levels");
		}
		case eFolderIndex::kFolderIndex_AI:
		{
			return KOTEK_TEXTU("AI");
		}
		case eFolderIndex::kFolderIndex_UserData:
		{
			return KOTEK_TEXTU("UserData");
		}
		case eFolderIndex::kFolderIndex_UserData_Tests:
		{
			return KOTEK_TEXTU("UserTests");
		}
		case eFolderIndex::kFolderIndex_UserData_ShaderCache:
		{
			return KOTEK_TEXTU("UserData_ShaderCache");
		}
		case eFolderIndex::kFolderIndex_Shaders_GLSL:
		{
			return KOTEK_TEXTU("Shaders_GLSL");
		}
		case eFolderIndex::kFolderIndex_Shaders_HLSL:
		{
			return KOTEK_TEXTU("Shaders_HLSL");
		}
		case eFolderIndex::kFolderindex_Shaders_SPV:
		{
			return KOTEK_TEXTU("Shaders_SPV");
		}
		case eFolderIndex::kFolderIndex_Shaders_WEBGPU:
		{
			return KOTEK_TEXTU("Shaders_WEBGPU");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_FOLDER_INDEX");
		}
		}
	}

	ktk::cstring Translate_EngineFeature(eEngineFeature type)
	{
		switch (type)
		{
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_ENGINE_FEATURE");
		}
		}
	}

	ktk::cstring Translate_EngineFeatureRender(eEngineFeatureRender type)
	{
		switch (type)
		{
		case eEngineFeatureRender::kEngine_Feature_Render_MSAA:
		{
			return KOTEK_TEXTU("MSAA");
		}
		case eEngineFeatureRender::kEngine_Feature_Render_VSYNC:
		{
			return KOTEK_TEXTU("VSYNC");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDER");
		}
		}
	}

	ktk::cstring Translate_EngineSupportedRenderer(
		eEngineSupportedRenderer type)
	{
		switch (type)
		{
		case eEngineSupportedRenderer::kDirectX_7:
		{
			return KOTEK_TEXTU("DirectX 7");
		}
		case eEngineSupportedRenderer::kDirectX_8:
		{
			return KOTEK_TEXTU("DirectX 8");
		}
		case eEngineSupportedRenderer::kDirectX_9:
		{
			return KOTEK_TEXTU("DirectX 9");
		}
		case eEngineSupportedRenderer::kDirectX_10:
		{
			return KOTEK_TEXTU("DirectX 10");
		}
		case eEngineSupportedRenderer::kDirectX_11:
		{
			return KOTEK_TEXTU("DirectX 11");
		}
		case eEngineSupportedRenderer::kDirectX_12:
		{
			return KOTEK_TEXTU("DirectX 12");
		}
		case eEngineSupportedRenderer::kOpenGL_1_0:
		{
			return KOTEK_TEXTU("OpenGL 1.0");
		}
		case eEngineSupportedRenderer::kOpenGL_1_1:
		{
			return KOTEK_TEXTU("OpenGL 1.1");
		}
		case eEngineSupportedRenderer::kOpenGL_1_2:
		{
			return KOTEK_TEXTU("OpenGL 1.2");
		}
		case eEngineSupportedRenderer::kOpenGL_1_3:
		{
			return KOTEK_TEXTU("OpenGL 1.3");
		}
		case eEngineSupportedRenderer::kOpenGL_1_4:
		{
			return KOTEK_TEXTU("OpenGL 1.4");
		}
		case eEngineSupportedRenderer::kOpenGL_1_5:
		{
			return KOTEK_TEXTU("OpenGL 1.5");
		}
		case eEngineSupportedRenderer::kOpenGL_2_0:
		{
			return KOTEK_TEXTU("OpenGL 2.0");
		}
		case eEngineSupportedRenderer::kOpenGL_2_1:
		{
			return KOTEK_TEXTU("OpenGL 2.1");
		}
		case eEngineSupportedRenderer::kOpenGL_3_0:
		{
			return KOTEK_TEXTU("OpenGL 3.0");
		}
		case eEngineSupportedRenderer::kOpenGL_3_1:
		{
			return KOTEK_TEXTU("OpenGL 3.1");
		}
		case eEngineSupportedRenderer::kOpenGL_3_2:
		{
			return KOTEK_TEXTU("OpenGL 3.2");
		}
		case eEngineSupportedRenderer::kOpenGL_3_3:
		{
			return KOTEK_TEXTU("OpenGL 3.3");
		}
		case eEngineSupportedRenderer::kOpenGL_4_0:
		{
			return KOTEK_TEXTU("OpenGL 4.0");
		}
		case eEngineSupportedRenderer::kOpenGL_4_1:
		{
			return KOTEK_TEXTU("OpenGL 4.1");
		}
		case eEngineSupportedRenderer::kOpenGL_4_2:
		{
			return KOTEK_TEXTU("OpenGL 4.2");
		}
		case eEngineSupportedRenderer::kOpenGL_4_3:
		{
			return KOTEK_TEXTU("OpenGL 4.3");
		}
		case eEngineSupportedRenderer::kOpenGL_4_4:
		{
			return KOTEK_TEXTU("OpenGL 4.4");
		}
		case eEngineSupportedRenderer::kOpenGL_4_5:
		{
			return KOTEK_TEXTU("OpenGL 4.5");
		}
		case eEngineSupportedRenderer::kOpenGL_4_6:
		{
			return KOTEK_TEXTU("OpenGL 4.6");
		}
		case eEngineSupportedRenderer::kVulkan_1_0:
		{
			return KOTEK_TEXTU("Vulkan 1.0");
		}
		case eEngineSupportedRenderer::kVulkan_1_1:
		{
			return KOTEK_TEXTU("Vulkan 1.1");
		}
		case eEngineSupportedRenderer::kVulkan_1_2:
		{
			return KOTEK_TEXTU("Vulkan 1.2");
		}
		case eEngineSupportedRenderer::kVulkan_1_3:
		{
			return KOTEK_TEXTU("Vulkan 1.3");
		}
		case eEngineSupportedRenderer::kOpenGLES_1:
		{
			return KOTEK_TEXTU("OpenGL ES 1");
		}
		case eEngineSupportedRenderer::kOpenGLES_2:
		{
			return KOTEK_TEXTU("OpenGL ES 2");
		}
		case eEngineSupportedRenderer::kOpenGLES_3_0:
		{
			return KOTEK_TEXTU("OpenGL ES 3.0");
		}
		case eEngineSupportedRenderer::kOpenGLES_3_1:
		{
			return KOTEK_TEXTU("OpenGL ES 3.1");
		}
		case eEngineSupportedRenderer::kOpenGLES_3_2:
		{
			return KOTEK_TEXTU("OpenGL ES 3.2");
		}
		case eEngineSupportedRenderer::kUnknown:
		{
			return KOTEK_TEXTU("Unknown");
		}
		default:
		{
			return KOTEK_TEXTU(
				"UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_DIRECTX_VERSION");
		}
		}
	}

	// TODO: re implement that in order to detect all possible flags what this
	// flag has
	ktk::cstring Translate_EngineFeatureRenderer(eEngineFeatureRenderer type)
	{
		switch (type)
		{
		case eEngineFeatureRenderer::kEngine_Feature_Renderer_DirectX_Latest:
		{
			return Translate_EngineSupportedRenderer(
				eEngineSupportedRenderer::kDirectX_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Feature_Renderer_OpenGL_Latest:
		{
			return Translate_EngineSupportedRenderer(
				eEngineSupportedRenderer::kOpenGL_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Feature_Renderer_OpenGLES_Latest:
		{
			return Translate_EngineSupportedRenderer(
				eEngineSupportedRenderer::kOpenGLES_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Feature_Renderer_Vulkan_Latest:
		{
			return Translate_EngineSupportedRenderer(
				eEngineSupportedRenderer::kVulkan_Latest);
		}
		case eEngineFeatureRenderer::
			kEngine_Feature_Renderer_OpenGL_SpecifiedByUser:
		{
			return KOTEK_TEXTU("OpenGL version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Feature_Renderer_DirectX_SpecifiedByUser:
		{
			return KOTEK_TEXTU("DirectX version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Feature_Renderer_Vulkan_SpecifiedByUser:
		{
			return KOTEK_TEXTU("Vulkan version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser:
		{
			return KOTEK_TEXTU("OpenGL ES version is specified by user");
		}
		case eEngineFeatureRenderer::kEngine_Feature_Renderer_Software:
		{
			return KOTEK_TEXTU("Software");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDERER");
		}
		}
	}

	ktk::cstring Translate_EngineFeatureRendererANGLE(
		eEngineFeatureRendererANGLE type)
	{
		switch (type)
		{
		case eEngineFeatureRendererANGLE::
			kEngine_Feature_Renderer_ANGLE_Feature_Desktop_GL:
		{
			return KOTEK_TEXTU("Desktop GL");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Feature_Renderer_ANGLE_Feature_DirectX_9:
		{
			return KOTEK_TEXTU("DirectX 9");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Feature_Renderer_ANGLE_Feature_DirectX_11:
		{
			return KOTEK_TEXTU("DirectX 11");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Feature_Renderer_ANGLE_Feature_Vulkan:
		{
			return KOTEK_TEXTU("Vulkan");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Feature_Renderer_ANGLE_Feature_GL_ES:
		{
			return KOTEK_TEXTU("GL ES");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Feature_Renderer_ANGLE_Feature_Metal:
		{
			return KOTEK_TEXTU("Metal");
		}
		default:
		{
			return KOTEK_TEXTU(
				"UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDERER_ANGLE");
		}
		}
	}

	ktk::cstring Translate_EngineFeatureSDK(eEngineFeatureSDK type)
	{
		switch (type)
		{
		case eEngineFeatureSDK::kEngine_Feature_SDK:
		{
			// TODO: add determing what GUI kit is used like wxWidgets, Qt, MFC
			// and etc
			return KOTEK_TEXTU("SDK (not ImGui Mode)");
		}
		case eEngineFeatureSDK::kEngine_Feature_SDK_ImGui:
		{
			return KOTEK_TEXTU("SDK (ImGui Mode)");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_ENGINE_FEATURE_SDK");
		}
		}
	}

	ktk::cstring Translate_EngineFeatureWindow(eEngineFeatureWindow type)
	{
		switch (type)
		{
		case eEngineFeatureWindow::kEngine_Feature_Window_Borderless:
		{
			return KOTEK_TEXTU("Borderless");
		}
		case eEngineFeatureWindow::kEngine_Feature_Window_FullScreen:
		{
			return KOTEK_TEXTU("FullScreen");
		}
		case eEngineFeatureWindow::kEngine_Feature_Window_Windowed:
		{
			return KOTEK_TEXTU("Windowed");
		}
		case eEngineFeatureWindow::kEngine_Feature_Window_None:
		{
			return KOTEK_TEXTU("None");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_ENGINE_FEATURE_WINDOW");
		}
		}
	}

	ktk::cstring Translate_ResourceLoadingType(eResourceLoadingType type)
	{
		switch (type)
		{
		case eResourceLoadingType::kAutoDetect:
		{
			return KOTEK_TEXTU("AutoDetect");
		}
		case eResourceLoadingType::kDLL:
		{
			return KOTEK_TEXTU("DLL (some programming module)");
		}
		case eResourceLoadingType::kModel:
		{
			return KOTEK_TEXTU("Model");
		}
		case eResourceLoadingType::kSound:
		{
			return KOTEK_TEXTU("Sound");
		}
		case eResourceLoadingType::kText:
		{
			return KOTEK_TEXTU("Text");
		}
		case eResourceLoadingType::kTexture:
		{
			return KOTEK_TEXTU("Texture");
		}
		case eResourceLoadingType::kUnknown:
		{
			return KOTEK_TEXTU("Unknown");
		}
		case eResourceLoadingType::kVideo:
		{
			return KOTEK_TEXTU("Video");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_RESOURCE_LOADING_TYPE");
		}
		}
	}

	ktk::cstring Translate_ResourceLoadingPolicy(eResourceLoadingPolicy type)
	{
		switch (type)
		{
		case eResourceLoadingPolicy::kAsync:
		{
			return KOTEK_TEXTU("Async");
		}
		case eResourceLoadingPolicy::kSync:
		{
			return KOTEK_TEXTU("Sync");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_RESOURCE_LOADING_POLICY");
		}
		}
	}

	ktk::cstring Translate_ResourceCachingPolicy(eResourceCachingPolicy type)
	{
		switch (type)
		{
		case eResourceCachingPolicy::kCache:
		{
			return KOTEK_TEXTU("Cache");
		}
		case eResourceCachingPolicy::kWithoutCache:
		{
			return KOTEK_TEXTU("WithoutCache");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_RESOURCE_CACHING_POLICY");
		}
		}
	}

	ktk::cstring Translate_ConsoleCommandIndex(eConsoleCommandIndex type)
	{
		switch (type)
		{
		case eConsoleCommandIndex::kConsoleCommand_App_Close:
		{
			return KOTEK_TEXTU("App_Close");
		}
		case eConsoleCommandIndex::kConsoleCommand_App_Hide:
		{
			return KOTEK_TEXTU("App_Hide");
		}
		case eConsoleCommandIndex::kConsoleCommand_App_Show:
		{
			return KOTEK_TEXTU("App_Show");
		}
		case eConsoleCommandIndex::
			kConsoleCommand_Render_UploadAllResourcesToGPU:
		{
			return KOTEK_TEXTU("Render_UploadAllResourcesToGPU");
		}
		case eConsoleCommandIndex::kConsoleCommand_Resize:
		{
			return KOTEK_TEXTU("Resize");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_CONSOLE_COMMAND_INDEX");
		}
		}
	}

	ktk::cstring Translate_InputType(eInputType type)
	{
		switch (type)
		{
		case eInputType::kInputType_Cursor:
		{
			return KOTEK_TEXTU("InputType_Cursor");
		}
		case eInputType::kInputType_DisabledCursor:
		{
			return KOTEK_TEXTU("InputType_DisabledCursor");
		}
		case eInputType::kInputType_HiddenCursor:
		{
			return KOTEK_TEXTU("InputType_HiddenCursor");
		}
		default:
		{
			return KOTEK_TEXTU("UNDEFINED_ENUM_OF_INPUT_TYPE");
		}
		}
	}

	const char* Translate_InputControllerType(eInputControllerType type)
	{
		switch (type)
		{
		case eInputControllerType::kControllerKeyboard:
		{
			return "controller_keyboard";
		}
		case eInputControllerType::kControllerMouse:
		{
			return "controller_mouse";
		}
		case eInputControllerType::kControllerGamepad:
		{
			return "controller_gamepad";
		}
		case eInputControllerType::kControllerJoystick:
		{
			return "controller_joystick";
		}
		case eInputControllerType::kControllerUnknown:
		{
			return "controller_unknown";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_INPUT_CONTROLLER_TYPE";
		}
		}
	}

	const char* Translate_InputControllerMouseData(
		eInputControllerMouseData type)
	{
		switch (type)
		{
		case eInputControllerMouseData::kMousePreviousCoordinateX:
		{
			return "previous_coordinate_x";
		}
		case eInputControllerMouseData::kMoousePreviousCoordinateY:
		{
			return "previous_coordinate_y";
		}
		case eInputControllerMouseData::kMouseCoordinateX:
		{
			return "coordinate_x";
		}
		case eInputControllerMouseData::kMouseCoordinateY:
		{
			return "coordinate_y";
		}
		case eInputControllerMouseData::kMouseSensetivity:
		{
			return "sensetivity";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_INPUT_CONTROLLER_MOUSE_DATA";
		}
		}
	}

	const char* Translate_InputKeyboardKeys(eInputKeyboardKeys type)
	{
		switch (type)
		{
		case eInputKeyboardKeys::kKEY_A:
			return "KEY_A";
		case eInputKeyboardKeys::kKEY_B:
			return "KEY_B";
		case eInputKeyboardKeys::kKEY_C:
			return "KEY_C";
		case eInputKeyboardKeys::kKEY_D:
			return "KEY_D";
		case eInputKeyboardKeys::kKEY_E:
			return "KEY_E";
		case eInputKeyboardKeys::kKEY_F:
			return "KEY_F";
		case eInputKeyboardKeys::kKEY_G:
			return "KEY_G";
		case eInputKeyboardKeys::kKEY_H:
			return "KEY_H";
		case eInputKeyboardKeys::kKEY_I:
			return "KEY_I";
		case eInputKeyboardKeys::kKEY_J:
			return "KEY_J";
		case eInputKeyboardKeys::kKEY_K:
			return "KEY_K";
		case eInputKeyboardKeys::kKEY_L:
			return "KEY_L";
		case eInputKeyboardKeys::kKEY_M:
			return "KEY_M";
		case eInputKeyboardKeys::kKEY_N:
			return "KEY_N";
		case eInputKeyboardKeys::kKEY_O:
			return "KEY_O";
		case eInputKeyboardKeys::kKEY_P:
			return "KEY_P";
		case eInputKeyboardKeys::kKEY_Q:
			return "KEY_Q";
		case eInputKeyboardKeys::kKEY_R:
			return "KEY_R";
		case eInputKeyboardKeys::kKEY_S:
			return "KEY_S";
		case eInputKeyboardKeys::kKEY_T:
			return "KEY_T";
		case eInputKeyboardKeys::kKEY_U:
			return "KEY_U";
		case eInputKeyboardKeys::kKEY_V:
			return "KEY_V";
		case eInputKeyboardKeys::kKEY_W:
			return "KEY_W";
		case eInputKeyboardKeys::kKEY_X:
			return "KEY_X";
		case eInputKeyboardKeys::kKEY_Y:
			return "KEY_Y";
		case eInputKeyboardKeys::kKEY_Z:
			return "KEY_Z";
		case eInputKeyboardKeys::kKEY_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS";
		}
	}

	const char* Translate_InputKeyboardKeysNumbers(
		eInputKeyboardKeysNumbers type)
	{
		switch (type)
		{
		case eInputKeyboardKeysNumbers::kKEY_1:
			return "KEY_1";
		case eInputKeyboardKeysNumbers::kKEY_2:
			return "KEY_2";
		case eInputKeyboardKeysNumbers::kKEY_3:
			return "KEY_3";
		case eInputKeyboardKeysNumbers::kKEY_4:
			return "KEY_4";
		case eInputKeyboardKeysNumbers::kKEY_5:
			return "KEY_5";
		case eInputKeyboardKeysNumbers::kKEY_6:
			return "KEY_6";
		case eInputKeyboardKeysNumbers::kKEY_7:
			return "KEY_7";
		case eInputKeyboardKeysNumbers::kKEY_8:
			return "KEY_8";
		case eInputKeyboardKeysNumbers::kKEY_9:
			return "KEY_9";
		case eInputKeyboardKeysNumbers::kKEY_0:
			return "KEY_0";
		case eInputKeyboardKeysNumbers::kKEY_NUMBER_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_NUMBER";
		}
	}

	const char* Translate_InputKeyboardKeysFunctionKeys(
		eInputKeyboardKeysFunctionKeys type)
	{
		switch (type)
		{
		case eInputKeyboardKeysFunctionKeys::kKEY_F1:
			return "KEY_F1";
		case eInputKeyboardKeysFunctionKeys::kKEY_F2:
			return "KEY_F2";
		case eInputKeyboardKeysFunctionKeys::kKEY_F3:
			return "KEY_F3";
		case eInputKeyboardKeysFunctionKeys::kKEY_F4:
			return "KEY_F4";
		case eInputKeyboardKeysFunctionKeys::kKEY_F5:
			return "KEY_F5";
		case eInputKeyboardKeysFunctionKeys::kKEY_F6:
			return "KEY_F6";
		case eInputKeyboardKeysFunctionKeys::kKEY_F7:
			return "KEY_F7";
		case eInputKeyboardKeysFunctionKeys::kKEY_F8:
			return "KEY_F8";
		case eInputKeyboardKeysFunctionKeys::kKEY_F9:
			return "KEY_F9";
		case eInputKeyboardKeysFunctionKeys::kKEY_F10:
			return "KEY_F10";
		case eInputKeyboardKeysFunctionKeys::kKEY_F11:
			return "KEY_F11";
		case eInputKeyboardKeysFunctionKeys::kKEY_F12:
			return "KEY_F12";
		case eInputKeyboardKeysFunctionKeys::kKEY_FUNCTION_KEY_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_FUNCTION_KEYS";
		}
	}

	const char* Translate_InputKeyboardKeysOther(eInputKeyboardKeysOther type)
	{
		switch (type)
		{
		case eInputKeyboardKeysOther::kKEY_PRTSC:
			return "KEY_PRTSC";
		case eInputKeyboardKeysOther::kKEY_PAUSE:
			return "KEY_PAUSE";
		case eInputKeyboardKeysOther::kKEY_DEL:
			return "KEY_DEL";
		case eInputKeyboardKeysOther::kKEY_END:
			return "KEY_END";
		case eInputKeyboardKeysOther::kKEY_INSERT:
			return "KEY_INSERT";
		case eInputKeyboardKeysOther::kKEY_HOME:
			return "KEY_HOME";
		case eInputKeyboardKeysOther::kKEY_PAGEUP:
			return "KEY_PAGEUP";
		case eInputKeyboardKeysOther::kKEY_PAGEDOWN:
			return "KEY_PAGEDOWN";
		case eInputKeyboardKeysOther::kKEY_SCROLLLOCK:
			return "kKEY_SCROLLLOCK";
		case eInputKeyboardKeysOther::kKEY_ESC:
			return "kKEY_ESC";
		case eInputKeyboardKeysOther::kKEY_OTHER_KEY_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_OTHER";
		}
	}

	const char* Translate_InputKeyboardKeysEnter(eInputKeyboardKeysEnter type)
	{
		switch (type)
		{
		case eInputKeyboardKeysEnter::kKEY_ENTER:
			return "KEY_ENTER";
		case eInputKeyboardKeysEnter::kKEY_ENTER_NUMPAD:
			return "KEY_NUMPAD_ENTER";
		case eInputKeyboardKeysEnter::kKEY_ENTER_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_ENTER";
		}
	}

	const char* Translate_InputKeyboardKeysNumpad(eInputKeyboardKeysNumpad type)
	{
		switch (type)
		{
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_NUMLOCK:
			return "KEY_NUMPAD_NUMLOCK";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_ENTER:
			return "KEY_NUMPAD_ENTER";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_SLASH:
			return "KEY_NUMPAD_SLASH";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_ASTERISK:
			return "KEY_NUMPAD_ASTERISK";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_1:
			return "KEY_NUMPAD_1";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_2:
			return "KEY_NUMPAD_2";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_3:
			return "KEY_NUMPAD_3";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_4:
			return "KEY_NUMPAD_4";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_5:
			return "KEY_NUMPAD_5";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_6:
			return "KEY_NUMPAD_6";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_7:
			return "KEY_NUMPAD_7";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_8:
			return "KEY_NUMPAD_8";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_9:
			return "KEY_NUMPAD_9";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_0:
			return "KEY_NUMPAD_0";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_MINUS:
			return "KEY_NUMPAD_MINUS";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_PLUS:
			return "KEY_NUMPAD_PLUS";
		case eInputKeyboardKeysNumpad::kKEY_NUMPAD_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_NUMPAD";
		}
	}

	const char* Translate_InputKeyboardKeysApplication(
		eInputKeyboardKeysApplication type)
	{
		switch (type)
		{
		case eInputKeyboardKeysApplication::kKEY_MENU:
			return "KEY_MENU";
		case eInputKeyboardKeysApplication::kKEY_APPLICATION_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_APPLICATION";
		}
	}

	const char* Translate_InputKeyboardKeysSystem(eInputKeyboardKeysSystem type)
	{
		switch (type)
		{
		case eInputKeyboardKeysSystem::kKEY_WINDOWS:
			return "KEY_WINDOWS";
		case eInputKeyboardKeysSystem::kKEY_SYSTEM_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_KEYS_SYSTEM";
		}
	}

	const char* Translate_InputKeyboardCursorControlKeys(
		eInputKeyboardCursorControlKeys type)
	{
		switch (type)
		{
		case eInputKeyboardCursorControlKeys::kKEY_ARROW_LEFT:
			return "KEY_ARROW_LEFT";
		case eInputKeyboardCursorControlKeys::kKEY_ARROW_UP:
			return "KEY_ARROW_UP";
		case eInputKeyboardCursorControlKeys::kKEY_ARROW_RIGHT:
			return "KEY_ARROW_RIGHT";
		case eInputKeyboardCursorControlKeys::kKEY_ARROW_DOWN:
			return "KEY_ARROW_DOWN";
		case eInputKeyboardCursorControlKeys::kKEY_CURSOR_CONTROL_UNKNOWN:
			return "KEY_UNKNOWN";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_KEYBOARD_CURSOR_CONTROL_KEYS";
		}
	}

	const char* Translate_InputMouseKeys(eInputMouseKeys type)
	{
		switch (type)
		{
		case eInputMouseKeys::kKEY_LeftButton:
			return "KEY_LEFT";
		case eInputMouseKeys::kKEY_RightButton:
			return "KEY_RIGHT";
		case eInputMouseKeys::kKEY_MiddleButton:
			return "KEY_MIDDLE";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_MOUSE_KEYS";
		}
	}

	const char* Translate_InputPlatformBackend(eInputPlatformBackend type)
	{
		switch (type)
		{
		case eInputPlatformBackend::kPlatformBackend_GLFW3:
			return "GLFW3";
		case eInputPlatformBackend::kPlatformBackend_SDL2:
			return "SDL2";
		case eInputPlatformBackend::kPlatformBackend_SDL3:
			return "SDL3";
		case eInputPlatformBackend::kPlatformBackend_WINAPI:
			return "WINAPI";
		case eInputPlatformBackend::kPlatformBackend_X11:
			return "X11";
		case eInputPlatformBackend::kPlatformBackend_MACOS:
			return "MACOS";
		case eInputPlatformBackend::kPlatformBackend_PS1:
			return "PS1";
		case eInputPlatformBackend::kPlatformBackend_PS2:
			return "PS2";
		case eInputPlatformBackend::kPlatformBackend_PS3:
			return "PS3";
		case eInputPlatformBackend::kPlatformBackend_PS4:
			return "PS4";
		case eInputPlatformBackend::kPlatformBackend_PS5:
			return "PS5";
		case eInputPlatformBackend::kPlatformBackend_PS6:
			return "PS6";
		case eInputPlatformBackend::kPlatformBackend_XBOX:
			return "XBOX";
		case eInputPlatformBackend::kPlatformBackend_XBOXONE:
			return "XBOXONE";
		case eInputPlatformBackend::kPlatformBackend_XBOXSERIESS:
			return "XBOXSERIES_S";
		case eInputPlatformBackend::kPlatformBackend_XBOXSERIESX:
			return "XBOXSERIES_X";
		case eInputPlatformBackend::kPlatformBackend_NS:
			return "NS";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_PLATFORM_BACKEND";
		}
	}

	const char* Translate_InputAllKeys(eInputAllKeys type)
	{
		switch (type)
		{
		case eInputAllKeys::kCK_KEY_A:
			return "KEY_A";
		case eInputAllKeys::kCK_KEY_B:
			return "KEY_B";
		case eInputAllKeys::kCK_KEY_C:
			return "KEY_C";
		case eInputAllKeys::kCK_KEY_D:
			return "KEY_D";
		case eInputAllKeys::kCK_KEY_E:
			return "KEY_E";
		case eInputAllKeys::kCK_KEY_F:
			return "KEY_F";
		case eInputAllKeys::kCK_KEY_G:
			return "KEY_G";
		case eInputAllKeys::kCK_KEY_H:
			return "KEY_H";
		case eInputAllKeys::kCK_KEY_I:
			return "KEY_I";
		case eInputAllKeys::kCK_KEY_J:
			return "KEY_J";
		case eInputAllKeys::kCK_KEY_K:
			return "KEY_K";
		case eInputAllKeys::kCK_KEY_L:
			return "KEY_L";
		case eInputAllKeys::kCK_KEY_M:
			return "KEY_M";
		case eInputAllKeys::kCK_KEY_N:
			return "KEY_N";
		case eInputAllKeys::kCK_KEY_O:
			return "KEY_O";
		case eInputAllKeys::kCK_KEY_P:
			return "KEY_P";
		case eInputAllKeys::kCK_KEY_Q:
			return "KEY_Q";
		case eInputAllKeys::kCK_KEY_R:
			return "KEY_R";
		case eInputAllKeys::kCK_KEY_S:
			return "KEY_S";
		case eInputAllKeys::kCK_KEY_T:
			return "KEY_T";
		case eInputAllKeys::kCK_KEY_U:
			return "KEY_U";
		case eInputAllKeys::kCK_KEY_V:
			return "KEY_V";
		case eInputAllKeys::kCK_KEY_W:
			return "KEY_W";
		case eInputAllKeys::kCK_KEY_X:
			return "KEY_X";
		case eInputAllKeys::kCK_KEY_Y:
			return "KEY_Y";
		case eInputAllKeys::kCK_KEY_Z:
			return "KEY_Z";
		case eInputAllKeys::kCK_KEY_CAPS_LOCK:
			return "KEY_CAPS_LOCK";
		case eInputAllKeys::kCK_KEY_SCROLL_LOCK:
			return "KEY_SCROLL_LOCK";
		case eInputAllKeys::kCK_KEY_1:
			return "KEY_1";
		case eInputAllKeys::kCK_KEY_2:
			return "KEY_2";
		case eInputAllKeys::kCK_KEY_3:
			return "KEY_3";
		case eInputAllKeys::kCK_KEY_4:
			return "KEY_4";
		case eInputAllKeys::kCK_KEY_5:
			return "KEY_5";
		case eInputAllKeys::kCK_KEY_6:
			return "KEY_6";
		case eInputAllKeys::kCK_KEY_7:
			return "KEY_7";
		case eInputAllKeys::kCK_KEY_8:
			return "KEY_8";
		case eInputAllKeys::kCK_KEY_9:
			return "KEY_9";
		case eInputAllKeys::kCK_KEY_0:
			return "KEY_0";
		case eInputAllKeys::kCK_KEY_MINUS:
			return "KEY_MINUS";
		case eInputAllKeys::kCK_KEY_PLUS:
			return "KEY_PLUS";
		case eInputAllKeys::kCK_KEY_F1:
			return "KEY_F1";
		case eInputAllKeys::kCK_KEY_F2:
			return "KEY_F2";
		case eInputAllKeys::kCK_KEY_F3:
			return "KEY_F3";
		case eInputAllKeys::kCK_KEY_F4:
			return "KEY_F4";
		case eInputAllKeys::kCK_KEY_F5:
			return "KEY_F5";
		case eInputAllKeys::kCK_KEY_F6:
			return "KEY_F6";
		case eInputAllKeys::kCK_KEY_F7:
			return "KEY_F7";
		case eInputAllKeys::kCK_KEY_F8:
			return "KEY_F8";
		case eInputAllKeys::kCK_KEY_F9:
			return "KEY_F9";
		case eInputAllKeys::kCK_KEY_F10:
			return "KEY_F10";
		case eInputAllKeys::kCK_KEY_F11:
			return "KEY_F11";
		case eInputAllKeys::kCK_KEY_F12:
			return "KEY_F12";
		case eInputAllKeys::kCK_KEY_PRTSC:
			return "KEY_PRTSC";
		case eInputAllKeys::kCK_KEY_PAUSE:
			return "KEY_PAUSE";
		case eInputAllKeys::kCK_KEY_DEL:
			return "KEY_DEL";
		case eInputAllKeys::kCK_KEY_END:
			return "KEY_END";
		case eInputAllKeys::kCK_KEY_INSERT:
			return "KEY_INSERT";
		case eInputAllKeys::kCK_KEY_HOME:
			return "KEY_HOME";
		case eInputAllKeys::kCK_KEY_PAGEUP:
			return "KEY_PAGEUP";
		case eInputAllKeys::kCK_KEY_PAGEDOWN:
			return "KEY_PAGEDOWN";
		case eInputAllKeys::kCK_KEY_SCROLLLOCK:
			return "KEY_SCROLLLOCK";
		case eInputAllKeys::kCK_KEY_ESC:
			return "KEY_ESC";
		case eInputAllKeys::kCK_KEY_SPACE:
			return "KEY_SPACE";
		case eInputAllKeys::kCK_KEY_LEFT_SHIFT:
			return "KEY_LEFT_SHIFT";
		case eInputAllKeys::kCK_KEY_RIGHT_SHIFT:
			return "KEY_RIGHT_SHIFT";
		case eInputAllKeys::kCK_KEY_LEFT_CONTROL:
			return "KEY_LEFT_CONTROL";
		case eInputAllKeys::kCK_KEY_RIGHT_CONTROL:
			return "KEY_RIGHT_CONTROL";
		case eInputAllKeys::kCK_KEY_APOSTROPHE:
			return "KEY_APOSTROPHE";
		case eInputAllKeys::kCK_KEY_COMMA:
			return "KEY_COMMA";
		case eInputAllKeys::kCK_KEY_PERIOD:
			return "KEY_PERIOD";
		case eInputAllKeys::kCK_KEY_SLASH:
			return "KEY_SLASH";
		case eInputAllKeys::kCK_KEY_BACKSLASH:
			return "KEY_BACKSLASH";
		case eInputAllKeys::kCK_KEY_SEMICOLON:
			return "KEY_SEMICOLON";
		case eInputAllKeys::kCK_KEY_EQUAL:
			return "KEY_EQUAL";
		case eInputAllKeys::kCK_KEY_LEFT_BRACKET:
			return "KEY_LEFT_BRACKET";
		case eInputAllKeys::kCK_KEY_RIGHT_BRACKET:
			return "KEY_RIGHT_BRACKET";
		case eInputAllKeys::kCK_KEY_GRAVE_ACCENT:
			return "KEY_GRAVE_ACCENT";
		case eInputAllKeys::kCK_KEY_ESCAPE:
			return "KEY_ESCAPE";
		case eInputAllKeys::kCK_KEY_TAB:
			return "KEY_TAB";
		case eInputAllKeys::kCK_KEY_BACKSPACE:
			return "KEY_BACKSPACE";
		case eInputAllKeys::kCK_KEY_ENTER:
			return "KEY_ENTER";
		case eInputAllKeys::kCK_KEY_ENTER_NUMPAD:
			return "KEY_ENTER_NUMPAD";
		case eInputAllKeys::kCK_KEY_NUMPAD_NUMLOCK:
			return "KEY_NUMPAD_NUMLOC";
		case eInputAllKeys::kCK_KEY_NUMPAD_ENTER:
			return "KEY_NUMPAD_ENTER";
		case eInputAllKeys::kCK_KEY_NUMPAD_SLASH:
			return "KEY_NUMPAD_SLASH";
		case eInputAllKeys::kCK_KEY_NUMPAD_ASTERISK:
			return "KEY_NUMPAD_ASTERI";
		case eInputAllKeys::kCK_KEY_NUMPAD_1:
			return "KEY_NUMPAD_1";
		case eInputAllKeys::kCK_KEY_NUMPAD_2:
			return "KEY_NUMPAD_2";
		case eInputAllKeys::kCK_KEY_NUMPAD_3:
			return "KEY_NUMPAD_3";
		case eInputAllKeys::kCK_KEY_NUMPAD_4:
			return "KEY_NUMPAD_4";
		case eInputAllKeys::kCK_KEY_NUMPAD_5:
			return "KEY_NUMPAD_5";
		case eInputAllKeys::kCK_KEY_NUMPAD_6:
			return "KEY_NUMPAD_6";
		case eInputAllKeys::kCK_KEY_NUMPAD_7:
			return "KEY_NUMPAD_7";
		case eInputAllKeys::kCK_KEY_NUMPAD_8:
			return "KEY_NUMPAD_8";
		case eInputAllKeys::kCK_KEY_NUMPAD_9:
			return "KEY_NUMPAD_9";
		case eInputAllKeys::kCK_KEY_NUMPAD_0:
			return "KEY_NUMPAD_0";
		case eInputAllKeys::kCK_KEY_NUMPAD_MINUS:
			return "KEY_NUMPAD_MINUS";
		case eInputAllKeys::kCK_KEY_NUMPAD_PLUS:
			return "KEY_NUMPAD_PLUS";
		case eInputAllKeys::kCK_KEY_MENU:
			return "KEY_MENU";
		case eInputAllKeys::kCK_KEY_LEFT_ALT:
			return "KEY_LEFT_ALT";
		case eInputAllKeys::kCK_KEY_RIGHT_ALT:
			return "KEY_RIGHT_ALT";
		case eInputAllKeys::kCK_KEY_LEFT_SUPER:
			return "KEY_LEFT_SUPER";
		case eInputAllKeys::kCK_KEY_RIGHT_SUPER:
			return "KEY_RIGHT_SUPER";
		case eInputAllKeys::kCK_KEY_WINDOWS:
			return "KEY_WINDOWS";
		case eInputAllKeys::kCK_KEY_ARROW_LEFT:
			return "KEY_ARROW_LEFT";
		case eInputAllKeys::kCK_KEY_ARROW_UP:
			return "KEY_ARROW_UP";
		case eInputAllKeys::kCK_KEY_ARROW_RIGHT:
			return "KEY_ARROW_RIGHT";
		case eInputAllKeys::kCK_KEY_ARROW_DOWN:
			return "KEY_ARROW_DOWN";
		case eInputAllKeys::kCM_KEY_LEFT:
			return "KEY_LEFT";
		case eInputAllKeys::kCM_KEY_RIGHT:
			return "KEY_RIGHT";
		case eInputAllKeys::kCM_KEY_MIDDLE:
			return "KEY_MIDDLE";
		case eInputAllKeys::kCA_KEY_END_ENUM:
			return "KEY_END_ENUM";
		default:
			return "UNDEFINED_ENUM_OF_INPUT_ALL_KEYS";
		}
	}

	eEngineSupportedRenderer TranslateFromStringToEnum_EngineSupportedRenderer(
		const ktk::cstring& renderer_name, const ktk::cstring& version_name)
	{
		eEngineSupportedRenderer result{eEngineSupportedRenderer::kUnknown};

		if (version_name.empty())
			return result;

		if (renderer_name.empty())
			return result;

		bool is_latest = ktk::to_lower(version_name) == KOTEK_TEXTU("latest");

		int major_version{};
		int minor_version{};

		if (renderer_name == KOTEK_TEXTU("GL"))
		{
			major_version = ktk::lexical_cast<int>(version_name[0]);
			minor_version = ktk::lexical_cast<int>(version_name[2]);

			if (is_latest)
			{
				return eEngineSupportedRenderer::kOpenGL_Latest;
			}

			switch (major_version)
			{
			case 0:
			{
				return result;
			}
			case 1:
			{
				switch (minor_version)
				{
				case 0:
				{
					result = eEngineSupportedRenderer::kOpenGL_1_0;
					break;
				}
				case 1:
				{
					result = eEngineSupportedRenderer::kOpenGL_1_1;
					break;
				}
				case 2:
				{
					result = eEngineSupportedRenderer::kOpenGL_1_2;
					break;
				}
				case 3:
				{
					result = eEngineSupportedRenderer::kOpenGL_1_3;
					break;
				}
				case 4:
				{
					result = eEngineSupportedRenderer::kOpenGL_1_4;
					break;
				}
				case 5:
				{
					result = eEngineSupportedRenderer::kOpenGL_1_5;
					break;
				}
				default:
				{
					return result;
				}
				}

				return result;
			}
			case 2:
			{
				switch (minor_version)
				{
				case 0:
				{
					result = eEngineSupportedRenderer::kOpenGL_2_0;
					break;
				}
				case 1:
				{
					result = eEngineSupportedRenderer::kOpenGL_2_1;
					break;
				}
				default:
				{
					return result;
				}
				}

				return result;
			}
			case 3:
			{
				switch (minor_version)
				{
				case 0:
				{
					result = eEngineSupportedRenderer::kOpenGL_3_0;
					break;
				}
				case 1:
				{
					result = eEngineSupportedRenderer::kOpenGL_3_1;
					break;
				}
				case 2:
				{
					result = eEngineSupportedRenderer::kOpenGL_3_2;
					break;
				}
				case 3:
				{
					result = eEngineSupportedRenderer::kOpenGL_3_3;
					break;
				}
				default:
				{
					return result;
				}
				}

				return result;
			}
			case 4:
			{
				switch (minor_version)
				{
				case 0:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_0;
					break;
				}
				case 1:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_1;
					break;
				}
				case 2:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_2;
					break;
				}
				case 3:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_3;
					break;
				}
				case 4:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_4;
					break;
				}
				case 5:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_5;
					break;
				}
				case 6:
				{
					result = eEngineSupportedRenderer::kOpenGL_4_6;
					break;
				}
				default:
				{
					return result;
				}
				}

				return result;
			}
			default:
			{
				return result;
			}
			}

			return result;
		}
		else if (renderer_name == KOTEK_TEXTU("GLES"))
		{
			major_version = ktk::lexical_cast<int>(version_name[0]);
			minor_version = ktk::lexical_cast<int>(version_name[2]);

			if (is_latest)
			{
				return eEngineSupportedRenderer::kOpenGLES_Latest;
			}

			switch (major_version)
			{
			case 1:
			{
				switch (minor_version)
				{
				case 0:
					result = eEngineSupportedRenderer::kOpenGLES_1;
					break;
				}
			}
			case 2:
			{
				result = eEngineSupportedRenderer::kOpenGLES_2;
				break;
			}
			case 3:
			{
				switch (minor_version)
				{
				case 0:
				{
					result = eEngineSupportedRenderer::kOpenGLES_3_0;
					break;
				}
				case 1:
				{
					result = eEngineSupportedRenderer::kOpenGLES_3_1;
					break;
				}
				case 2:
				{
					result = eEngineSupportedRenderer::kOpenGLES_3_2;
					break;
				}
				}
			}
			default:
			{
				return result;
			}
			}

			return result;
		}
		else if (renderer_name == KOTEK_TEXTU("DX"))
		{
			major_version = ktk::lexical_cast<int>(version_name.c_str());

			if (is_latest)
			{
				return eEngineSupportedRenderer::kDirectX_Latest;
			}

			switch (major_version)
			{
			case 7:
			{
				result = eEngineSupportedRenderer::kDirectX_7;
				break;
			}
			case 8:
			{
				result = eEngineSupportedRenderer::kDirectX_8;
				break;
			}
			case 9:
			{
				result = eEngineSupportedRenderer::kDirectX_9;
				break;
			}
			case 10:
			{
				result = eEngineSupportedRenderer::kDirectX_10;
				break;
			}
			case 11:
			{
				result = eEngineSupportedRenderer::kDirectX_11;
				break;
			}
			case 12:
			{
				result = eEngineSupportedRenderer::kDirectX_12;
				break;
			}
			}

			return result;
		}
		else if (renderer_name == KOTEK_TEXTU("VK"))
		{
			major_version = ktk::lexical_cast<int>(version_name[0]);
			minor_version = ktk::lexical_cast<int>(version_name[2]);

			if (is_latest)
			{
				return eEngineSupportedRenderer::kVulkan_Latest;
			}

			switch (major_version)
			{
			case 1:
			{
				switch (minor_version)
				{
				case 0:
				{
					result = eEngineSupportedRenderer::kVulkan_1_0;
					break;
				}
				case 1:
				{
					result = eEngineSupportedRenderer::kVulkan_1_1;
					break;
				}
				case 2:
				{
					result = eEngineSupportedRenderer::kVulkan_1_2;
					break;
				}
				case 3:
				{
					result = eEngineSupportedRenderer::kVulkan_1_3;
					break;
				}
				}

				return result;
			}
			default:
			{
				return result;
			}
			}

			return result;
		}
		else
		{
			return result;
		}
	}

	eEngineFeatureRenderer TranslateFromStringToEnum_EngineFeatureRenderer(
		const ktk::cstring& name)
	{
		eEngineFeatureRenderer result{
			eEngineFeatureRenderer::kEngine_Feature_Renderer_None};

		if (name.empty())
			return result;

		auto renderer_name = ktk::to_lower(name);

		if (renderer_name == KOTEK_TEXTU("angle") ||
			renderer_name == KOTEK_TEXTU("opengl es") ||
			renderer_name == KOTEK_TEXTU("opengles") ||
			renderer_name == KOTEK_TEXTU("gles") ||
			renderer_name == KOTEK_TEXTU("gl es"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser;
		}
		else if (renderer_name == KOTEK_TEXTU("software") ||
			renderer_name == KOTEK_TEXTU("sw"))
		{
			result = eEngineFeatureRenderer::kEngine_Feature_Renderer_Software;
		}
		else if (renderer_name == KOTEK_TEXTU("directx") ||
			renderer_name == KOTEK_TEXTU("dx"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Feature_Renderer_DirectX_SpecifiedByUser;
		}
		else if (renderer_name == KOTEK_TEXTU("vulkan") ||
			renderer_name == KOTEK_TEXTU("vk"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Feature_Renderer_Vulkan_SpecifiedByUser;
		}
		else if (renderer_name == KOTEK_TEXTU("opengl") ||
			renderer_name == KOTEK_TEXTU("gl"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Feature_Renderer_OpenGL_SpecifiedByUser;
		}

		return result;
	}
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
