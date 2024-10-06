#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderDevice : public Core::ktkIRenderDevice
	{
	public:
		ktkRenderDevice(void);
		~ktkRenderDevice(void);

		void Initialize(Core::ktkMainManager* main_manager) override;
		void Shutdown(void) override;
		void Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
			Core::ktkIRenderer* p_raw_renderer,
			Core::ktkIRenderResourceManager* p_raw_resource_manager, int width,
			int height) override;
		int GetWidth(void) const noexcept override;
		int GetHeight(void) const noexcept override;
		void GPUFlush(void) override;

		void SetWidth(int width) noexcept;
		void SetHeight(int height) noexcept;

	private:
		int m_width;
		int m_height;
	};
} // namespace gl
KOTEK_END_NAMESPACE_KOTEK
KOTEK_END_NAMESPACE_KOTEK
