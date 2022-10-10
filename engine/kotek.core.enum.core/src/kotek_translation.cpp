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
		case eEngineFeature::kEngine_Feature_SDK:
		{
			return "SDK";
		}
		case eEngineFeature::kEngine_Feature_SDK_ImGui:
		{
			return "SDK_ImGui";
		}
		case eEngineFeature::kEngine_Feature_Unknown:
		{
			return "Unknown";
		}
		case eEngineFeature::kEngine_Render_Feature_MSAA:
		{
			return "MSAA";
		}
		case eEngineFeature::kEngine_Render_Feature_VSYNC:
		{
			return "VSYNC";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX:
		{
			return "DirectX (user can't use it)";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX_10:
		{
			return "DirectX 10";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX_11:
		{
			return "DirectX 11";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX_12:
		{
			return "DirectX 12";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX_7:
		{
			return "DirectX 7";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX_8:
		{
			return "DirectX 8";
		}
		case eEngineFeature::kEngine_Render_Renderer_DirectX_9:
		{
			return "DirectX 9";
		}
		case eEngineFeature::kEngine_Render_Renderer_OpenGL:
		{
			return "OpenGL";
		}
		case eEngineFeature::kEngine_Render_Renderer_OpenGL1_0:
		{
			return "OpenGL 1.0";
		}
		case eEngineFeature::kEngine_Render_Renderer_OpenGL2_0:
		{
			return "OpenGL 2.0";
		}
		case eEngineFeature::kEngine_Render_Renderer_OpenGL3_3:
		{
			return "OpenGL 3.3";
		}
		case eEngineFeature::kEngine_Render_Renderer_OpenGL4_6:
		{
			return "OpenGL 4.6";
		}
		case eEngineFeature::kEngine_Render_Renderer_Software:
		{
			return "Software";
		}
		case eEngineFeature::kEngine_Render_Renderer_Vulkan:
		{
			return "Vulkan";
		}
		case eEngineFeature::kEngine_Window_Borderless:
		{
			return "Window_Borderless";
		}
		case eEngineFeature::kEngine_Window_FullScreen:
		{
			return "Window_FullScreen";
		}
		case eEngineFeature::kEngine_Window_Windowed:
		{
			return "Window_Windowed";
		}
		default:
		{
			return "UNDEFINED_ENUM_OF_ENGINE_FEATURE";
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