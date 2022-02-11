#include "kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
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
				glViewport(0, 0, width, height);
			}

		} // namespace gl
	}     // namespace Render
} // namespace Kotek