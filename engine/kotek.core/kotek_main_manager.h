#pragma once

#include "../kotek.core.api/kotek_api.h"
#include "kotek_console.h"
#include "kotek_dynamic_library.h"
#include "kotek_filesystem.h"
#include "kotek_input.h"
#include "kotek_profiler.h"
#include "kotek_std.h"
#include "kotek_resource_manager.h"

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
			kEngine_Render_Renderer_Vulkan,
			kEngine_Render_Renderer_DirectX_9,
			kEngine_Render_Renderer_DirectX_11,
			kEngine_Render_Renderer_DirectX_12,
			kEngine_Render_Renderer_OpenGL,
			kEngine_Render_Renderer_Software
		};

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

			int getARGC(void) const noexcept;
			char** getARGV(void) const noexcept;

			bool IsContainsConsoleCommandLineArgument(
				const ktk::string& your_argument) const noexcept;

			bool LoadUserGameLibrary(const ktk::string& library_name) noexcept;
			void UnLoadUserGameLibrary(void) noexcept;
			
			const ktk::dll::shared_library& GetUserLibrary(void) const noexcept;

			// @ Uses in while so true application is working if false it doesn't
			bool IsApplicationWorking(void) const noexcept;

			void SetApplicationWorking(bool status) noexcept;

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
