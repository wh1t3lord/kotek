#include "../kotek.core/kotek_std.h"
#include "kotek_render.h"

/* TODO:
#include "kotek_render_device.h"
#include "kotek_render_imgui_manager.h"
#include "kotek_render_resource_manager.h"
#include "kotek_render_swapchain.h"
#include "kotek_renderer.h"
*/

#include "../kotek.core/kotek_main_manager.h"
#include "../kotek.render.vk/kotek_render_vk.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render(Core::ktkMainManager& main_manager)
		{
			// TODO: сделать выбор рендера

			bool status = InitializeModule_Render_VK(main_manager);

			KOTEK_ASSERT(
				status, "can't initialize module render Vulkan. See log");

			KOTEK_MESSAGE("render module is initialized");

			return true;
		}

		bool ShutdownModule_Render(Core::ktkMainManager& main_manager)
		{
			bool status = ShutdownModule_Render_VK(main_manager);

			return status;
		}
	} // namespace Render
} // namespace Kotek
