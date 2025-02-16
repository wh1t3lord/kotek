#include "../include/kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gles
{
	ktkRenderDevice::ktkRenderDevice(Core::eEngineSupportedRenderer version) :
		m_width{}, m_height{}, m_version{version}
	{
	}

	ktkRenderDevice::~ktkRenderDevice(void) {}

	void ktkRenderDevice::Initialize(Core::ktkMainManager* p_main_manager)
	{
		p_main_manager->Get_WindowManager()->ActiveWindow_MakeContextCurrent();

		// todo: make universal function for getprocs like what if we use sdl
		// and etc so based on window library (or if it doesn't present) use
		// preprocessor for passing this function to glad
		int version = gladLoadGLES2Loader(
			reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		KOTEK_ASSERT(version, "failed to gladLoadGLLoader");

		KOTEK_MESSAGE("Initialized GLAD for: {}",
			reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void ktkRenderDevice::Shutdown(void) {}

	void ktkRenderDevice::Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
		Core::ktkIRenderer* p_raw_renderer,
		Core::ktkIRenderResourceManager* p_raw_resource_manager, int width,
		int height)
	{
	}

	int ktkRenderDevice::GetWidth(void) const noexcept
	{
		return this->m_width;
	}

	int ktkRenderDevice::GetHeight(void) const noexcept
	{
		return this->m_height;
	}

	void ktkRenderDevice::GPUFlush(void) {}

	void ktkRenderDevice::SetWidth(int width) noexcept
	{
		this->m_width = width;
	}

	void ktkRenderDevice::SetHeight(int height) noexcept
	{
		this->m_height = height;
	}
} // namespace gles

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
