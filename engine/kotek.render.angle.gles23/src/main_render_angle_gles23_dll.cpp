#include "../include/kotek_render_angle_gles23.h"

#include "../include/kotek_render_device.h"
#include "../include/kotek_render_swapchain.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_ANGLE_GLES23(Core::ktkMainManager* p_main_manager,
	Core::eEngineSupportedRenderer version)
{
	KOTEK_MESSAGE("render module is initialized");

	auto* p_engine_config = p_main_manager->Get_EngineConfig();

	p_engine_config->SetFeatureStatus(version, true);

	gles::ktkRenderDevice* p_render_device = new gles::ktkRenderDevice(version);

	gles::ktkRenderSwapchain* p_render_swapchain =
		new gles::ktkRenderSwapchain();



	return true;
}

bool ShutdownModule_Render_ANGLE_GLES23(Core::ktkMainManager* p_main_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK