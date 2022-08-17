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

			void ktkRenderSwapchain::Present(
				Core::ktkMainManager* p_main_manager,
				Core::ktkIRenderDevice* p_render_device)
			{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
				glfwSwapBuffers(static_cast<GLFWwindow*>(
					p_main_manager->GetGameManager()->GetWindowHandle()));
#elif defined(KOTEK_USE_WINDOW_LIBRARY_SDL)
				// TODO: add SDL here too!
#else
				// user specific here...
#endif
			}

		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek