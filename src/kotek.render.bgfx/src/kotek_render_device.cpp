#include "../include/kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

ktkRenderDevice::ktkRenderDevice(void) : m_width{-1}, m_height{-1} {}

ktkRenderDevice::~ktkRenderDevice(void) {}

// todo: provide support for multithreaded version like separated render
// thread
void ktkRenderDevice::Initialize(kun_core ktkMainManager* p_main_manager)
{
	KOTEK_ASSERT(this->m_width > 0, "call SetWidth before Initialize");
	KOTEK_ASSERT(this->m_height > 0, "call SetHeight before Initialize");

	kun_core ktkIFrameworkConfig* p_config = p_main_manager->Get_EngineConfig();

	KOTEK_ASSERT(
		p_config, "you must initialize config before calling this method!");

	::bgfx::renderFrame();

	::bgfx::Init init;

	bool isGLES = p_config->IsFeatureEnabled(kun_core eEngineFeatureRenderer::
						  kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser) ||
		p_config->IsFeatureEnabled(kun_core eEngineFeatureRenderer::
				kEngine_Feature_Renderer_OpenGLES_Latest);

	if (isGLES)
	{
		init.type = ::bgfx::RendererType::OpenGLES;
	}
	else
	{
		KOTEK_MESSAGE_ERROR(
			"unknown renderer or we just didn't implement support! Sorry");
	}

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkWin32OSData* p_platform_data = static_cast<ktkWin32OSData*>(
		p_main_manager->Get_WindowManager()->Get_ActiveWindow()->Get_OSData());
	KOTEK_ASSERT(p_platform_data,
		"window must have valid platform data aka hwnd and etc");

	KOTEK_ASSERT(p_platform_data->hWnd, "HWND is not valid!");

	init.platformData.nwh = p_platform_data->hWnd;
#elif defined(KOTEK_USE_PLATFORM_LINUX)
#else
	#error unknown platform
#endif

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

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
