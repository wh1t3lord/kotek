#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include "kotek_console.h"
#include "kotek_dynamic_library.h"
#include "kotek_filesystem.h"
#include "kotek_input.h"
#include "kotek_profiler.h"
#include "kotek_resource_manager.h"
#include "kotek_std.h"

namespace Kotek
{
	namespace Core
	{
		enum class eEngineFeature : ktk::enum_base_t
		{
			kEngine_Window_Windowed,
			kEngine_Window_Borderless,
			kEngine_Window_FullScreen,
			kEngine_Render_Feature_MSAA,
			kEngine_Render_Feature_VSYNC,
			kEngine_Render_Renderer_DirectX_7,
			kEngine_Render_Renderer_DirectX_8,
			kEngine_Render_Renderer_DirectX_9,
			kEngine_Render_Renderer_DirectX_10,
			kEngine_Render_Renderer_DirectX_11,
			kEngine_Render_Renderer_DirectX_12,
			kEngine_Render_Renderer_OpenGL3_3,
			kEngine_Render_Renderer_OpenGL4_6,
			kEngine_Render_Renderer_Vulkan,
			kEngine_Render_Renderer_Software,
			kEngine_Feature_Unknown = -1
		};

		constexpr const ktk::tchar* kRenderName_OpenGL = KOTEK_TEXT("OpenGL");
		constexpr const ktk::tchar* kRenderName_Vulkan = KOTEK_TEXT("Vulkan");
		constexpr const ktk::tchar* kRenderName_DirectX12 =
			KOTEK_TEXT("DirectX12");
		constexpr const ktk::tchar* kRenderName_DirectX11 =
			KOTEK_TEXT("DirectX11");
		constexpr const ktk::tchar* kRenderName_DirectX9 =
			KOTEK_TEXT("DirectX9");
		constexpr const ktk::tchar* kRenderName_Software =
			KOTEK_TEXT("Software");

		class ktkMainManager
		{
		public:
			ktkMainManager(int argc, char** argv);
			ktkMainManager(void) = delete;

			~ktkMainManager(void);

			void initialize(int argc, char** argv);
			void shutdown(void);

			ktkProfiler* GetProfiler(void) const noexcept;

			ktkFileSystem* GetFileSystem(void) const noexcept;
			ktkInput* GetInput(void) const noexcept;

			ktkIGameManager* GetGameManager(void) const noexcept;
			void SetGameManager(ktkIGameManager* p_game_manager) noexcept;

			ktkIResourceManager* GetResourceManager(void) const noexcept;
			void SetResourceManager(ktkIResourceManager* p_manager) noexcept;

			ktkIRenderDevice* getRenderDevice(void) const noexcept;

			void setRenderDevice(
				ktk::shared_ptr<ktkIRenderDevice> pointer) noexcept;

			// @ returns user's resource manager
			ktkIRenderResourceManager* GetRenderResourceManager(
				void) const noexcept;

			void SetRenderResourceManager(
				ktk::shared_ptr<ktkIRenderResourceManager> pointer) noexcept;

			ktkIRenderSwapchain* getRenderSwapchainManager(void) const noexcept;

			void setRenderSwapchainManager(
				ktk::shared_ptr<ktkIRenderSwapchain> pointer) noexcept;

			bool IsFeatureEnabled(eEngineFeature id) const noexcept;

			void SetFeatureStatus(
				eEngineFeature id, bool status = true) noexcept;

			ktk::string GetRenderName(void) const noexcept;
			eEngineFeature GetRenderFeature(void) const noexcept;

			bool IsCurrentRenderLegacy(void) const noexcept;

			/// <summary>
			/// means Vulkan or DirectX 12
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			bool IsCurrentRenderModern(void) const noexcept;

			int getARGC(void) const noexcept;
			char** getARGV(void) const noexcept;

			bool IsContainsConsoleCommandLineArgument(
				const ktk::string& your_argument) const noexcept;

			bool LoadUserGameLibrary(const ktk::string& library_name) noexcept;
			void UnLoadUserGameLibrary(void) noexcept;

			const ktk::dll::shared_library& GetUserLibrary(void) const noexcept;

			// @ Uses in while so true application is working if false it
			// doesn't
			bool IsApplicationWorking(void) const noexcept;

			void SetApplicationWorking(bool status) noexcept;

		private:
			bool IsFeatureRender(eEngineFeature feature) const noexcept;

		private:
			ktk::mt::atomic<bool> m_is_running;
			int m_argc;
			kotek_i_renderer* m_p_manager_renderer;
			ktkIGameManager* m_p_game_manager;
			ktkIResourceManager* m_p_resource_manager;
			char** m_argv;
			ktk::vector<ktk::string> m_parsed_command_line_arguments;
			ktk::unordered_map<eEngineFeature, bool> m_engine_flags;
			ktk::shared_ptr<ktkIFileSystem> m_manager_filesystem;
			ktk::shared_ptr<ktkIInput> m_manager_input;
			ktk::shared_ptr<ktkIRenderDevice> m_manager_render_device;
			ktk::shared_ptr<ktkIRenderResourceManager>
				m_manager_render_resource;
			ktk::shared_ptr<ktkIRenderGraph> m_manager_render_graph;
			ktk::shared_ptr<ktkIRenderSwapchain> m_manager_swapchain;
			ktk::shared_ptr<ktkProfiler> m_manager_profiler;
			ktk::dll::shared_library m_user_dll;
		};
	} // namespace Core
} // namespace Kotek
