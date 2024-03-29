#include "../include/kotek_render_swapchain.h"
#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderSwapchain::ktkRenderSwapchain(void) {}
	ktkRenderSwapchain::~ktkRenderSwapchain(void) {}

	void ktkRenderSwapchain::Initialize(Core::ktkIRenderDevice* p_render_device)
	{
	}

	void ktkRenderSwapchain::Shutdown(Core::ktkIRenderDevice* p_render_device)
	{
	}

	void ktkRenderSwapchain::Resize(
		Core::ktkIRenderDevice* p_render_device, int width, int height)
	{
	}

	void ktkRenderSwapchain::Present(Core::ktkMainManager* p_main_manager,
		Core::ktkIRenderDevice* p_render_device)
	{
		glViewport(
			0, 0, p_render_device->GetWidth(), p_render_device->GetHeight());

#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
		glfwSwapBuffers(static_cast<GLFWwindow*>(
			p_main_manager->GetGameManager()->GetWindowHandle()));

	#ifdef KOTEK_DEBUG
		const char* description_error{};
		if (glfwGetError(&description_error))
		{
            KOTEK_MESSAGE("{}", description_error);
		}
	#endif
#elif defined(KOTEK_USE_WINDOW_LIBRARY_SDL)
		// TODO: add SDL here too!
#else
		// user specific here...
#endif
	}

} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
