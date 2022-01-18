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
		enum class eEngineFeature : int
		{
			kEngineWindowed,
			kEngineRender_MSAA,
			kEngineRender_VSYNC,
			kEngineRender_Vulkan,
			kEngineRender_DirectX_9,
			kEngineRender_DirectX_11,
			kEngineRender_DirectX_12,
			kEngineRender_OpenGL,
			kEngineRender_Software
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

			ktkIRenderDevice* getRenderDevice(void) const noexcept;

			void setRenderDevice(
				ktk::shared_ptr<ktkIRenderDevice> pointer) noexcept;

			ktkIRenderResourceManager* getRenderResourceManager(
				void) const noexcept;

			void setRenderResourceManager(
				ktk::shared_ptr<ktkIRenderResourceManager>
					pointer) noexcept;

			ktkIRenderSwapchain* getRenderSwapchainManager(
				void) const noexcept;

			void setRenderSwapchainManager(
				ktk::shared_ptr<ktkIRenderSwapchain> pointer) noexcept;

			bool IsFeatureEnabled(eEngineFeature id) const noexcept;

			void SetFeatureStatus(
				eEngineFeature id, bool status = true) noexcept;

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
			ktk::unordered_map<eEngineFeature, bool> m_engine_flags;
			ktkDynamicLibrary m_dynamic_library_user_game;
			ktk::shared_ptr<ktkIFileSystem> m_manager_filesystem;
			ktk::shared_ptr<ktkIInput> m_manager_input;
			ktk::shared_ptr<ktkIRenderDevice> m_manager_render_device;
			ktk::shared_ptr<ktkIRenderResourceManager>
				m_manager_render_resource;
			ktk::shared_ptr<ktkIRenderGraph> m_manager_render_graph;
			ktk::shared_ptr<ktkIRenderSwapchain> m_manager_swapchain;
			ktk::shared_ptr<ktkProfiler> m_manager_profiler;
		};
	} // namespace Core
} // namespace Kotek
