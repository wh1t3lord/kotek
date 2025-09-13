#include "../include/kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace bgfx
{
	ktkRenderDevice::ktkRenderDevice(void) : m_width{-1}, m_height{-1} {}

	ktkRenderDevice::~ktkRenderDevice(void) {}

	// todo: provide support for multithreaded version like separated render
	// thread
	void ktkRenderDevice::Initialize(Core::ktkMainManager* p_main_manager)
	{
		KOTEK_ASSERT(this->m_width > 0, "call SetWidth before Initialize");
		KOTEK_ASSERT(this->m_height > 0, "call SetHeight before Initialize");

		::bgfx::renderFrame();

		::bgfx::Init init;
		init.platformData.nwh =
			p_main_manager->Get_WindowManager()->ActiveWindow_GetHandle();

		init.resolution.width = this->m_width;
		init.resolution.height = this->m_height;

		// todo: provide option that we can bypass
		init.resolution.reset = BGFX_RESET_VSYNC;

		bool status = ::bgfx::init(init);
		KOTEK_ASSERT(status, "failed to initialize bgfx!");

		if (status)
		{
			KOTEK_MESSAGE("bgfx initialized: {}",
				::bgfx::getRendererName(::bgfx::getRendererType()));

#ifdef KOTEK_DEBUG
			::bgfx::setDebug(BGFX_DEBUG_TEXT);
#endif
		}
	}

	void ktkRenderDevice::Shutdown(void)
	{
		::bgfx::shutdown();
	}

	void ktkRenderDevice::Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
		Core::ktkIRenderer* p_raw_renderer,
		Core::ktkIRenderResourceManager* p_raw_resource_manager, int width,
		int height)
	{
		this->m_width = width;
		this->m_height = height;

		p_raw_swapchain->Resize(this, width, height);
		p_raw_renderer->Resize();
	}

	int ktkRenderDevice::GetWidth(void) const noexcept
	{
		return this->m_width;
	}

	int ktkRenderDevice::GetHeight(void) const noexcept
	{
		return this->m_height;
	}

	void ktkRenderDevice::GPUFlush() {}

	void ktkRenderDevice::SetWidth(int width) noexcept
	{
		this->m_width = width;
	}

	void ktkRenderDevice::SetHeight(int height) noexcept
	{
		this->m_height = height;
	}

} // namespace bgfx
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
