#include "../include/kotek_render_device.h"
#include "../include/kotek_render_gl.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_GL3_3(Core::ktkMainManager* p_main_manager)
		{
			p_main_manager->Get_EngineConfig()->SetFeatureStatus(
				Core::eEngineFeature::kEngine_Render_Renderer_OpenGL3_3, true);

			gl3_3::ktkRenderDevice* p_render_device =
				new gl3_3::ktkRenderDevice();
			gl3_3::ktkRenderSwapchain* p_render_swapchain =
				new gl3_3::ktkRenderSwapchain();
			gl3_3::ktkRenderResourceManager* p_render_resource_manager =
				new gl3_3::ktkRenderResourceManager(
					p_render_device, p_main_manager);

			p_main_manager->setRenderDevice(p_render_device);
			p_main_manager->setRenderSwapchainManager(p_render_swapchain);
			p_main_manager->SetRenderResourceManager(p_render_resource_manager);

			p_render_device->Initialize(p_main_manager);

			// TODO: load from user settings
			p_render_device->SetWidth(
				p_main_manager->GetGameManager()->GetWindowWidth());
			p_render_device->SetHeight(
				p_main_manager->GetGameManager()->GetWindowHeight());

			p_render_swapchain->Initialize(p_render_device);
			p_render_resource_manager->initialize(
				p_render_device, p_render_swapchain);

			p_main_manager->GetResourceManager()->Set_RenderResourceManager(
				p_render_resource_manager);

			KOTEK_MESSAGE("render module is initialized");

			return true;
		}

		bool ShutdownModule_Render_GL3_3(Core::ktkMainManager* p_main_manager)
		{
			p_main_manager->getRenderDevice()->GPUFlush();

			p_main_manager->getRenderSwapchainManager()->Shutdown(
				p_main_manager->getRenderDevice());
			p_main_manager->GetRenderResourceManager()->shutdown(
				p_main_manager->getRenderDevice());

			Core::ktkIGameManager* p_game_manager =
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

			gl3_3::ktkRenderDevice* p_render_device =
				dynamic_cast<gl3_3::ktkRenderDevice*>(
					p_main_manager->getRenderDevice());
			gl3_3::ktkRenderResourceManager* p_render_resource_manager =
				dynamic_cast<gl3_3::ktkRenderResourceManager*>(
					p_main_manager->GetRenderResourceManager());
			gl3_3::ktkRenderSwapchain* p_render_swapchain =
				dynamic_cast<gl3_3::ktkRenderSwapchain*>(
					p_main_manager->getRenderSwapchainManager());

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

			p_main_manager->setRenderDevice(nullptr);
			p_main_manager->SetRenderResourceManager(nullptr);
			p_main_manager->setRenderSwapchainManager(nullptr);

			return true;
		}
	} // namespace Render
} // namespace Kotek