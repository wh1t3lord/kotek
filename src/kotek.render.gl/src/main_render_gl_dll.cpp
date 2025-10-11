#include "../include/kotek_render_device.h"
#include "../include/kotek_render_gl.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_swapchain.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
bool InitializeModule_Render_GL(Core::ktkMainManager* p_main_manager,
	Core::eEngineSupportedRenderer version)
{
	auto* p_engine_config = p_main_manager->Get_EngineConfig();

	auto gl_version = version;
	p_engine_config->SetFeatureStatus(gl_version, true);
 

	gl::ktkRenderDevice* p_render_device = new gl::ktkRenderDevice();
	gl::ktkRenderSwapchain* p_render_swapchain = new gl::ktkRenderSwapchain();
	gl::ktkRenderResourceManager* p_render_resource_manager =
		new gl::ktkRenderResourceManager(p_render_device, p_main_manager);

	p_main_manager->setRenderDevice(p_render_device);
	p_main_manager->setRenderSwapchainManager(p_render_swapchain);
	p_main_manager->SetRenderResourceManager(p_render_resource_manager);

	p_main_manager->Get_WindowManager()->Get_ActiveWindow()->Initialize(
		gl_version, p_engine_config->GetEngineFeatureRendererVendor());

	p_render_device->Initialize(p_main_manager);

	// TODO: load from user settings
	p_render_device->SetWidth(
		p_main_manager->Get_WindowManager()->ActiveWindow_GetWidth());
	p_render_device->SetHeight(
		p_main_manager->Get_WindowManager()->ActiveWindow_GetHeight());

	p_render_swapchain->Initialize(p_render_device);
	p_render_resource_manager->Initialize(p_render_device, p_render_swapchain);

	KOTEK_MESSAGE("render module is initialized");

	return true;
}

bool ShutdownModule_Render_GL(Core::ktkMainManager* p_main_manager)
{
	p_main_manager->getRenderDevice()->GPUFlush();

	p_main_manager->getRenderSwapchainManager()->Shutdown(
		p_main_manager->getRenderDevice());
	p_main_manager->GetRenderResourceManager()->Shutdown(
		p_main_manager->getRenderDevice());

	Core::ktkIGameManager* p_game_manager = p_main_manager->GetGameManager();
	if (p_game_manager)
	{
		auto* p_renderer = p_game_manager->GetRenderer();

		if (p_renderer)
		{
			p_renderer->Shutdown();
		}
	}

	p_main_manager->getRenderDevice()->Shutdown();

	gl::ktkRenderDevice* p_render_device =
		dynamic_cast<gl::ktkRenderDevice*>(p_main_manager->getRenderDevice());
	gl::ktkRenderResourceManager* p_render_resource_manager =
		dynamic_cast<gl::ktkRenderResourceManager*>(
			p_main_manager->GetRenderResourceManager());
	gl::ktkRenderSwapchain* p_render_swapchain =
		dynamic_cast<gl::ktkRenderSwapchain*>(
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
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK