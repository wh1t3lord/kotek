#pragma once

#include "../kotek.core.api/kotek_api.h"
#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_device;
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
			class kotek_render_swapchain : public Core::kotek_i_render_swapchain
			{
			public:
				kotek_render_swapchain(void);
				~kotek_render_swapchain(void);

				void initialize(
					Core::kotek_i_render_device* p_render_device) override;
				void shutdown(
					Core::kotek_i_render_device* p_render_device) override;
				void resize(Core::kotek_i_render_device* p_render_device,
					int width, int height) override;

				ktk::uint32_t wait(
					kotek_render_device* p_render_device) noexcept;
				void present(Core::ktkMainManager& main_manager,
					kotek_render_device* p_render_device) noexcept;

				VkSwapchainKHR getSwapchain(void) const noexcept;

				void setSwapchainFormat(VkFormat texture_format) noexcept;

				void setSwapchainColorSpace(
					VkColorSpaceKHR color_space) noexcept;

				VkFormat getSwapchainFormat(void) const noexcept;

				VkColorSpaceKHR getSwapchainColorSpace(void) const noexcept;

				VkSemaphore getSemaphore_ImageAvailable(void) const noexcept;

				VkSemaphore getSemaphore_RenderFinished(void) const noexcept;

				VkFence getFence_CommandExecuted(void) const noexcept;

				// Can we turn off Vsync or not?
				bool canVSYNCTurnOff(
					const ktk::vector<VkPresentModeKHR>& modes) const noexcept;

				ktk::uint32_t GetAcquiredImageIndex(void) const noexcept;

			private:
				void create(kotek_render_device* p_render_device, int width,
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
