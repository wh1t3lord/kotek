#include "../include/kotek_render_angle_gles23.h"

#include "../include/kotek_render_device.h"
#include "../include/kotek_render_swapchain.h"
#include <kotek.render.gl/include/kotek_render_resource_manager.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_ANGLE_GLES23(
	kun_kotek kun_core ktkMainManager* p_main_manager,
	kun_kotek kun_core eEngineSupportedRenderer version)
{
	KOTEK_MESSAGE("render module is initialized");

	auto* p_engine_config = p_main_manager->Get_EngineConfig();

	p_engine_config->SetFeatureStatus(version, true);

	gles::ktkRenderDevice* p_render_device = new gles::ktkRenderDevice(version);
	gl::ktkRenderResourceManager* p_render_resource_manager =
		new gl::ktkRenderResourceManager(p_render_device, p_main_manager);
	gles::ktkRenderSwapchain* p_render_swapchain =
		new gles::ktkRenderSwapchain();

	p_main_manager->setRenderDevice(p_render_device);
	p_main_manager->setRenderSwapchainManager(p_render_swapchain);
	p_main_manager->SetRenderResourceManager(p_render_resource_manager);

	if (p_main_manager->Get_Splash())
	{
		p_main_manager->Get_Splash()->Set_Text("loading complete!");
		p_main_manager->Get_Splash()->Set_Progress(-1.0f);
	}

	// todo: wut, too expensive better to use task manager...
	kun_kotek kun_ktk kun_mt thread close_splash(
		[p_main_manager]()
		{
			kun_kotek kun_ktk kun_mt this_thread::sleep_for(
				kun_kotek kun_ktk chrono::milliseconds(700));

			if (p_main_manager)
			{
				kun_kotek kun_core ktkIWindowSplash* p_window =
					p_main_manager->Get_Splash();

				if (p_window)
				{
					p_window->Hide();
				}
			}
		});

	close_splash.detach();

	p_main_manager->Get_WindowManager()->Get_ActiveWindow()->Initialize(
		version);

	p_render_device->Initialize(p_main_manager);

	// TODO: load from user settings
	p_render_device->SetWidth(
		p_main_manager->Get_WindowManager()->ActiveWindow_GetWidth());
	p_render_device->SetHeight(
		p_main_manager->Get_WindowManager()->ActiveWindow_GetHeight());

	p_render_swapchain->Initialize(p_render_device);
	p_render_resource_manager->initialize(p_render_device, p_render_swapchain,
		p_engine_config->Get_VideoMemoryForInitialize());

	p_main_manager->SetRenderResourceManager(p_render_resource_manager);

	KOTEK_MESSAGE("render module is initialized");

	return true;
}

bool ShutdownModule_Render_ANGLE_GLES23(Core::ktkMainManager* p_main_manager)
{
	p_main_manager->getRenderDevice()->GPUFlush();

	Core::ktkIGameManager* p_game_manager = p_main_manager->GetGameManager();
	if (p_game_manager)
	{
		auto* p_renderer = p_game_manager->GetRenderer();

		if (p_renderer)
		{
			p_renderer->Shutdown();
		}
	}

	p_main_manager->getRenderSwapchainManager()->Shutdown(
		p_main_manager->getRenderDevice());

	p_main_manager->GetRenderResourceManager()->shutdown(
		p_main_manager->getRenderDevice());

	p_main_manager->getRenderDevice()->Shutdown();

	gles::ktkRenderDevice* p_render_device =
		dynamic_cast<gles::ktkRenderDevice*>(p_main_manager->getRenderDevice());
	gl::ktkRenderResourceManager* p_render_resource_manager =
		dynamic_cast<gl::ktkRenderResourceManager*>(
			p_main_manager->GetRenderResourceManager());
	gles::ktkRenderSwapchain* p_render_swapchain =
		dynamic_cast<gles::ktkRenderSwapchain*>(
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