#include "../include/kotek_main_manager.h"

namespace Kotek
{
	namespace Core
	{
		ktkMainManager::ktkMainManager() :
			m_p_manager_config{}, m_p_manager_renderer{}, m_p_game_manager{},
			m_p_resource_manager{}, m_p_manager_filesystem{},
			m_p_manager_input{}, m_p_manager_render_device{},
			m_p_manager_render_resource{}, m_p_manager_render_graph{},
			m_p_manager_swapchain{}, m_p_manager_profiler{}
		{
		}

		ktkMainManager::~ktkMainManager(void) { }

		ktkIProfiler* ktkMainManager::GetProfiler(void) const noexcept
		{
			return this->m_p_manager_profiler;
		}

		ktkIFileSystem* ktkMainManager::GetFileSystem(void) const noexcept
		{
			return this->m_p_manager_filesystem;
		}

		ktkIInput* ktkMainManager::GetInput(void) const noexcept
		{
			return this->m_p_manager_input;
		}

		ktkIGameManager* ktkMainManager::GetGameManager(void) const noexcept
		{
			return this->m_p_game_manager;
		}

		void ktkMainManager::SetGameManager(
			ktkIGameManager* p_game_manager) noexcept
		{
			this->m_p_game_manager = p_game_manager;
		}

		ktkIResourceManager* ktkMainManager::GetResourceManager(
			void) const noexcept
		{
			return this->m_p_resource_manager;
		}

		void ktkMainManager::SetResourceManager(
			ktkIResourceManager* p_manager) noexcept
		{
			this->m_p_resource_manager = p_manager;
		}

		ktkIRenderDevice* ktkMainManager::getRenderDevice(void) const noexcept
		{
			return this->m_p_manager_render_device;
		}

		void ktkMainManager::setRenderDevice(ktkIRenderDevice* pointer) noexcept
		{
			this->m_p_manager_render_device = pointer;
		}

		ktkIRenderResourceManager* ktkMainManager::GetRenderResourceManager(
			void) const noexcept
		{
			return this->m_p_manager_render_resource;
		}

		void ktkMainManager::SetRenderResourceManager(
			ktkIRenderResourceManager* pointer) noexcept
		{
			this->m_p_manager_render_resource = pointer;
		}

		ktkIRenderSwapchain* ktkMainManager::getRenderSwapchainManager(
			void) const noexcept
		{
			return this->m_p_manager_swapchain;
		}

		void ktkMainManager::setRenderSwapchainManager(
			ktkIRenderSwapchain* pointer) noexcept
		{
			this->m_p_manager_swapchain = pointer;
		}

		void ktkMainManager::Initialize(int argc, char** argv) 
		{ 
			if (this->m_p_manager_config) 
			{
				this->m_p_manager_config->SetARGC(argc);
				this->m_p_manager_config->SetARGV(argv);
			}
		}

	} // namespace Core
} // namespace Kotek
