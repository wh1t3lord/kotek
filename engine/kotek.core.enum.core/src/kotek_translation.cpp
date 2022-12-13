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
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX:
		{
			return "DirectX";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_10:
		{
			return "DirectX 10";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_11:
		{
			return "DirectX 11";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_12:
		{
			return "DirectX 12";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_7:
		{
			return "DirectX 7";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_8:
		{
			return "DirectX 8";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_9:
		{

			return "DirectX 9";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL:
		{
			return "OpenGL";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL1_0:
		{
			return "OpenGL 1.0";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL2_0:
		{
			return "OpenGL 2.0";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL3_3:
		{
			return "OpenGL 3.3";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL4_6:
		{
			return "OpenGL 4.6";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Software:
		{
			return "Software";
		}
		case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan:
		{
			return "Vulkan";
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
		return ktk::string();
	}

	ktk::string Translate_EngineFeatureWindow(eEngineFeatureWindow type)
	{
		return ktk::string();
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