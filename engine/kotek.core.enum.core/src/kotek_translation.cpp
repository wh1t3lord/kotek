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
            return KOTEK_TEXT("Root");
		}
		case eFolderIndex::kFolderIndex_Gamedata:
		{
            return KOTEK_TEXT("Gamedata");
		}
		case eFolderIndex::kFolderIndex_Configs:
		{
            return KOTEK_TEXT("Configs");
		}
		case eFolderIndex::kFolderIndex_Models:
		{
            return KOTEK_TEXT("Models");
		}
		case eFolderIndex::kFolderIndex_Scripts:
		{
            return KOTEK_TEXT("Scripts");
		}
		case eFolderIndex::kFolderIndex_Shaders:
		{
            return KOTEK_TEXT("Shaders");
		}
		case eFolderIndex::kFolderIndex_Sounds:
		{
            return KOTEK_TEXT("Sounds");
		}
		case eFolderIndex::kFolderIndex_Textures:
		{
            return KOTEK_TEXT("Textures");
		}
		case eFolderIndex::kFolderIndex_Levels:
		{
            return KOTEK_TEXT("Levels");
		}
		case eFolderIndex::kFolderIndex_AI:
		{
            return KOTEK_TEXT("AI");
		}
		case eFolderIndex::kFolderIndex_UserData:
		{
            return KOTEK_TEXT("UserData");
		}
		case eFolderIndex::kFolderIndex_UserTests:
		{
            return KOTEK_TEXT("UserTests");
		}
		case eFolderIndex::kFolderIndex_UserData_ShaderCache:
		{
            return KOTEK_TEXT("UserData_ShaderCache");
		}
		case eFolderIndex::kFolderIndex_Shaders_GLSL:
		{
            return KOTEK_TEXT("Shaders_GLSL");
		}
		case eFolderIndex::kFolderIndex_Shaders_HLSL:
		{
            return KOTEK_TEXT("Shaders_HLSL");
		}
		case eFolderIndex::kFolderindex_Shaders_SPV:
		{
            return KOTEK_TEXT("Shaders_SPV");
		}
		case eFolderIndex::kFolderIndex_Shaders_WEBGPU:
		{
            return KOTEK_TEXT("Shaders_WEBGPU");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_FOLDER_INDEX");
		}
		}
	}

    ktk::cstring Translate_EngineFeature(eEngineFeature type)
	{
		switch (type)
		{
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_FEATURE");
		}
		}
	}

    ktk::cstring Translate_EngineFeatureRender(eEngineFeatureRender type)
	{
		switch (type)
		{
		case eEngineFeatureRender::kEngine_Render_Feature_MSAA:
		{
            return KOTEK_TEXT("MSAA");
		}
		case eEngineFeatureRender::kEngine_Render_Feature_VSYNC:
		{
            return KOTEK_TEXT("VSYNC");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDER");
		}
		}
	}

	// TODO: re implement that in order to detect all possible flags what this
	// flag has
    ktk::cstring Translate_EngineFeatureRenderer(eEngineFeatureRenderer type)
	{
		switch (type)
		{
		case eEngineFeatureRenderer::kEngine_Render_Renderer_ANGLE:
		{
            return KOTEK_TEXT("ANGLE");
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest:
		{
			return Translate_EngineSupportedDirectXVersion(
				eEngineSupportedDirectXVersion::kDirectX_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest:
		{
			return Translate_EngineSupportedOpenGLVersion(
				eEngineSupportedOpenGLVersion::kOpenGL_Latest);
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest:
		{
			return Translate_EngineSupportedVulkanVersion(
				eEngineSupportedVulkanVersion::kVulkan_Latest);
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
		{
            return KOTEK_TEXT("OpenGL version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_DirectX_SpecifiedByUser:
		{
            return KOTEK_TEXT("DirectX version is specified by user");
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
		{
            return KOTEK_TEXT("Vulkan version is specified by user");
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Software:
		{
            return KOTEK_TEXT("Software");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDERER");
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
            return KOTEK_TEXT("Desktop GL");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_DirectX_9:
		{
            return KOTEK_TEXT("DirectX 9");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_DirectX_11:
		{
            return KOTEK_TEXT("DirectX 11");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Vulkan:
		{
            return KOTEK_TEXT("Vulkan");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_GL_ES:
		{
            return KOTEK_TEXT("GL ES");
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Metal:
		{
            return KOTEK_TEXT("Metal");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDERER_ANGLE");
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
            return KOTEK_TEXT("SDK (not ImGui Mode)");
		}
		case eEngineFeatureSDK::kEngine_Feature_SDK_ImGui:
		{
            return KOTEK_TEXT("SDK (ImGui Mode)");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_FEATURE_SDK");
		}
		}
	}

    ktk::cstring Translate_EngineFeatureWindow(eEngineFeatureWindow type)
	{
		switch (type)
		{
		case eEngineFeatureWindow::kEngine_Window_Borderless:
		{
            return KOTEK_TEXT("Borderless");
		}
		case eEngineFeatureWindow::kEngine_Window_FullScreen:
		{
            return KOTEK_TEXT("FullScreen");
		}
		case eEngineFeatureWindow::kEngine_Window_Windowed:
		{
            return KOTEK_TEXT("Windowed");
		}
		case eEngineFeatureWindow::kNone:
		{
            return KOTEK_TEXT("None");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_FEATURE_WINDOW");
		}
		}
	}

    ktk::cstring Translate_EngineSupportedDirectXVersion(
		eEngineSupportedDirectXVersion type)
	{
		switch (type)
		{
		case eEngineSupportedDirectXVersion::kDirectX_7:
		{
            return KOTEK_TEXT("DirectX 7");
		}
		case eEngineSupportedDirectXVersion::kDirectX_8:
		{
            return KOTEK_TEXT("DirectX 8");
		}
		case eEngineSupportedDirectXVersion::kDirectX_9:
		{
            return KOTEK_TEXT("DirectX 9");
		}
		case eEngineSupportedDirectXVersion::kDirectX_10:
		{
            return KOTEK_TEXT("DirectX 10");
		}
		case eEngineSupportedDirectXVersion::kDirectX_11:
		{
            return KOTEK_TEXT("DirectX 11");
		}
		case eEngineSupportedDirectXVersion::kDirectX_12:
		{
            return KOTEK_TEXT("DirectX 12");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_DIRECTX_VERSION");
		}
		}
	}

    ktk::cstring Translate_EngineSupportedOpenGLVersion(
		eEngineSupportedOpenGLVersion type)
	{
		switch (type)
		{
		case eEngineSupportedOpenGLVersion::kOpenGL_1_0:
		{
            return KOTEK_TEXT("OpenGL 1.0");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_1:
		{
            return KOTEK_TEXT("OpenGL 1.1");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_2:
		{
            return KOTEK_TEXT("OpenGL 1.2");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_3:
		{
            return KOTEK_TEXT("OpenGL 1.3");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_4:
		{
            return KOTEK_TEXT("OpenGL 1.4");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_5:
		{
            return KOTEK_TEXT("OpenGL 1.5");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_2_0:
		{
            return KOTEK_TEXT("OpenGL 2.0");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_2_1:
		{
            return KOTEK_TEXT("OpenGL 2.1");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_0:
		{
            return KOTEK_TEXT("OpenGL 3.0");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_1:
		{
            return KOTEK_TEXT("OpenGL 3.1");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_2:
		{
            return KOTEK_TEXT("OpenGL 3.2");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_3:
		{
            return KOTEK_TEXT("OpenGL 3.3");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_0:
		{
            return KOTEK_TEXT("OpenGL 4.0");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_1:
		{
            return KOTEK_TEXT("OpenGL 4.1");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_2:
		{
            return KOTEK_TEXT("OpenGL 4.2");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_3:
		{
            return KOTEK_TEXT("OpenGL 4.3");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_4:
		{
            return KOTEK_TEXT("OpenGL 4.4");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_5:
		{
            return KOTEK_TEXT("OpenGL 4.5");
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_6:
		{
            return KOTEK_TEXT("OpenGL 4.6");
		}
		case eEngineSupportedOpenGLVersion::kUnknown:
		{
            return KOTEK_TEXT("Unknown");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_OPENGL_VERSION");
		}
		}
	}

    ktk::cstring Translate_EngineSupportedVulkanVersion(
		eEngineSupportedVulkanVersion type)
	{
		switch (type)
		{
		case eEngineSupportedVulkanVersion::kVulkan_1_0:
		{
            return KOTEK_TEXT("Vulkan 1.0");
		}
		case eEngineSupportedVulkanVersion::kVulkan_1_1:
		{
            return KOTEK_TEXT("Vulkan 1.1");
		}
		case eEngineSupportedVulkanVersion::kVulkan_1_2:
		{
            return KOTEK_TEXT("Vulkan 1.2");
		}
		case eEngineSupportedVulkanVersion::kVulkan_1_3:
		{
            return KOTEK_TEXT("Vulkan 1.3");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_VULKAN_VERSION");
		}
		}
	}

    ktk::cstring Translate_ResourceLoadingType(eResourceLoadingType type)
	{
		switch (type)
		{
		case eResourceLoadingType::kAutoDetect:
		{
            return KOTEK_TEXT("AutoDetect");
		}
		case eResourceLoadingType::kDLL:
		{
            return KOTEK_TEXT("DLL (some programming module)");
		}
		case eResourceLoadingType::kModel:
		{
            return KOTEK_TEXT("Model");
		}
		case eResourceLoadingType::kSound:
		{
            return KOTEK_TEXT("Sound");
		}
		case eResourceLoadingType::kText:
		{
            return KOTEK_TEXT("Text");
		}
		case eResourceLoadingType::kTexture:
		{
            return KOTEK_TEXT("Texture");
		}
		case eResourceLoadingType::kUnknown:
		{
            return KOTEK_TEXT("Unknown");
		}
		case eResourceLoadingType::kVideo:
		{
            return KOTEK_TEXT("Video");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_RESOURCE_LOADING_TYPE");
		}
		}
	}

    ktk::cstring Translate_ResourceLoadingPolicy(eResourceLoadingPolicy type)
	{
		switch (type)
		{
		case eResourceLoadingPolicy::kAsync:
		{
            return KOTEK_TEXT("Async");
		}
		case eResourceLoadingPolicy::kSync:
		{
            return KOTEK_TEXT("Sync");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_RESOURCE_LOADING_POLICY");
		}
		}
	}

    ktk::cstring Translate_ResourceCachingPolicy(eResourceCachingPolicy type)
	{
		switch (type)
		{
		case eResourceCachingPolicy::kCache:
		{
            return KOTEK_TEXT("Cache");
		}
		case eResourceCachingPolicy::kWithoutCache:
		{
            return KOTEK_TEXT("WithoutCache");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_RESOURCE_CACHING_POLICY");
		}
		}
	}

    ktk::cstring Translate_ConsoleCommandIndex(eConsoleCommandIndex type)
	{
		switch (type)
		{
		case eConsoleCommandIndex::kConsoleCommand_App_Close:
		{
            return KOTEK_TEXT("App_Close");
		}
		case eConsoleCommandIndex::kConsoleCommand_App_Hide:
		{
            return KOTEK_TEXT("App_Hide");
		}
		case eConsoleCommandIndex::kConsoleCommand_App_Show:
		{
            return KOTEK_TEXT("App_Show");
		}
		case eConsoleCommandIndex::
			kConsoleCommand_Render_UploadAllResourcesToGPU:
		{
            return KOTEK_TEXT("Render_UploadAllResourcesToGPU");
		}
		case eConsoleCommandIndex::kConsoleCommand_Resize:
		{
            return KOTEK_TEXT("Resize");
		}
		default:
		{
            return KOTEK_TEXT("UNDEFINED_ENUM_OF_CONSOLE_COMMAND_INDEX");
		}
		}
	}

	ktk::cstring Translate_InputType(eInputType type)
	{
		switch (type)
		{
		case eInputType::kInputType_Cursor:
		{
			return KOTEK_TEXT("InputType_Cursor");
		}
		case eInputType::kInputType_DisabledCursor:
		{
			return KOTEK_TEXT("InputType_DisabledCursor");
		}
		case eInputType::kInputType_HiddenCursor:
		{
			return KOTEK_TEXT("InputType_HiddenCursor");
		}
		default:
		{
			return KOTEK_TEXT("UNDEFINED_ENUM_OF_INPUT_TYPE");
		}
		}
	}

	eEngineSupportedOpenGLVersion
	TranslateFromStringToEnum_EngineSupportedOpenGLVersion(
        const ktk::cstring& version_name)
	{
		eEngineSupportedOpenGLVersion result{
			eEngineSupportedOpenGLVersion::kUnknown};

		if (version_name.empty())
			return result;

        if (version_name.size() != 3 && version_name != KOTEK_TEXT("Latest"))
			return result;

        if (version_name == KOTEK_TEXT("Latest"))
		{
			result = eEngineSupportedOpenGLVersion::kOpenGL_Latest;
			return result;
		}

		int major_version{};
		int minor_version{};

        major_version = ktk::lexical_cast<int>(version_name[0]);
        minor_version = ktk::lexical_cast<int>(version_name[2]);

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
				result = eEngineSupportedOpenGLVersion::kOpenGL_1_0;
				break;
			}
			case 1:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_1_1;
				break;
			}
			case 2:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_1_2;
				break;
			}
			case 3:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_1_3;
				break;
			}
			case 4:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_1_4;
				break;
			}
			case 5:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_1_5;
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
				result = eEngineSupportedOpenGLVersion::kOpenGL_2_0;
				break;
			}
			case 1:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_2_1;
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
				result = eEngineSupportedOpenGLVersion::kOpenGL_3_0;
				break;
			}
			case 1:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_3_1;
				break;
			}
			case 2:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_3_2;
				break;
			}
			case 3:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_3_3;
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
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_0;
				break;
			}
			case 1:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_1;
				break;
			}
			case 2:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_2;
				break;
			}
			case 3:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_3;
				break;
			}
			case 4:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_4;
				break;
			}
			case 5:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_5;
				break;
			}
			case 6:
			{
				result = eEngineSupportedOpenGLVersion::kOpenGL_4_6;
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
	}

	eEngineSupportedVulkanVersion
	TranslateFromStringToEnum_EngineSupportedVulkanVersion(
        const ktk::cstring& version_name)
	{
		eEngineSupportedVulkanVersion result{
			eEngineSupportedVulkanVersion::kUnknown};

		if (version_name.empty())
			return result;

        if (version_name.size() != 3 && version_name != KOTEK_TEXT("Latest"))
			return result;

        if (version_name == KOTEK_TEXT("Latest"))
		{
			result = eEngineSupportedVulkanVersion::kVulkan_Latest;
			return result;
		}

		int major_version{};
		int minor_version{};

        major_version = ktk::lexical_cast<int>(version_name[0]);
        minor_version = ktk::lexical_cast<int>(version_name[2]);

		switch (major_version)
		{
		case 1:
		{
			switch (minor_version)
			{
			case 0:
			{
				result = eEngineSupportedVulkanVersion::kVulkan_1_0;
				break;
			}
			case 1:
			{
				result = eEngineSupportedVulkanVersion::kVulkan_1_1;
				break;
			}
			case 2:
			{
				result = eEngineSupportedVulkanVersion::kVulkan_1_2;
				break;
			}
			case 3:
			{
				result = eEngineSupportedVulkanVersion::kVulkan_1_3;
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
	}

	eEngineSupportedDirectXVersion
	TranslateFromStringToEnum_EngineSupportedDirectXVersion(
        const ktk::cstring& version_name)
	{
		eEngineSupportedDirectXVersion result{
			eEngineSupportedDirectXVersion::kUnknown};

		if (version_name.empty())
			return result;

        if (version_name.size() > 2 && version_name != KOTEK_TEXT("Latest"))
			return result;

        if (version_name == KOTEK_TEXT("Latest"))
		{
			result = eEngineSupportedDirectXVersion::kDirectX_Latest;
			return result;
		}

		int version =
            ktk::lexical_cast<int>(version_name.c_str());

		switch (version)
		{
		case 7:
		{
			result = eEngineSupportedDirectXVersion::kDirectX_7;
			break;
		}
		case 8:
		{
			result = eEngineSupportedDirectXVersion::kDirectX_8;
			break;
		}
		case 9:
		{
			result = eEngineSupportedDirectXVersion::kDirectX_9;
			break;
		}
		case 10:
		{
			result = eEngineSupportedDirectXVersion::kDirectX_10;
			break;
		}
		case 11:
		{
			result = eEngineSupportedDirectXVersion::kDirectX_11;
			break;
		}
		case 12:
		{
			result = eEngineSupportedDirectXVersion::kDirectX_12;
			break;
		}
		}

		return result;
	}

	eEngineFeatureRenderer TranslateFromStringToEnum_EngineFeatureRenderer(
        const ktk::cstring& renderer_name)
	{
		eEngineFeatureRenderer result{eEngineFeatureRenderer::kNone};

		if (renderer_name.empty())
			return result;

        if (renderer_name == KOTEK_TEXT("ANGLE"))
		{
			result = eEngineFeatureRenderer::kEngine_Render_Renderer_ANGLE;
		}
        else if (renderer_name == KOTEK_TEXT("Software"))
		{
			result = eEngineFeatureRenderer::kEngine_Render_Renderer_Software;
		}
        else if (renderer_name == KOTEK_TEXT("DirectX"))
		{
			result = eEngineFeatureRenderer::
				kEngine_Render_Renderer_DirectX_SpecifiedByUser;
		}
        else if (renderer_name == KOTEK_TEXT("Vulkan"))
		{

			result = eEngineFeatureRenderer::
				kEngine_Render_Renderer_Vulkan_SpecifiedByUser;
		}
        else if (renderer_name == KOTEK_TEXT("OpenGL"))
		{

			result = eEngineFeatureRenderer::
				kEngine_Render_Renderer_OpenGL_SpecifiedByUser;
		}

		return result;
	}
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
