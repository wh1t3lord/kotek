#include "kotek_render_swapchain.h"
#include "../kotek.core/kotek_main_manager.h"
#include "kotek_render_device.h"
#include "kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_swapchain::kotek_render_swapchain() :
				m_semaphore_index(0), m_semaphore_index_previous(0),
				m_p_swapchain(nullptr)
			{
#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("ctor");
#endif
			}

			kotek_render_swapchain::~kotek_render_swapchain()
			{
#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("~dtor");
#endif
			}

			void kotek_render_swapchain::initialize(
				Core::kotek_i_render_device* p_raw_render_device)
			{
				kotek_render_device* p_render_device =
					static_cast<kotek_render_device*>(p_raw_render_device);

				KOTEK_ASSERT(p_render_device->getWidth() != -1,
					"you didn't set width for render device");
				KOTEK_ASSERT(p_render_device->getHeight() != -1,
					"you didn't set height for render device");

				VkResult status;

				this->m_executed_fences.resize(_kSwapchainBackBuffers);
				this->m_semaphores_image_available.resize(
					_kSwapchainBackBuffers);
				this->m_semaphores_finished_render.resize(
					_kSwapchainBackBuffers);

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize device before calling this method");

				for (ktk::uint32_t i = 0; i < _kSwapchainBackBuffers; ++i)
				{
					VkFenceCreateInfo info_fence = {};

					info_fence.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
					info_fence.pNext = nullptr;
					info_fence.flags = VK_FENCE_CREATE_SIGNALED_BIT;

					status = vkCreateFence(p_device, &info_fence, nullptr,
						&this->m_executed_fences[i]);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't create fence. See status: {}", status);

					VkSemaphoreCreateInfo info_semaphore = {};

					info_semaphore.sType =
						VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
					info_semaphore.pNext = nullptr;
					info_semaphore.flags = 0;

					status = vkCreateSemaphore(p_device, &info_semaphore,
						nullptr, &this->m_semaphores_image_available[i]);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't create semaphore. See status: {}", status);

					status = vkCreateSemaphore(p_device, &info_semaphore,
						nullptr, &this->m_semaphores_finished_render[i]);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't create semaphore. See status: {}", status);
				}

				this->create(p_render_device, p_render_device->getWidth(),
					p_render_device->getHeight());

				KOTEK_MESSAGE("swapchain is initialized");
			}

			void kotek_render_swapchain::shutdown(
				Core::kotek_i_render_device* p_raw_render_device)
			{
				kotek_render_device* p_render_device =
					static_cast<kotek_render_device*>(p_raw_render_device);

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize (early calling) device before "
					"swapchain (VkDevice)");

				if (this->m_p_swapchain)
				{
					vkDestroySwapchainKHR(
						p_device, this->m_p_swapchain, nullptr);
				}

				for (auto& p_fence : this->m_executed_fences)
				{
					vkDestroyFence(p_device, p_fence, nullptr);
				}

				for (auto& p_semaphore : this->m_semaphores_finished_render)
				{
					vkDestroySemaphore(p_device, p_semaphore, nullptr);
				}

				for (auto& p_semaphore : this->m_semaphores_image_available)
				{
					vkDestroySemaphore(p_device, p_semaphore, nullptr);
				}

				KOTEK_MESSAGE("swapchain is shutdown");
			}

			void kotek_render_swapchain::resize(
				Core::kotek_i_render_device* p_raw_render_device, int width,
				int height)
			{
				kotek_render_device* p_render_device =
					static_cast<kotek_render_device*>(p_raw_render_device);

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize (early calling) device before "
					"swapchain (VkDevice)");

				KOTEK_ASSERT(this->m_p_swapchain,
					"you can't destroy an invalid swapchain (nullptr)");

				vkDestroySwapchainKHR(p_device, this->m_p_swapchain, nullptr);

				this->create(p_render_device, width, height);
			}

			ktk::uint32_t kotek_render_swapchain::wait(
				kotek_render_device* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				auto status = vkAcquireNextImageKHR(p_device, this->m_p_swapchain,
					ktk::kMax_UINT64,
					this->m_semaphores_image_available.at(
						this->m_semaphore_index),
					nullptr, &this->m_image_index);

				KOTEK_ASSERT(status == VK_SUCCESS, "failed to vkAcquireNextImageKHR");

				this->m_semaphore_index_previous = this->m_semaphore_index;
				++this->m_semaphore_index;

				if (this->m_semaphore_index >= _kSwapchainBackBuffers)
					this->m_semaphore_index = 0;

				status = vkWaitForFences(p_device, 1,
					&this->m_executed_fences[this->m_semaphore_index_previous],
					VK_TRUE, ktk::kMax_UINT64);

				KOTEK_ASSERT(status == VK_SUCCESS, "failed to vkWaitForFences");

				status = vkResetFences(p_device, 1,
					&this->m_executed_fences[this->m_semaphore_index_previous]);

				KOTEK_ASSERT(status == VK_SUCCESS, "failed to vkResetFences");

				return this->m_image_index;
			}

			void kotek_render_swapchain::present(
				Core::ktkMainManager& main_manager,
				kotek_render_device* p_render_device) noexcept
			{
				VkPresentInfoKHR info = {};

				info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
				info.pNext = nullptr;
				info.waitSemaphoreCount = 1;
				info.pWaitSemaphores = &(this->m_semaphores_finished_render.at(
					this->m_semaphore_index));
				info.swapchainCount = 1;
				info.pSwapchains = &this->m_p_swapchain;
				info.pImageIndices = &this->m_image_index;
				info.pResults = nullptr;

				VkQueue p_queue_present = p_render_device->getQueue_Present();

				KOTEK_ASSERT(p_queue_present,
					"you must initialize device (VkQueue=Present)");

				VkResult status = vkQueuePresentKHR(p_queue_present, &info);

				if (!(status == VK_SUCCESS))
				{
					if (status == VK_ERROR_OUT_OF_DATE_KHR)
					{
						int height = main_manager.GetGameManager()->GetWindowHeight();
						int width = main_manager.GetGameManager()->GetWindowWidth();

						main_manager.GetGameManager()->GetConsole()->Execute(
							Core::ktkConsoleCommandIndex::
								kConsoleCommand_Resize,
							{ktk::string(width), ktk::string(height)});
					}
					else
					{
						KOTEK_ASSERT(status == VK_SUCCESS,
							"failed to vkQueuePresentKHR. See status");
					}
				}
			}

			VkSwapchainKHR kotek_render_swapchain::getSwapchain(
				void) const noexcept
			{
				return this->m_p_swapchain;
			}

			void kotek_render_swapchain::setSwapchainFormat(
				VkFormat texture_format) noexcept
			{
				this->m_swapchain_format.format = texture_format;
			}

			void kotek_render_swapchain::setSwapchainColorSpace(
				VkColorSpaceKHR color_space) noexcept
			{
				this->m_swapchain_format.colorSpace = color_space;
			}

			VkFormat kotek_render_swapchain::getSwapchainFormat(
				void) const noexcept
			{
				return this->m_swapchain_format.format;
			}

			VkColorSpaceKHR kotek_render_swapchain::getSwapchainColorSpace(
				void) const noexcept
			{
				return this->m_swapchain_format.colorSpace;
			}

			VkSemaphore kotek_render_swapchain::getSemaphore_ImageAvailable(
				void) const noexcept
			{
				return this->m_semaphores_image_available.at(
					this->m_semaphore_index_previous);
			}

			VkSemaphore kotek_render_swapchain::getSemaphore_RenderFinished(
				void) const noexcept
			{
				return this->m_semaphores_finished_render.at(
					this->m_semaphore_index);
			}

			VkFence kotek_render_swapchain::getFence_CommandExecuted(
				void) const noexcept
			{
				return this->m_executed_fences.at(
					this->m_semaphore_index_previous);
			}

			bool kotek_render_swapchain::canVSYNCTurnOff(
				const ktk::vector<VkPresentModeKHR>& modes) const noexcept
			{
				if (modes.empty())
				{
					return false;
				}

				for (const auto& mode : modes)
				{
					if (mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
					{
						return true;
					}
				}

				return false;
			}

			ktk::uint32_t kotek_render_swapchain::GetAcquiredImageIndex(
				void) const noexcept
			{
				return this->m_image_index;
			}

			void kotek_render_swapchain::create(
				kotek_render_device* p_render_device, int width,
				int height) noexcept
			{
#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE(
					"issued resize for: width={} height={}", width, height);
#endif

				VkSurfaceCapabilitiesKHR surface_caps;

				VkDevice p_device = p_render_device->getDevice();
				VkPhysicalDevice p_physical_device =
					p_render_device->getCurrentPhysicalDevice();
				VkSurfaceKHR p_surface = p_render_device->getSurface();

				KOTEK_ASSERT(p_device,
					"you must initialize device before using swapchain "
					"(VkDevice)");

				KOTEK_ASSERT(p_physical_device,
					"you must initialize device before using swapchain "
					"(VkPhysicalDevice)");

				KOTEK_ASSERT(p_surface,
					"you must initialize device before using swapchain "
					"(VkSurfaceKHR)");

				VkResult status = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
					p_physical_device, p_surface, &surface_caps);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't get surface capabilities. See status");

				VkExtent2D extent;

				extent.width = width;
				extent.height = height;

				/*
				  https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/VkSurfaceCapabilitiesKHR.html
				*/

				if (surface_caps.currentExtent.width == 0xFFFFFFFF)
				{
					if (extent.width < surface_caps.minImageExtent.width)
					{
						extent.width = surface_caps.minImageExtent.width;
					}
					else if (extent.width > surface_caps.maxImageExtent.width)
					{
						extent.width = surface_caps.maxImageExtent.width;
					}

					if (extent.height < surface_caps.minImageExtent.height)
					{
						extent.height = surface_caps.minImageExtent.height;
					}
					else if (extent.height > surface_caps.maxImageExtent.height)
					{
						extent.height = surface_caps.maxImageExtent.height;
					}
				}
				else
				{
				}

				VkSurfaceTransformFlagBitsKHR pretransform =
					(surface_caps.supportedTransforms &
						VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
					? VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR
					: surface_caps.currentTransform;

				VkCompositeAlphaFlagBitsKHR composite_alpha =
					VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

				VkCompositeAlphaFlagBitsKHR composite_alpha_flags[4] = {
					VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
					VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
					VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
					VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR};

				for (ktk::uint32_t i = 0; i < sizeof(composite_alpha_flags);
					 ++i)
				{
					if (surface_caps.supportedCompositeAlpha &
						composite_alpha_flags[i])
					{
						composite_alpha = composite_alpha_flags[i];
						break;
					}
				}

				ktk::uint32_t present_mode_count = 0;

				status = vkGetPhysicalDeviceSurfacePresentModesKHR(
					p_physical_device, p_surface, &present_mode_count, nullptr);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't get present modes of surface");

				ktk::vector<VkPresentModeKHR> present_modes(present_mode_count);

				status =
					vkGetPhysicalDeviceSurfacePresentModesKHR(p_physical_device,
						p_surface, &present_mode_count, present_modes.data());

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't fill vector of VkPresentModeKHR");

				// TODO: validate vsync here, because present_modes vector might
				// contain only FIFO but not immediate that means we can't turn
				// off vsync

				VkSwapchainCreateInfoKHR info_swapchain = {};

				// TODO: implement HDR support
				this->m_swapchain_format =
					p_render_device->getCurrentPhysicalDeviceSurfaceFormat();

				info_swapchain.sType =
					VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				info_swapchain.pNext = nullptr;
				info_swapchain.surface = p_surface;
				info_swapchain.imageFormat = this->m_swapchain_format.format;
				info_swapchain.minImageCount = _kSwapchainBackBuffers;
				info_swapchain.imageColorSpace =
					this->m_swapchain_format.colorSpace;
				info_swapchain.imageExtent.height = extent.height;
				info_swapchain.imageExtent.width = extent.width;
				info_swapchain.preTransform = pretransform;
				info_swapchain.compositeAlpha = composite_alpha;
				info_swapchain.imageArrayLayers = 1;
				info_swapchain.presentMode =
					VK_PRESENT_MODE_FIFO_KHR; // TODO: depends on flag if we use
				                              // Vsync
				info_swapchain.oldSwapchain = nullptr;
				info_swapchain.clipped = true;
				info_swapchain.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT |
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
				info_swapchain.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				info_swapchain.queueFamilyIndexCount = 0;
				info_swapchain.pQueueFamilyIndices = nullptr;

				ktk::uint32_t queue_family_index_graphics =
					p_render_device->getFamilyQueueIndex_Graphics();
				ktk::uint32_t queue_family_index_present =
					p_render_device->getFamilyQueueIndex_Present();

				if (queue_family_index_graphics != queue_family_index_present)
				{
					ktk::uint32_t p_indecies[2] = {queue_family_index_graphics,
						queue_family_index_present};

					info_swapchain.imageSharingMode =
						VK_SHARING_MODE_CONCURRENT;
					info_swapchain.queueFamilyIndexCount =
						sizeof(p_indecies) / sizeof(p_indecies[0]);
					info_swapchain.pQueueFamilyIndices = p_indecies;
				}

				status = vkCreateSwapchainKHR(
					p_device, &info_swapchain, nullptr, &this->m_p_swapchain);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't create swapchain. See status");
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
