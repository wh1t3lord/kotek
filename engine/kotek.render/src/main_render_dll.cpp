#include "../include/kotek_render.h"

#include <kotek.render.gl3/include/kotek_render_gl.h>
#include <kotek.render.vk/include/kotek_render_vk.h>

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render(Core::ktkMainManager* main_manager)
		{
			// TODO: сделать выбор рендера

			bool status{};
			if (main_manager->Get_EngineConfig()
					->IsContainsConsoleCommandLineArgument(
						kConsoleCommandArg_Render_OpenGL3_3))
			{
				status = InitializeModule_Render_GL(main_manager);
			}
			else if (main_manager->Get_EngineConfig()
						 ->IsContainsConsoleCommandLineArgument(
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
				main_manager->Get_EngineConfig()->GetRenderName().get_as_is());

			KOTEK_MESSAGE("render module {} is initialized",
				main_manager->Get_EngineConfig()->GetRenderName().get_as_is());

			return true;
		}

		bool ShutdownModule_Render(Core::ktkMainManager* main_manager)
		{
			bool status{};

			if (main_manager->Get_EngineConfig()
					->IsContainsConsoleCommandLineArgument(
						kConsoleCommandArg_Render_OpenGL3_3))
			{
				status = ShutdownModule_Render_GL(main_manager);
			}
			else if (main_manager->Get_EngineConfig()
						 ->IsContainsConsoleCommandLineArgument(
							 kConsoleCommandArg_Render_Vulkan))
			{
				status = ShutdownModule_Render_VK(main_manager);
			}
			else
			{
				status = ShutdownModule_Render_GL(main_manager);
			}

			KOTEK_ASSERT(status, "failed to shutdown render {} module",
				main_manager->Get_EngineConfig()->GetRenderName().get_as_is());

			return status;
		}
	} // namespace Render
} // namespace Kotek
