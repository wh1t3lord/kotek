#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

namespace Kotek
{
	namespace Core
	{
		// TODO: add helper namespace for translating this enum
		enum class eFolderIndex : ktk::enum_base_t
		{
			kFolderIndex_Root,
			kFolderIndex_Gamedata,
			kFolderIndex_Configs,
			kFolderIndex_Scripts,
			kFolderIndex_Textures,
			kFolderIndex_Shaders,
			kFolderIndex_Models,
			kFolderIndex_Sound,
			kFolderIndex_UserTests,
			kFolderIndex_UserData
		};

		enum class eResourceLoadingType : ktk::enum_base_t
		{
			kText,
			kTexture,
			kModel,
			kSound,
			kVideo,
			kDLL,
			kAutoDetect,
			kUnknown = -1
		};

		enum class eResourceLoadingPolicy : ktk::enum_base_t
		{
			kAsync,
			kSync
		};

		enum class eResourceCachingPolicy : ktk::enum_base_t
		{
			// Returns constructed object
			kCache,

			// TODO: think about it and do we need really implement this?
			// Using temporary instances that resource manager has
			kWithoutCache
		};

		enum class eEngineFeature : ktk::enum_base_t
		{
			kEngine_Window_Windowed,
			kEngine_Window_Borderless,
			kEngine_Window_FullScreen,

			kEngine_Render_Feature_MSAA,
			kEngine_Render_Feature_VSYNC,

			// don't use, internal usage only
			kEngine_Render_Renderer_DirectX,

			kEngine_Render_Renderer_DirectX_7,
			kEngine_Render_Renderer_DirectX_8,
			kEngine_Render_Renderer_DirectX_9,
			kEngine_Render_Renderer_DirectX_10,
			kEngine_Render_Renderer_DirectX_11,
			kEngine_Render_Renderer_DirectX_12,

			// don't use, internal usage only
			kEngine_Render_Renderer_OpenGL,

			kEngine_Render_Renderer_OpenGL1_0,
			kEngine_Render_Renderer_OpenGL2_0,
			kEngine_Render_Renderer_OpenGL3_3,
			kEngine_Render_Renderer_OpenGL4_6,

			kEngine_Render_Renderer_Vulkan,

			kEngine_Render_Renderer_Software,

			kEngine_Feature_Unknown = -1
		};

		enum class ktkConsoleCommandIndex : ktk::enum_base_t
		{
			// (int width, int height)
			kConsoleCommand_Resize,

			kConsoleCommand_App_Close,
			kConsoleCommand_App_Hide,
			kConsoleCommand_App_Show,
			kConsoleCommand_Render_UploadAllResourcesToGPU
		};
	} // namespace Core
} // namespace Kotek