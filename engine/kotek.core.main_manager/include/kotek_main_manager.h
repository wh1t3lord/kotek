#pragma once

#include <kotek.core.api/include/kotek_api.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager
		{
		public:
			ktkMainManager(void);
			~ktkMainManager(void);

			void Set_Profiler(ktkIProfiler* p_instance) noexcept;
			ktkIProfiler* GetProfiler(void) const noexcept;

			ktkIFileSystem* GetFileSystem(void) const noexcept;
			void Set_FileSystem(ktkIFileSystem* p_instance) noexcept;

			ktkIInput* GetInput(void) const noexcept;

			ktkIGameManager* GetGameManager(void) const noexcept;
			void SetGameManager(ktkIGameManager* p_game_manager) noexcept;

			ktkIResourceManager* GetResourceManager(void) const noexcept;
			void SetResourceManager(ktkIResourceManager* p_manager) noexcept;

			ktkIRenderDevice* getRenderDevice(void) const noexcept;

			void setRenderDevice(ktkIRenderDevice* pointer) noexcept;

			// @ returns user's resource manager
			ktkIRenderResourceManager* GetRenderResourceManager(
				void) const noexcept;

			void SetRenderResourceManager(
				ktkIRenderResourceManager* pointer) noexcept;

			ktkIRenderSwapchain* getRenderSwapchainManager(void) const noexcept;

			void setRenderSwapchainManager(
				ktkIRenderSwapchain* pointer) noexcept;

			ktkIEngineConfig* Get_EngineConfig(void) const noexcept;

		private:
			void Initialize(int argc, char** argv);

		private:
			ktkIEngineConfig* m_p_manager_config;
			kotek_i_renderer* m_p_manager_renderer;
			ktkIGameManager* m_p_game_manager;
			ktkIResourceManager* m_p_resource_manager;
			ktkIFileSystem* m_p_manager_filesystem;
			ktkIInput* m_p_manager_input;
			ktkIRenderDevice* m_p_manager_render_device;
			ktkIRenderResourceManager* m_p_manager_render_resource;
			ktkIRenderGraph* m_p_manager_render_graph;
			ktkIRenderSwapchain* m_p_manager_swapchain;
			ktkIProfiler* m_p_manager_profiler;
		};
	} // namespace Core
} // namespace Kotek
