#include "../include/kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderResourceManager::ktkRenderResourceManager(
				ktkRenderDevice* p_device, Core::ktkMainManager* p_manager) :
				m_p_render_device(p_device),
				m_p_main_manager(p_manager)
			{
			}

			ktkRenderResourceManager::~ktkRenderResourceManager(void) {}

			void ktkRenderResourceManager::initialize(
				Core::ktkIRenderDevice* p_raw_device,
				Core::ktkIRenderSwapchain* p_raw_swapchain)
			{
				KOTEK_ASSERT(
					p_raw_device, "you can't pass an invalid interface");
				KOTEK_ASSERT(
					p_raw_swapchain, "you can't pass an invalid interface");
			}

			void ktkRenderResourceManager::shutdown(
				Core::ktkIRenderDevice* p_raw_device)
			{
				KOTEK_ASSERT(
					p_raw_device, "you can't pass an invalid interface");
			}

			void ktkRenderResourceManager::Resize(
				Core::ktkIRenderDevice* p_raw_device,
				Core::ktkIRenderSwapchain* p_raw_swapchain)
			{
				KOTEK_ASSERT(
					p_raw_device, "you can't pass an invalid interface");
				KOTEK_ASSERT(
					p_raw_swapchain, "you can't pass an invalid interface");
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek