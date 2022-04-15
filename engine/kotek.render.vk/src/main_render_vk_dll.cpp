#include <kotek.core/include/kotek_main_manager.h>
#include <kotek.core/include/kotek_std.h>
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

			main_manager.SetFeatureStatus(
				Core::eEngineFeature::kEngine_Render_Renderer_Vulkan);

			auto p_render_manager_device =
				std::make_shared<vk::ktkRenderDevice>();
			main_manager.setRenderDevice(p_render_manager_device);

			auto p_render_manager_swapchain =
				std::make_shared<vk::ktkRenderSwapchain>();
			main_manager.setRenderSwapchainManager(p_render_manager_swapchain);

			auto p_render_manager_render_resource =
				std::make_shared<vk::ktkRenderResourceManager>(
					p_render_manager_device.get(), &main_manager);
			main_manager.SetRenderResourceManager(
				p_render_manager_render_resource);



			p_render_manager_device->Initialize(main_manager);

			// TODO: load from user settings
			p_render_manager_device->SetWidth(
				main_manager.GetGameManager()->GetWindowWidth());
			p_render_manager_device->SetHeight(
				main_manager.GetGameManager()->GetWindowHeight());

			p_render_manager_swapchain->Initialize(
				p_render_manager_device.get());

			p_render_manager_render_resource->initialize(
				p_render_manager_device.get(),
				p_render_manager_swapchain.get());

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

			return true;
		}
	} // namespace Render
} // namespace Kotek