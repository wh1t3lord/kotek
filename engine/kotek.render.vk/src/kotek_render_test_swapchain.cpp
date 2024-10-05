#ifdef KOTEK_DEBUG
	#include "../include/kotek_render_device.h"
	#include "../include/kotek_render_swapchain.h"
	#include <catch2/catch_test_macros.hpp>

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