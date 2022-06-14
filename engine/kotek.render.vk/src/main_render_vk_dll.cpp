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
		void registerCommands(Core::ktkMainManager& main_manager) {}

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

		bool InitializeModule_Render_VK(Core::ktkMainManager& main_manager)
		{
			KOTEK_CPU_PROFILE();

			main_manager.Get_EngineConfig()->SetFeatureStatus(
				Core::eEngineFeature::kEngine_Render_Renderer_Vulkan, true);

			vk::ktkRenderDevice* p_render_manager_device =
				new vk::ktkRenderDevice();

			main_manager.setRenderDevice(p_render_manager_device);

			vk::ktkRenderSwapchain* p_render_manager_swapchain =
				new vk::ktkRenderSwapchain();
			main_manager.setRenderSwapchainManager(p_render_manager_swapchain);

			vk::ktkRenderResourceManager* p_render_manager_render_resource =
				new vk::ktkRenderResourceManager(
					p_render_manager_device, &main_manager);
			main_manager.SetRenderResourceManager(
				p_render_manager_render_resource);

			p_render_manager_device->Initialize(main_manager);

			// TODO: load from user settings
			p_render_manager_device->SetWidth(
				main_manager.GetGameManager()->GetWindowWidth());
			p_render_manager_device->SetHeight(
				main_manager.GetGameManager()->GetWindowHeight());

			p_render_manager_swapchain->Initialize(p_render_manager_device);

			p_render_manager_render_resource->initialize(
				p_render_manager_device, p_render_manager_swapchain);

			KOTEK_MESSAGE("render module is initialized");

			registerCommands(main_manager);

			return true;
		}

		bool ShutdownModule_Render_VK(Core::ktkMainManager& main_manager)
		{
			main_manager.getRenderDevice()->GPUFlush();

			main_manager.getRenderSwapchainManager()->Shutdown(
				main_manager.getRenderDevice());
			main_manager.GetRenderResourceManager()->shutdown(
				main_manager.getRenderDevice());
			main_manager.GetGameManager()->GetRenderer()->Shutdown();
			main_manager.getRenderDevice()->Shutdown();

			vk::ktkRenderDevice* p_render_device =
				dynamic_cast<vk::ktkRenderDevice*>(
					main_manager.getRenderDevice());
			vk::ktkRenderResourceManager* p_render_resource_manager =
				dynamic_cast<vk::ktkRenderResourceManager*>(
					main_manager.GetRenderResourceManager());
			vk::ktkRenderSwapchain* p_render_swapchain =
				dynamic_cast<vk::ktkRenderSwapchain*>(
					main_manager.getRenderSwapchainManager());

			KOTEK_ASSERT(p_render_device,
				"you must get a valid point of gl::ktkRenderDevice (otherwise "
				"it is impossible situation and something went really wrong)");
			KOTEK_ASSERT(p_render_resource_manager,
				"you must get a valid point of gl::ktkRenderResourceManager "
				"(otherwise it is impossible situation and something went "
				"really wrong)");
			KOTEK_ASSERT(p_render_swapchain,
				"you must get a valid point of gl::ktkRenderSwapchain "
				"(otherwise it is impossible situation and something went "
				"really wrong)");

			delete p_render_device;
			delete p_render_resource_manager;
			delete p_render_swapchain;

			main_manager.setRenderDevice(nullptr);
			main_manager.SetRenderResourceManager(nullptr);
			main_manager.setRenderSwapchainManager(nullptr);

			return true;
		}
	} // namespace Render
} // namespace Kotek