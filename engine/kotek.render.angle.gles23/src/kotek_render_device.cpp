#include "../include/kotek_render_device.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gles
{
	ktkRenderDevice3::ktkRenderDevice3(void) : m_width{}, m_height{} {}

	ktkRenderDevice3::~ktkRenderDevice3(void) {}

	void ktkRenderDevice3::Initialize(Core::ktkMainManager* p_main_manager) 
	{
		
	}

	void ktkRenderDevice3::Shutdown(void) {}

	void ktkRenderDevice3::Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
		Core::kotek_i_renderer* p_raw_renderer,
		Core::ktkIRenderResourceManager* p_raw_resource_manager, int width,
		int height)
	{
	}

	int ktkRenderDevice3::GetWidth(void) const noexcept
	{
		return this->m_width;
	}

	int ktkRenderDevice3::GetHeight(void) const noexcept
	{
		return this->m_height;
	}

	void ktkRenderDevice3::GPUFlush(void) {}

	void ktkRenderDevice3::SetWidth(int width) noexcept
	{
		this->m_width = width;
	}

	void ktkRenderDevice3::SetHeight(int height) noexcept
	{
		this->m_height = height;
	}
} // namespace gles

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
