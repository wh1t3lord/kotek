#include "kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderResourceManager::ktkRenderResourceManager(void) {}

			ktkRenderResourceManager::~ktkRenderResourceManager(void) {}

			void ktkRenderResourceManager::initialize(
				Core::ktkIRenderDevice* p_raw_device,
				Core::ktkIRenderSwapchain* p_raw_swapchain)
			{
			}

			void ktkRenderResourceManager::shutdown(
				Core::ktkIRenderDevice* p_raw_device)
			{
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek