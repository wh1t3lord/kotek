#include "../include/kotek_render_swapchain.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace bgfx
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
		::bgfx::reset(static_cast<uint32_t>(width),
			static_cast<uint32_t>(height), BGFX_RESET_VSYNC);
	}

	void ktkRenderSwapchain::Present(Core::ktkMainManager* p_main_manager,
		Core::ktkIRenderDevice* p_render_device)
	{
		::bgfx::frame();
	}

} // namespace bgfx
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
