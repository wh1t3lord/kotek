#pragma once

#include "../kotek.core.api/kotek_api.h"
#include "kotek_console.h"
#include "kotek_dynamic_library.h"
#include "kotek_filesystem.h"
#include "kotek_input.h"
#include "kotek_profiler.h"
#include "kotek_std.h"

namespace Kotek
{
	namespace Core
	{
		enum class engine_feature_index_t : int
		{
			kEngineWindowed,
			kEngineMSAA,
			kEngineVSYNC
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

			kotek_i_render_device* getRenderDevice(void) const noexcept;

			void setRenderDevice(
				ktk::shared_ptr<kotek_i_render_device> pointer) noexcept;

			kotek_i_render_resource_manager* getRenderResourceManager(
				void) const noexcept;

			void setRenderResourceManager(
				ktk::shared_ptr<kotek_i_render_resource_manager>
					pointer) noexcept;

			kotek_i_render_swapchain* getRenderSwapchainManager(
				void) const noexcept;

			void setRenderSwapchainManager(
				ktk::shared_ptr<kotek_i_render_swapchain> pointer) noexcept;

			bool isFeatureEnabled(engine_feature_index_t id) const noexcept;

			void setFeatureStatus(
				engine_feature_index_t id, bool status) noexcept;

			int getARGC(void) const noexcept;
			char** getARGV(void) const noexcept;

			void LoadDynamicLibraryUserGame(
				const ktk::string& library_name) noexcept;
			void UnLoadDynamicLibraryUserGame() noexcept;

#ifdef KOTEK_PLATFORM_WINDOWS
			FARPROC GetUserCallbackFromUserGameLibrary(
				const ktk::string& function_name) noexcept;
#elif KOTEK_PLATFORM_LINUX
#endif
			bool IsContainsConsoleCommandLineArgument(
				const ktk::string& your_argument) const noexcept;

		private:
			int m_argc;
			kotek_i_renderer* m_p_manager_renderer;
			ktkIGameManager* m_p_game_manager;
			char** m_argv;
			ktk::vector<ktk::string> m_parsed_command_line_arguments;
			ktk::unordered_map<engine_feature_index_t, bool> m_engine_flags;
			ktkDynamicLibrary m_dynamic_library_user_game;
			ktk::shared_ptr<ktkIFileSystem> m_manager_filesystem;
			ktk::shared_ptr<ktkIInput> m_manager_input;
			ktk::shared_ptr<kotek_i_render_device> m_manager_render_device;
			ktk::shared_ptr<kotek_i_render_resource_manager>
				m_manager_render_resource;
			ktk::shared_ptr<kotek_i_render_graph> m_manager_render_graph;
			ktk::shared_ptr<kotek_i_render_swapchain> m_manager_swapchain;
			ktk::shared_ptr<ktkProfiler> m_manager_profiler;
		};
	} // namespace Core
} // namespace Kotek
