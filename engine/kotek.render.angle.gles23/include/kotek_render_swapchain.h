#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gles
{
	class ktkRenderSwapchain : public Core::ktkIRenderSwapchain
	{
	public:
		ktkRenderSwapchain();
		~ktkRenderSwapchain();

		
		void Initialize(Core::ktkIRenderDevice* p_render_device) override;

		void Shutdown(Core::ktkIRenderDevice* p_render_device) override;

		void Resize(Core::ktkIRenderDevice* p_render_device, int width,
			int height) override;

		void Present(Core::ktkMainManager* p_main_manager,
			Core::ktkIRenderDevice* p_render_device) override;
	};
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
