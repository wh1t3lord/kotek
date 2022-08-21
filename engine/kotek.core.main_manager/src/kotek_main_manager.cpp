#include "../include/kotek_main_manager.h"

namespace Kotek
{
	namespace Core
	{
		ktkMainManager::ktkMainManager(int argc, char** argv) :
			m_argc{argc}, m_argv{argv}, m_p_manager_config{},
			m_p_manager_renderer{}, m_p_game_manager{}, m_p_resource_manager{},
			m_p_manager_filesystem{}, m_p_manager_input{},
			m_p_manager_render_device{}, m_p_manager_render_resource{},
			m_p_manager_render_graph{}, m_p_manager_swapchain{},
			m_p_manager_profiler{}
		{
		}

		ktkMainManager::ktkMainManager() :
			m_argc{}, m_argv{}, m_p_manager_config{}, m_p_manager_renderer{},
			m_p_game_manager{}, m_p_resource_manager{},
			m_p_manager_filesystem{}, m_p_manager_input{},
			m_p_manager_render_device{}, m_p_manager_render_resource{},
			m_p_manager_render_graph{}, m_p_manager_swapchain{},
			m_p_manager_profiler{}
		{
		}

		ktkMainManager::~ktkMainManager(void) {}

		void ktkMainManager::Set_Profiler(ktkIProfiler* p_instance) noexcept
		{
			this->m_p_manager_profiler = p_instance;
		}

		ktkIProfiler* ktkMainManager::GetProfiler(void) const noexcept
		{
			return this->m_p_manager_profiler;
		}

		ktkIFileSystem* ktkMainManager::GetFileSystem(void) const noexcept
		{
			return this->m_p_manager_filesystem;
		}

		void ktkMainManager::Set_FileSystem(ktkIFileSystem* p_instance) noexcept
		{
			this->m_p_manager_filesystem = p_instance;
		}

		void ktkMainManager::Set_Input(ktkIInput* p_instance) noexcept
		{
			this->m_p_manager_input = p_instance;
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

		void ktkMainManager::Set_EngineConfig(
			ktkIEngineConfig* pointer) noexcept
		{
			this->m_p_manager_config = pointer;
		}

		ktkIEngineConfig* ktkMainManager::Get_EngineConfig(void) const noexcept
		{
			return this->m_p_manager_config;
		}

		ktkIWindow* ktkMainManager::Get_Window(void) const noexcept
		{
			return this->m_p_window;
		}

		void ktkMainManager::Set_Window(ktkIWindow* p_window) noexcept 
		{
			this->m_p_window = p_window;
		}

		void ktkMainManager::WindowManager_PollEvents()
		{
			this->m_p_window->PollEvents();
		}

		bool ktkMainManager::WindowManager_NeedToCloseTheActiveWindow()
		{
			return this->m_p_window->Is_NeedToClose();
		}

		void ktkMainManager::Initialize(void)
		{
			if (this->m_p_manager_config)
			{
				this->m_p_manager_config->SetARGC(this->m_argc);
				this->m_p_manager_config->SetARGV(this->m_argv);
			}
		}

		void ktkMainManager::Shutdown(void) {}

	} // namespace Core
} // namespace Kotek
