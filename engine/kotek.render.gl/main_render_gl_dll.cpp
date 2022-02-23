#include "../kotek.core/kotek_main_manager.h"
#include "kotek_render_device.h"
#include "kotek_render_gl.h"
#include "kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_GL(Core::ktkMainManager& main_manager)
		{
			main_manager.SetFeatureStatus(
				Core::eEngineFeature::kEngine_Render_Renderer_OpenGL);

			auto p_render_device = std::make_shared<gl::ktkRenderDevice>();
			auto p_render_swapchain =
				std::make_shared<gl::ktkRenderSwapchain>();

			main_manager.setRenderDevice(p_render_device);
			main_manager.setRenderSwapchainManager(p_render_swapchain);

			p_render_device->Initialize(main_manager);

			// TODO: load from user settings
			p_render_device->SetWidth(
				main_manager.GetGameManager()->GetWindowWidth());
			p_render_device->SetHeight(
				main_manager.GetGameManager()->GetWindowHeight());

			p_render_swapchain->Initialize(p_render_device.get());

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

			return true;
		}
	} // namespace Render
} // namespace Kotek