#include "../include/kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderSwapchain::ktkRenderSwapchain(void) {}
			ktkRenderSwapchain::~ktkRenderSwapchain(void) {}

			void ktkRenderSwapchain::Initialize(
				Core::ktkIRenderDevice* p_render_device)
			{
			}

			void ktkRenderSwapchain::Shutdown(
				Core::ktkIRenderDevice* p_render_device)
			{
			}

			void ktkRenderSwapchain::Resize(
				Core::ktkIRenderDevice* p_render_device, int width, int height)
			{
			}

		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek