#ifdef KOTEK_DEBUG
	#include "../kotek.core/kotek_main_manager.h"
	#include "kotek_render_device.h"
	#include "kotek_render_swapchain.h"
	#include <boost/test/unit_test.hpp>

namespace Kotek
{
	namespace Render
	{
		void registerTests_Swapchain_ForModule_Render_VK(void)
		{
			KOTEK_MESSAGE("registered!");
		}

	} // namespace Render
} // namespace Kotek
#endif