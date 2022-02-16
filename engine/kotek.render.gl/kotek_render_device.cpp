#include "kotek_render_device.h"
#include "../kotek.core/kotek_main_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderDevice::ktkRenderDevice(void) : m_width{}, m_height{} {}

			ktkRenderDevice::~ktkRenderDevice(void) {}

			void ktkRenderDevice::Initialize(Core::ktkMainManager& main_manager)
			{
				main_manager.GetGameManager()->CreateSurface(
					static_cast<Core::ktkMainManager*>(&main_manager), nullptr,
					nullptr);

/*
				glfwMakeContextCurrent(static_cast<GLFWwindow*>(
					main_manager.GetGameManager()->GetWindowHandle()));

				if (!gladLoadGLLoader(
						reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				{
					KOTEK_ASSERT(false,
						"failed to gladLoadGLLoader. Can't initialize OpenGL "
						"for this system");
					return;
				}*/
			}

			void ktkRenderDevice::Shutdown(void) {}

			void ktkRenderDevice::Resize(
				Core::ktkIRenderSwapchain* p_raw_swapchain,
				Core::kotek_i_renderer* p_raw_renderer,
				Core::ktkIRenderResourceManager* p_raw_resource_manager,
				int width, int height)
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

			void ktkRenderDevice::GPUFlush() {}

			void ktkRenderDevice::SetWidth(int width) noexcept
			{
				this->m_width = width;
			}

			void ktkRenderDevice::SetHeight(int height) noexcept
			{
				this->m_height = height;
			}

		} // namespace gl
	}     // namespace Render
} // namespace Kotek