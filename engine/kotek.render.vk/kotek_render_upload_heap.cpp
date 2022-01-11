#include "kotek_render_upload_heap.h"
#include "kotek_render_device.h"
#include "kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_upload_heap::kotek_render_upload_heap() :
				m_total_size(0), m_p_data_begin(nullptr),
				m_p_data_current(nullptr), m_p_data_end(nullptr),
				m_p_command_pool(nullptr), m_p_command_buffer(nullptr),
				m_p_buffer(nullptr), m_p_device_memory(nullptr),
				m_p_fence(nullptr), m_alignment(0)
			{
			}

			kotek_render_upload_heap::~kotek_render_upload_heap() {}

			void kotek_render_upload_heap::initialize(
				ktkRenderDevice* p_render_device, ktk::uint32_t size)
			{
				this->m_total_size = size;

				this->createCommandPool(p_render_device);
				this->createCommandBuffer(p_render_device);
				this->createBuffer(p_render_device);
				this->createFence(p_render_device);

				this->beginCommandBuffer(p_render_device);
			}

			void kotek_render_upload_heap::shutdown(
				ktkRenderDevice* p_render_device)
			{
				this->m_total_size = 0;

				this->destroyBuffer(p_render_device);
				this->destroyCommandBuffer(p_render_device);
				this->destroyCommandPool(p_render_device);
				this->destroyFence(p_render_device);
			}

			ktk::uint8_t* kotek_render_upload_heap::subAllocate(
				ktk::size_t size) noexcept
			{
				// TODO: sync here

				ktk::uint8_t* p_result = nullptr;

				KOTEK_ASSERT(size < static_cast<size_t>(this->m_p_data_end -
										this->m_p_data_begin),
					"data is overflow out. need resize or increase");

				this->m_p_data_current =
					reinterpret_cast<ktk::uint8_t*>(ktk::align_up(
						reinterpret_cast<size_t>(this->m_p_data_current),
						this->m_alignment));

				size = ktk::align_up(size, this->m_alignment);

				if ((this->m_p_data_current >= this->m_p_data_end) ||
					(this->m_p_data_current + size >= this->m_p_data_end))
				{
					KOTEK_ASSERT(false, "can't allocate memory");
					return static_cast<ktk::uint8_t*>(nullptr);
				}

				p_result = this->m_p_data_current;
				this->m_p_data_current += size;

				return p_result;
			}

			// TODO: I don't understand why I need this
			// When I just can place syncs in Suballocate method and get my
			// certain part of buffer
			ktk::uint8_t* kotek_render_upload_heap::beginSubAllocate(
				ktkRenderDevice* p_render_device, ktk::size_t size) noexcept
			{
				ktk::uint8_t* p_result = nullptr;

				for (;;)
				{
					p_result = this->subAllocate(size);

					if (p_result != nullptr)
					{
						break;
					}

					this->flushAndFinish(p_render_device);
				}

				// TODO: sync here

				return p_result;
			}

			// TODO: see todo about beginSubAllocate method
			void kotek_render_upload_heap::endSubAllocate()
			{
				// TODO: sync here
			}

			void kotek_render_upload_heap::addCopy(
				VkImage p_image, VkBufferImageCopy image_copy) noexcept
			{
				KOTEK_ASSERT(p_image, "must be a valid object");

				this->m_buffer_image_copies.push_back({p_image, image_copy});
			}

			void kotek_render_upload_heap::addPreBarrier(
				VkImageMemoryBarrier barrier) noexcept
			{
				this->m_pre_barrier.push_back(barrier);
			}

			void kotek_render_upload_heap::addPostBarrier(
				VkImageMemoryBarrier barrier) noexcept
			{
				this->m_post_barrier.push_back(barrier);
			}

			void kotek_render_upload_heap::flush(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkResult status = {};

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkMappedMemoryRange range[1] = {};

				range[0].sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
				range[0].memory = this->m_p_device_memory;
				range[0].size = this->m_p_data_current - this->m_p_data_begin;

				status = vkFlushMappedMemoryRanges(p_device, 1, range);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed operation vkFlushMappedMemoryRanges. See status");
			}

			void kotek_render_upload_heap::flushAndFinish(
				ktkRenderDevice* p_render_device) noexcept
			{
				// TODO: sync here

				KOTEK_ASSERT(
					this->m_p_command_buffer, "must be a valid object");

				this->flush(p_render_device);

				if (this->m_pre_barrier.empty() == false)
				{
					vkCmdPipelineBarrier(this->m_p_command_buffer,
						VK_PIPELINE_STAGE_HOST_BIT,
						VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0,
						nullptr,
						static_cast<ktk::uint32_t>(this->m_pre_barrier.size()),
						this->m_pre_barrier.data());

					this->m_pre_barrier.clear();
				}

				for (const auto& [p_image, image_copy] :
					this->m_buffer_image_copies)
				{
					vkCmdCopyBufferToImage(this->m_p_command_buffer,
						this->m_p_buffer, p_image,
						VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &image_copy);
				}

				this->m_buffer_image_copies.clear();

				if (this->m_post_barrier.empty() == false)
				{
					vkCmdPipelineBarrier(this->m_p_command_buffer,
						VK_PIPELINE_STAGE_TRANSFER_BIT,
						VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0,
						nullptr,
						static_cast<ktk::uint32_t>(this->m_post_barrier.size()),
						this->m_post_barrier.data());

					this->m_post_barrier.clear();
				}

				VkResult status = vkEndCommandBuffer(this->m_p_command_buffer);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkEndCommandBuffer. See status");

				const VkCommandBuffer p_buffers[] = {this->m_p_command_buffer};

				VkSubmitInfo info_submit = {};

				info_submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				info_submit.pNext = nullptr;
				info_submit.waitSemaphoreCount = 0;
				info_submit.pWaitSemaphores = nullptr;
				info_submit.pWaitDstStageMask = nullptr;
				info_submit.commandBufferCount = 1;
				info_submit.pCommandBuffers = p_buffers;
				info_submit.signalSemaphoreCount = 0;
				info_submit.pSignalSemaphores = nullptr;

				VkQueue p_graphics_queue = p_render_device->GetQueue_Graphics();

				KOTEK_ASSERT(p_graphics_queue,
					"you must initialize device (VkQueue = Graphics)");

				status = vkQueueSubmit(
					p_graphics_queue, 1, &info_submit, this->m_p_fence);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkSubmitQueue. See status");

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				status = vkWaitForFences(
					p_device, 1, &this->m_p_fence, VK_TRUE, ktk::kMax_UINT64);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkWaitForFences. See status");

				vkResetFences(p_device, 1, &this->m_p_fence);

				VkCommandBufferBeginInfo info_begin_command_buffer = {};

				info_begin_command_buffer.sType =
					VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				info_begin_command_buffer.pNext = nullptr;
				info_begin_command_buffer.pInheritanceInfo = nullptr;
				info_begin_command_buffer.flags =
					VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

				status = vkBeginCommandBuffer(
					this->m_p_command_buffer, &info_begin_command_buffer);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkBeginCommandBuffer. See status");

				this->m_p_data_current = this->m_p_data_begin;
			}

			ktk::size_t kotek_render_upload_heap::getOffset(
				const ktk::uint8_t* const p_allocated_part_from_heap)
				const noexcept
			{
				return p_allocated_part_from_heap - this->m_p_data_begin;
			}

			ktk::uint8_t* kotek_render_upload_heap::getDataBegin(
				void) const noexcept
			{
				return this->m_p_data_begin;
			}

			VkBuffer kotek_render_upload_heap::getBuffer(void) const noexcept
			{
				return this->m_p_buffer;
			}

			VkCommandBuffer kotek_render_upload_heap::getCommandBuffer(
				void) const noexcept
			{
				return this->m_p_command_buffer;
			}

			void kotek_render_upload_heap::createCommandPool(
				ktkRenderDevice* p_render_device) noexcept
			{
				KOTEK_ASSERT(this->m_p_command_pool == nullptr,
					"you must delete your command pool, because it's not empty "
					"and "
					"after that call this method");

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkCommandPoolCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				info.pNext = nullptr;
				info.queueFamilyIndex =
					p_render_device->GetFamilyQueueIndex_Graphics();
				info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

				VkResult status = vkCreateCommandPool(
					p_device, &info, nullptr, &this->m_p_command_pool);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"Can't create command pool. See status");

				KOTEK_DEBUG_VK_SET_OBJECT_NAME(p_render_device,
					VK_OBJECT_TYPE_COMMAND_POOL, this->m_p_command_pool,
					"upload heap command pool");
			}

			void kotek_render_upload_heap::destroyCommandPool(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkDestroyCommandPool(p_device, this->m_p_command_pool, nullptr);
			}

			void kotek_render_upload_heap::createBuffer(
				ktkRenderDevice* p_render_device) noexcept
			{
				KOTEK_ASSERT(this->m_p_buffer == nullptr,
					"you must delete your buffer, because it's not empty and "
					"after "
					"it call this method");

				KOTEK_ASSERT(this->m_p_data_begin == nullptr,
					"you must set to null this field too as this->m_p_buffer "
					"when "
					"you delete buffer");

				KOTEK_ASSERT(this->m_p_data_current == nullptr,
					"you must set to null this field too as this->m_p_buffer "
					"when "
					"you delete buffer");

				KOTEK_ASSERT(this->m_p_data_end == nullptr,
					"you must set to null this field too as this->m_p_buffer "
					"when "
					"you delete buffer");

				KOTEK_ASSERT(this->m_total_size,
					"you must specify your allocation size otherwise invalid "
					"value here");

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkBufferCreateInfo info_buffer = {};

				info_buffer.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				info_buffer.size = this->m_total_size;
				info_buffer.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
				info_buffer.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

				VkResult status = vkCreateBuffer(
					p_device, &info_buffer, nullptr, &this->m_p_buffer);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't create buffer. See status");

				// TODO: user can allocate size as is without restrictions, but
				// further suballocations have to use alignment from
				// VkMemoryRequirements So change api and delete second argument
				// from suballocate
				VkMemoryRequirements memory_requirements;
				vkGetBufferMemoryRequirements(
					p_device, this->m_p_buffer, &memory_requirements);

				VkMemoryAllocateInfo info_alloc = {};

				info_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				info_alloc.allocationSize = memory_requirements.size;
				info_alloc.memoryTypeIndex = 0;

				bool is_valid = p_render_device->IsMemoryTypeFromProperties(
					p_render_device->GetCurrentPhysicalDeviceMemoryProperties(),
					memory_requirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
					&info_alloc.memoryTypeIndex);

				KOTEK_ASSERT(is_valid, "no mappable. coherent memory");

				status = vkAllocateMemory(
					p_device, &info_alloc, nullptr, &this->m_p_device_memory);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "Can't allocate memory. See status");

				status = vkBindBufferMemory(
					p_device, this->m_p_buffer, this->m_p_device_memory, 0);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"Can't bind buffer memory. See status");

				status = vkMapMemory(p_device, this->m_p_device_memory, 0,
					memory_requirements.size, 0,
					reinterpret_cast<void**>(&this->m_p_data_begin));

				KOTEK_ASSERT(
					status == VK_SUCCESS, "Can't map memory. See status");

				this->m_p_data_current = this->m_p_data_begin;
				this->m_p_data_end =
					this->m_p_data_begin + memory_requirements.size;
				this->m_alignment = memory_requirements.alignment;

				KOTEK_ASSERT(this->m_alignment,
					"value of alignment field can't be equal to zero!");
			}

			void kotek_render_upload_heap::destroyBuffer(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkUnmapMemory(p_device, this->m_p_device_memory);
				vkDestroyBuffer(p_device, this->m_p_buffer, nullptr);
				vkFreeMemory(p_device, this->m_p_device_memory, nullptr);
			}

			void kotek_render_upload_heap::createCommandBuffer(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkCommandBufferAllocateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				info.pNext = nullptr;
				info.commandPool = this->m_p_command_pool;
				info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				info.commandBufferCount = 1;

				VkResult status = vkAllocateCommandBuffers(
					p_device, &info, &this->m_p_command_buffer);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"Can't allocate command buffers. See status");
			}

			void kotek_render_upload_heap::destroyCommandBuffer(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkFreeCommandBuffers(p_device, this->m_p_command_pool, 1,
					&this->m_p_command_buffer);
			}

			void kotek_render_upload_heap::createFence(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkFenceCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				info.pNext = nullptr;
				info.flags = 0;

				VkResult status =
					vkCreateFence(p_device, &info, nullptr, &this->m_p_fence);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "Can't create fence. See status");
			}

			void kotek_render_upload_heap::destroyFence(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkDestroyFence(p_device, this->m_p_fence, nullptr);
			}

			void kotek_render_upload_heap::beginCommandBuffer(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkCommandBufferBeginInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				info.pNext = nullptr;
				info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
				info.pInheritanceInfo = nullptr;

				VkResult status =
					vkBeginCommandBuffer(this->m_p_command_buffer, &info);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"Can't begin command buffer. See status");
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
