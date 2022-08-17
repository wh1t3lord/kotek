#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderDevice;
		}
	} // namespace Render

	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
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

				ktk::uint32_t Wait(ktkRenderDevice* p_render_device) noexcept;

				void Present(Core::ktkMainManager* p_main_manager,
					Core::ktkIRenderDevice* p_render_device) override;

				VkSwapchainKHR GetSwapchain(void) const noexcept;

				void SetSwapchainFormat(VkFormat texture_format) noexcept;

				void SetSwapchainColorSpace(
					VkColorSpaceKHR color_space) noexcept;

				VkFormat GetSwapchainFormat(void) const noexcept;

				VkColorSpaceKHR GetSwapchainColorSpace(void) const noexcept;

				VkSemaphore GetSemaphore_ImageAvailable(void) const noexcept;

				VkSemaphore GetSemaphore_RenderFinished(void) const noexcept;

				VkFence GetFence_CommandExecuted(void) const noexcept;

				// Can we turn off Vsync or not?
				bool CanVSYNCTurnOff(
					const ktk::vector<VkPresentModeKHR>& modes) const noexcept;

				ktk::uint32_t GetAcquiredImageIndex(void) const noexcept;

			private:
				void Create(ktkRenderDevice* p_render_device, int width,
					int height) noexcept;

			private:
				ktk::uint32_t m_image_index;
				ktk::uint32_t m_semaphore_index;
				ktk::uint32_t m_semaphore_index_previous;
				VkSwapchainKHR m_p_swapchain;
				VkSurfaceFormatKHR m_swapchain_format;
				ktk::vector<VkFence> m_executed_fences;
				ktk::vector<VkSemaphore> m_semaphores_image_available;
				ktk::vector<VkSemaphore> m_semaphores_finished_render;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
