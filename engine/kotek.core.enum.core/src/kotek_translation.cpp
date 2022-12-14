#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace helper
{
	ktk::string Translate_FolderIndex(eFolderIndex type)
	{
		switch (type)
		{
		case eFolderIndex::kFolderIndex_Root:
		{
			return "Root";
		}
		case eFolderIndex::kFolderIndex_Gamedata:
		{
			return "Gamedata";
		}
		case eFolderIndex::kFolderIndex_Configs:
		{
			return "Configs";
		}
		case eFolderIndex::kFolderIndex_Models:
		{
			return "Models";
		}
		case eFolderIndex::kFolderIndex_Scripts:
		{
			return "Scripts";
		}
		case eFolderIndex::kFolderIndex_Shaders:
		{
			return "Shaders";
		}
		case eFolderIndex::kFolderIndex_Sound:
		{
			return "Sound";
		}
		case eFolderIndex::kFolderIndex_Textures:
		{
			return "Textures";
		}
		case eFolderIndex::kFolderIndex_UserData:
		{
			return "UserData";
		}
		case eFolderIndex::kFolderIndex_UserTests:
		{
			return "UserTests";
		}
		case eFolderIndex::kFolderIndex_UserData_ShaderCache:
		{
			return "UserData_ShaderCache";
		}
		case eFolderIndex::kFolderIndex_Shaders_GLSL:
		{
			return "Shaders_GLSL";
		}
		case eFolderIndex::kFolderIndex_Shaders_HLSL:
		{
			return "Shaders_HLSL";
		}
		case eFolderIndex::kFolderindex_Shaders_SPV:
		{
			return "Shaders_SPV";
		}
		case eFolderIndex::kFolderIndex_Shaders_WEBGPU:
		{
			return "Shaders_WEBGPU";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_FOLDER_INDEX";
		}
		}
	}

	ktk::string Translate_EngineFeature(eEngineFeature type)
	{
		switch (type)
		{
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE";
		}
		}
	}

	ktk::string Translate_EngineFeatureRender(eEngineFeatureRender type)
	{
		switch (type)
		{
		case eEngineFeatureRender::kEngine_Render_Feature_MSAA:
		{
			return "MSAA";
		}
		case eEngineFeatureRender::kEngine_Render_Feature_VSYNC:
		{
			return "VSYNC";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDER";
		}
		}
	}

	ktk::string Translate_EngineFeatureRenderer(eEngineFeatureRenderer type)
	{
		switch (type)
		{
		case eEngineFeatureRenderer::kEngine_Render_Renderer_ANGLE:
		{
			return "ANGLE";
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
			return "OpenGL version is specified by user";
		}
		case eEngineFeatureRenderer::
			kEngine_Render_Renderer_DirectX_SpecifiedByUser:
		{
			return "DirectX version is specified by user";
		}
		case eEngineFeatureRenderer::
		kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
		{
			return "Vulkan version is specified by user";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Software:
		{
			return "Software";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDERER";
		}
		}
	}

	ktk::string Translate_EngineFeatureRendererANGLE(
		eEngineFeatureRendererANGLE type)
	{
		switch (type)
		{
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Desktop_GL:
		{
			return "Desktop GL";
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_DirectX_9:
		{
			return "DirectX 9";
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_DirectX_11:
		{
			return "DirectX 11";
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Vulkan:
		{
			return "Vulkan";
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_GL_ES:
		{
			return "GL ES";
		}
		case eEngineFeatureRendererANGLE::
			kEngine_Render_Renderer_ANGLE_Feature_Metal:
		{
			return "Metal";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE_RENDERER_ANGLE";
		}
		}
	}

	ktk::string Translate_EngineFeatureSDK(eEngineFeatureSDK type)
	{
		switch (type)
		{
		case eEngineFeatureSDK::kEngine_Feature_SDK:
		{
			// TODO: add determing what GUI kit is used like wxWidgets, Qt, MFC
			// and etc
			return "SDK (not ImGui Mode)";
		}
		case eEngineFeatureSDK::kEngine_Feature_SDK_ImGui:
		{
			return "SDK (ImGui Mode)";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE_SDK";
		}
		}
	}

	ktk::string Translate_EngineFeatureWindow(eEngineFeatureWindow type)
	{
		switch (type)
		{
		case eEngineFeatureWindow::kEngine_Window_Borderless:
		{
			return "Borderless";
		}
		case eEngineFeatureWindow::kEngine_Window_FullScreen:
		{
			return "FullScreen";
		}
		case eEngineFeatureWindow::kEngine_Window_Windowed:
		{
			return "Windowed";
		}
		case eEngineFeatureWindow::kNone:
		{
			return "None";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE_WINDOW";
		}
		}
	}

	ktk::string Translate_EngineSupportedDirectXVersion(
		eEngineSupportedDirectXVersion type)
	{
		switch (type)
		{
		case eEngineSupportedDirectXVersion::kDirectX_7:
		{
			return "DirectX 7";
		}
		case eEngineSupportedDirectXVersion::kDirectX_8:
		{
			return "DirectX 8";
		}
		case eEngineSupportedDirectXVersion::kDirectX_9:
		{
			return "DirectX 9";
		}
		case eEngineSupportedDirectXVersion::kDirectX_10:
		{
			return "DirectX 10";
		}
		case eEngineSupportedDirectXVersion::kDirectX_11:
		{
			return "DirectX 11";
		}
		case eEngineSupportedDirectXVersion::kDirectX_12:
		{
			return "DirectX 12";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_DIRECTX_VERSION";
		}
		}
	}

	ktk::string Translate_EngineSupportedOpenGLVersion(
		eEngineSupportedOpenGLVersion type)
	{
		switch (type)
		{
		case eEngineSupportedOpenGLVersion::kOpenGL_1_0:
		{
			return "OpenGL 1.0";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_1:
		{
			return "OpenGL 1.1";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_2:
		{
			return "OpenGL 1.2";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_3:
		{
			return "OpenGL 1.3";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_4:
		{
			return "OpenGL 1.4";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_1_5:
		{
			return "OpenGL 1.5";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_2_0:
		{
			return "OpenGL 2.0";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_2_1:
		{
			return "OpenGL 2.1";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_0:
		{
			return "OpenGL 3.0";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_1:
		{
			return "OpenGL 3.1";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_2:
		{
			return "OpenGL 3.2";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_3_3:
		{
			return "OpenGL 3.3";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_0:
		{
			return "OpenGL 4.0";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_1:
		{
			return "OpenGL 4.1";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_2:
		{
			return "OpenGL 4.2";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_3:
		{
			return "OpenGL 4.3";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_4:
		{
			return "OpenGL 4.4";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_5:
		{
			return "OpenGL 4.5";
		}
		case eEngineSupportedOpenGLVersion::kOpenGL_4_6:
		{
			return "OpenGL 4.6";
		}
		case eEngineSupportedOpenGLVersion::kUnknown:
		{
			return "Unknown";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_OPENGL_VERSION";
		}
		}
	}

	ktk::string Translate_EngineSupportedVulkanVersion(
		eEngineSupportedVulkanVersion type)
	{
		switch (type)
		{
		case eEngineSupportedVulkanVersion::kVulkan_1_0:
		{
			return "Vulkan 1.0";
		}
		case eEngineSupportedVulkanVersion::kVulkan_1_1:
		{
			return "Vulkan 1.1";
		}
		case eEngineSupportedVulkanVersion::kVulkan_1_2:
		{
			return "Vulkan 1.2";
		}
		case eEngineSupportedVulkanVersion::kVulkan_1_3:
		{
			return "Vulkan 1.3";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_SUPPORTED_VULKAN_VERSION";
		}
		}
	}

	ktk::string Translate_ResourceLoadingType(eResourceLoadingType type)
	{
		switch (type)
		{
		case eResourceLoadingType::kAutoDetect:
		{
			return "AutoDetect";
		}
		case eResourceLoadingType::kDLL:
		{
			return "DLL (some programming module)";
		}
		case eResourceLoadingType::kModel:
		{
			return "Model";
		}
		case eResourceLoadingType::kSound:
		{
			return "Sound";
		}
		case eResourceLoadingType::kText:
		{
			return "Text";
		}
		case eResourceLoadingType::kTexture:
		{
			return "Texture";
		}
		case eResourceLoadingType::kUnknown:
		{
			return "Unknown";
		}
		case eResourceLoadingType::kVideo:
		{
			return "Video";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_RESOURCE_LOADING_TYPE";
		}
		}
	}

	ktk::string Translate_ResourceLoadingPolicy(eResourceLoadingPolicy type)
	{
		switch (type)
		{
		case eResourceLoadingPolicy::kAsync:
		{
			return "Async";
		}
		case eResourceLoadingPolicy::kSync:
		{
			return "Sync";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_RESOURCE_LOADING_POLICY";
		}
		}
	}

	ktk::string Translate_ResourceCachingPolicy(eResourceCachingPolicy type)
	{
		switch (type)
		{
		case eResourceCachingPolicy::kCache:
		{
			return "Cache";
		}
		case eResourceCachingPolicy::kWithoutCache:
		{
			return "WithoutCache";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_RESOURCE_CACHING_POLICY";
		}
		}
	}

	ktk::string Translate_ConsoleCommandIndex(eConsoleCommandIndex type)
	{
		switch (type)
		{
		case eConsoleCommandIndex::kConsoleCommand_App_Close:
		{
			return "App_Close";
		}
		case eConsoleCommandIndex::kConsoleCommand_App_Hide:
		{
			return "App_Hide";
		}
		case eConsoleCommandIndex::kConsoleCommand_App_Show:
		{
			return "App_Show";
		}
		case eConsoleCommandIndex::
			kConsoleCommand_Render_UploadAllResourcesToGPU:
		{
			return "Render_UploadAllResourcesToGPU";
		}
		case eConsoleCommandIndex::kConsoleCommand_Resize:
		{
			return "Resize";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_CONSOLE_COMMAND_INDEX";
		}
		}
	}
} // namespace helper

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK