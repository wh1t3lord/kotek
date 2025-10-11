#include "../include/kotek_render_device.h"
#include "../include/kotek_render_graph.h"
#include "../include/kotek_render_imgui_manager.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_swapchain.h"
#include "../include/kotek_render_vk.h"

namespace Kotek
{
	namespace Render
	{
		void registerCommands(kun_core ktkMainManager* p_main_manager) {}

#ifdef KOTEK_DEBUG
		// TODO: write separated test-applications for that kind of library
		void registerAllTests()
		{
			/*
			            registerTests_ShaderManager_ForModule_Render_VK();
			            registerTests_Swapchain_ForModule_Render_VK();
			            registerTests_Device_ForModule_Render_VK();*/
		}
#endif

		bool InitializeModule_Render_VK(kun_core ktkMainManager* p_main_manager,
			kun_core eEngineSupportedRenderer version)
		{
			KOTEK_CPU_PROFILE();

			auto* p_engine_config = p_main_manager->Get_EngineConfig();

			p_engine_config->SetFeatureStatus(version, true);

			vk::ktkRenderDevice* p_render_manager_device =
				new vk::ktkRenderDevice(version);

			p_main_manager->setRenderDevice(p_render_manager_device);

			vk::ktkRenderSwapchain* p_render_manager_swapchain =
				new vk::ktkRenderSwapchain();
			p_main_manager->setRenderSwapchainManager(
				p_render_manager_swapchain);

			vk::ktkRenderResourceManager* p_render_manager_render_resource =
				new vk::ktkRenderResourceManager(
					p_render_manager_device, p_main_manager);
			p_main_manager->SetRenderResourceManager(
				p_render_manager_render_resource);

			p_main_manager->Get_WindowManager()->Get_ActiveWindow()->Initialize(
				version, p_engine_config->GetEngineFeatureRendererVendor());

			p_render_manager_device->Initialize(p_main_manager);

			// TODO: load from user settings
			p_render_manager_device->SetWidth(
				p_main_manager->Get_WindowManager()->ActiveWindow_GetWidth());
			p_render_manager_device->SetHeight(
				p_main_manager->Get_WindowManager()->ActiveWindow_GetHeight());

			p_render_manager_swapchain->Initialize(p_render_manager_device);

			p_render_manager_render_resource->Initialize(
				p_render_manager_device, p_render_manager_swapchain);

			KOTEK_MESSAGE("render module is initialized");

			registerCommands(p_main_manager);

			return true;
		}

		bool ShutdownModule_Render_VK(kun_core ktkMainManager* p_main_manager)
		{
			p_main_manager->getRenderDevice()->GPUFlush();

			p_main_manager->getRenderSwapchainManager()->Shutdown(
				p_main_manager->getRenderDevice());
			p_main_manager->GetRenderResourceManager()->Shutdown(
				p_main_manager->getRenderDevice());

			kun_core ktkIGameManager* p_game_manager =
				p_main_manager->GetGameManager();
			if (p_game_manager)
			{
				auto* p_renderer = p_game_manager->GetRenderer();

				if (p_renderer)
				{
					p_renderer->Shutdown();
				}
			}

			p_main_manager->getRenderDevice()->Shutdown();

			vk::ktkRenderDevice* p_render_device =
				dynamic_cast<vk::ktkRenderDevice*>(
					p_main_manager->getRenderDevice());
			vk::ktkRenderResourceManager* p_render_resource_manager =
				dynamic_cast<vk::ktkRenderResourceManager*>(
					p_main_manager->GetRenderResourceManager());
			vk::ktkRenderSwapchain* p_render_swapchain =
				dynamic_cast<vk::ktkRenderSwapchain*>(
					p_main_manager->getRenderSwapchainManager());

			KOTEK_ASSERT(p_render_device,
				"you must get a valid point of vk::ktkRenderDevice (otherwise "
				"it is impossible situation and something went really wrong)");
			KOTEK_ASSERT(p_render_resource_manager,
				"you must get a valid point of vk::ktkRenderResourceManager "
				"(otherwise it is impossible situation and something went "
				"really wrong)");
			KOTEK_ASSERT(p_render_swapchain,
				"you must get a valid point of vk::ktkRenderSwapchain "
				"(otherwise it is impossible situation and something went "
				"really wrong)");

			delete p_render_device;
			delete p_render_resource_manager;
			delete p_render_swapchain;

			p_main_manager->setRenderDevice(nullptr);
			p_main_manager->SetRenderResourceManager(nullptr);
			p_main_manager->setRenderSwapchainManager(nullptr);

			return true;
		}
	} // namespace Render
} // namespace Kotek