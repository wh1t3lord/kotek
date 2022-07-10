#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
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
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek