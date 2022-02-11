#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderSwapchain : public Core::ktkIRenderSwapchain
			{
			public:
				ktkRenderSwapchain(void);
				~ktkRenderSwapchain(void);

				void Initialize(
					Core::ktkIRenderDevice* p_render_device) override;
				void Shutdown(Core::ktkIRenderDevice* p_render_device) override;
				void Resize(Core::ktkIRenderDevice* p_render_device, int width,
					int height) override;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek