#include "../include/kotek_render.h"

#include <kotek.render.model/include/kotek_render_model.h>
#include <kotek.render.gl/include/kotek_render_gl.h>
#include <kotek.render.vk/include/kotek_render_vk.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render(Core::ktkMainManager* main_manager)
{
	// TODO: сделать выбор рендера

	InitializeModule_Render_Shared(main_manager);

	auto* p_engine_config = main_manager->Get_EngineConfig();

	// TODO: provide an overriding for every instance what implemented here
	KOTEK_ASSERT(p_engine_config,
		"you must initialize ktkEngineConfig instance or override it by your "
		"own implementation");

	KOTEK_ASSERT(p_engine_config->IsUserSpecifiedValidRenderer(),
		"User didn't specify renderer correctly!");

	bool status{};

	if (p_engine_config->IsUserSpecifiedRendererDirectXInCommandLine())
	{
	}
	else if (p_engine_config->IsUserSpecifiedRendererOpenGLInCommandLine())
	{
	}
	else if (p_engine_config->IsUserSpecifiedRendererVulkanInCommandLine())
	{
	}
	else
	{
		// TODO: by default run ANGLE with renderer what ANGLE supports
		// TODO: support feature for sys_info for default renderer field
	}

	if (p_engine_config->IsContainsConsoleCommandLineArgument(
			kConsoleCommandArg_Render_OpenGL3_3))
	{
		status = InitializeModule_Render_GL(main_manager);
	}
	else if (p_engine_config->IsContainsConsoleCommandLineArgument(
				 kConsoleCommandArg_Render_Vulkan))
	{
		status = InitializeModule_Render_VK(main_manager);
	}
	else
	{
		KOTEK_MESSAGE("trying to initialize default render OpenGL, "
					  "because you don't specify any or coudn't define "
					  "from serialized user data");
		status = InitializeModule_Render_GL(main_manager);
	}

	KOTEK_ASSERT(status, "can't initialize module render {}. See log",
		p_engine_config->GetRenderName());

	KOTEK_MESSAGE(
		"render module {} is initialized", p_engine_config->GetRenderName());

	return true;
}

bool ShutdownModule_Render(Core::ktkMainManager* main_manager)
{
	bool status{};

	if (p_engine_config->IsContainsConsoleCommandLineArgument(
			kConsoleCommandArg_Render_OpenGL3_3))
	{
		status = ShutdownModule_Render_GL(main_manager);
	}
	else if (p_engine_config->IsContainsConsoleCommandLineArgument(
				 kConsoleCommandArg_Render_Vulkan))
	{
		status = ShutdownModule_Render_VK(main_manager);
	}
	else
	{
		status = ShutdownModule_Render_GL(main_manager);
	}

	KOTEK_ASSERT(status, "failed to shutdown render {} module",
		p_engine_config->GetRenderName().get_as_is());

	return status;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
