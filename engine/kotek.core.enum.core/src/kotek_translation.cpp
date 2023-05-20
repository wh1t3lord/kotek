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
		case eFolderIndex::kFolderIndex_UserTests:
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
		case eEngineFeatureRender::kEngine_Render_Feature_MSAA:
		{
			return KOTEK_TEXTU("MSAA");
		}
		case eEngineFeatureRender::kEngine_Render_Feature_VSYNC:
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
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest:
		{
			return Translate_EngineSupportedRenderer(eEngineSupportedRenderer::kDirectX_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest:
		{
			return Translate_EngineSupportedRenderer(
				eEngineSupportedRenderer::kOpenGL_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGLES_Latest:
		{
			return Translate_EngineSupportedRenderer(eEngineSupportedRenderer::kOpenGLES_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest:
		{
			return Translate_EngineSupportedRenderer(
				eEngineSupportedRenderer::kVulkan_Latest);
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
		{
			return KOTEK_TEXTU("OpenGL version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_DirectX_SpecifiedByUser:
		{
			return KOTEK_TEXTU("DirectX version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
		{
			return KOTEK_TEXTU("Vulkan version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_OpenGLES_SpecifiedByUser:
		{
			return KOTEK_TEXTU("OpenGL ES version is specified by user");
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Software:
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
			kEngine_Render_Renderer_ANGLE_Feature_Desktop_GL:
		{
			return KOTEK_TEXTU("Desktop GL");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_DirectX_9:
		{
			return KOTEK_TEXTU("DirectX 9");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_DirectX_11:
		{
			return KOTEK_TEXTU("DirectX 11");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Vulkan:
		{
			return KOTEK_TEXTU("Vulkan");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_GL_ES:
		{
			return KOTEK_TEXTU("GL ES");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Metal:
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
		case eEngineFeatureWindow::kEngine_Window_Borderless:
		{
			return KOTEK_TEXTU("Borderless");
		}
		case eEngineFeatureWindow::kEngine_Window_FullScreen:
		{
			return KOTEK_TEXTU("FullScreen");
		}
		case eEngineFeatureWindow::kEngine_Window_Windowed:
		{
			return KOTEK_TEXTU("Windowed");
		}
		case eEngineFeatureWindow::kNone:
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
		eEngineFeatureRenderer result{eEngineFeatureRenderer::kNone};

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
				kEngine_Render_Renderer_OpenGLES_SpecifiedByUser;
		}
		else if (renderer_name == KOTEK_TEXTU("software") ||
			renderer_name == KOTEK_TEXTU("sw"))
		{
			result = eEngineFeatureRenderer::kEngine_Render_Renderer_Software;
		}
		else if (renderer_name == KOTEK_TEXTU("directx") ||
			renderer_name == KOTEK_TEXTU("dx"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Render_Renderer_DirectX_SpecifiedByUser;
		}
		else if (renderer_name == KOTEK_TEXTU("vulkan") ||
			renderer_name == KOTEK_TEXTU("vk"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Render_Renderer_Vulkan_SpecifiedByUser;
		}
		else if (renderer_name == KOTEK_TEXTU("opengl") ||
			renderer_name == KOTEK_TEXTU("gl"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Render_Renderer_OpenGL_SpecifiedByUser;
		}

		return result;
	}
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
