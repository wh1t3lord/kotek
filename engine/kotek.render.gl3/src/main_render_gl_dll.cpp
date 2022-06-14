#include "../include/kotek_render_device.h"
#include "../include/kotek_render_gl.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_GL(Core::ktkMainManager& main_manager)
		{
			main_manager.Get_EngineConfig()->SetFeatureStatus(
				Core::eEngineFeature::kEngine_Render_Renderer_OpenGL3_3, true);

			gl::ktkRenderDevice* p_render_device = new gl::ktkRenderDevice();
			gl::ktkRenderSwapchain* p_render_swapchain =
				new gl::ktkRenderSwapchain();
			gl::ktkRenderResourceManager* p_render_resource_manager =
				new gl::ktkRenderResourceManager(
					p_render_device, &main_manager);

			main_manager.setRenderDevice(p_render_device);
			main_manager.setRenderSwapchainManager(p_render_swapchain);
			main_manager.SetRenderResourceManager(p_render_resource_manager);

			p_render_device->Initialize(main_manager);

			// TODO: load from user settings
			p_render_device->SetWidth(
				main_manager.GetGameManager()->GetWindowWidth());
			p_render_device->SetHeight(
				main_manager.GetGameManager()->GetWindowHeight());

			p_render_swapchain->Initialize(p_render_device);
			p_render_resource_manager->initialize(
				p_render_device, p_render_swapchain);

			KOTEK_MESSAGE("render module is initialized");

			return true;
		}

		bool ShutdownModule_Render_GL(Core::ktkMainManager& main_manager)
		{
			main_manager.getRenderDevice()->GPUFlush();

			main_manager.getRenderSwapchainManager()->Shutdown(
				main_manager.getRenderDevice());
			main_manager.GetRenderResourceManager()->shutdown(
				main_manager.getRenderDevice());
			main_manager.GetGameManager()->GetRenderer()->Shutdown();
			main_manager.getRenderDevice()->Shutdown();

			gl::ktkRenderDevice* p_render_device =
				dynamic_cast<gl::ktkRenderDevice*>(
					main_manager.getRenderDevice());
			gl::ktkRenderResourceManager* p_render_resource_manager =
				dynamic_cast<gl::ktkRenderResourceManager*>(
					main_manager.GetRenderResourceManager());
			gl::ktkRenderSwapchain* p_render_swapchain =
				dynamic_cast<gl::ktkRenderSwapchain*>(
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