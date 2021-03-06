#include "../include/kotek_render_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderDevice::ktkRenderDevice(void) : m_width{}, m_height{} {}

			ktkRenderDevice::~ktkRenderDevice(void) {}

			void ktkRenderDevice::Initialize(
				Core::ktkMainManager* p_main_manager)
			{
				p_main_manager->GetGameManager()->CreateSurface(
					p_main_manager, nullptr, nullptr);
			}

			void ktkRenderDevice::Shutdown(void) {}

			void ktkRenderDevice::Resize(
				Core::ktkIRenderSwapchain* p_raw_swapchain,
				Core::kotek_i_renderer* p_raw_renderer,
				Core::ktkIRenderResourceManager* p_raw_resource_manager,
				int width, int height)
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

		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek