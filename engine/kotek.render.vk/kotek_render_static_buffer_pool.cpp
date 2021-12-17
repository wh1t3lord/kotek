#include "kotek_render_static_buffer_pool.h"
#include "kotek_render_device.h"
#include "kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_static_buffer_pool::kotek_render_static_buffer_pool() :
				m_memory_offset(0), m_total_memory_size(0), m_p_data(nullptr),
				m_p_buffer(nullptr), m_p_gpu_buffer(nullptr),
				m_p_device_memory(nullptr), m_p_device_gpu_memory(nullptr)

			{
			}

			kotek_render_static_buffer_pool::~kotek_render_static_buffer_pool()
			{
			}

			void kotek_render_static_buffer_pool::initialize(
				kotek_render_device* p_render_device,
				ktk::uint32_t total_memory_size, bool is_use_gpu_memory,
				const ktk::string& vma_name_allocation)
			{
				VkResult status = VK_ERROR_UNKNOWN;

				this->m_is_use_video_memory = is_use_gpu_memory;
				this->m_total_memory_size = total_memory_size;
				this->m_p_data = nullptr;
				this->m_memory_offset = 0;

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

#ifdef kotek_USE_GPU_ALLOCATOR
				// TODO: VMA
#else
				VkBufferCreateInfo info_buffer = {};

				info_buffer.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				info_buffer.pNext = nullptr;
				info_buffer.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
					VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

				if (this->m_is_use_video_memory)
					info_buffer.usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

				info_buffer.size = this->m_total_memory_size;
				info_buffer.queueFamilyIndexCount = 0;
				info_buffer.pQueueFamilyIndices = nullptr;
				info_buffer.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				info_buffer.flags = 0;

				status = vkCreateBuffer(
					p_device, &info_buffer, nullptr, &this->m_p_buffer);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't create buffer. See status");

				VkMemoryRequirements memory_requirements;

				vkGetBufferMemoryRequirements(
					p_device, this->m_p_buffer, &memory_requirements);

				VkMemoryAllocateInfo info_alloc = {};

				info_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				info_alloc.pNext = nullptr;
				info_alloc.memoryTypeIndex =
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
					VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
				info_alloc.allocationSize = memory_requirements.size;

				bool is_matched = p_render_device->isMemoryTypeFromProperties(
					p_render_device->getCurrentPhysicalDeviceMemoryProperties(),
					memory_requirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
						VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					&info_alloc.memoryTypeIndex);

				KOTEK_ASSERT(is_matched,
					"memory type index doesn't matched. No mappable, coherent "
					"memory");

				status = vkAllocateMemory(
					p_device, &info_alloc, nullptr, &this->m_p_device_memory);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't allocate memory for cpu device");

				status = vkBindBufferMemory(
					p_device, this->m_p_buffer, this->m_p_device_memory, 0);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't bind buffer with memory");

				status = vkMapMemory(p_device, this->m_p_device_memory, 0,
					memory_requirements.size, 0,
					reinterpret_cast<void**>(&this->m_p_data));

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't map memory. See status");
#endif

				if (this->m_is_use_video_memory)
				{
#ifdef kotek_USE_GPU_ALLOCATOR
					// TODO: VMA
#else
					VkBufferCreateInfo info_buffer_gpu = {};

					info_buffer_gpu.sType =
						VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
					info_buffer_gpu.pNext = nullptr;
					info_buffer_gpu.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
						VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
						VK_BUFFER_USAGE_TRANSFER_DST_BIT;
					info_buffer_gpu.size = this->m_total_memory_size;
					info_buffer_gpu.queueFamilyIndexCount = 0;
					info_buffer_gpu.pQueueFamilyIndices = nullptr;
					info_buffer_gpu.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
					info_buffer_gpu.flags = 0;

					status = vkCreateBuffer(p_device, &info_buffer_gpu, nullptr,
						&this->m_p_gpu_buffer);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't create buffer. See status");

					VkMemoryRequirements memory_requirements_gpu;
					vkGetBufferMemoryRequirements(p_device,
						this->m_p_gpu_buffer, &memory_requirements_gpu);

					VkMemoryAllocateInfo info_alloc_gpu = {};

					info_alloc_gpu.sType =
						VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
					info_alloc_gpu.pNext = nullptr;
					info_alloc_gpu.memoryTypeIndex =
						VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
					info_alloc_gpu.allocationSize =
						memory_requirements_gpu.size;

					bool is_matched_gpu =
						p_render_device->isMemoryTypeFromProperties(
							p_render_device
								->getCurrentPhysicalDeviceMemoryProperties(),
							memory_requirements_gpu.memoryTypeBits,
							VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
							&info_alloc_gpu.memoryTypeIndex);

					KOTEK_ASSERT(is_matched_gpu,
						"can't be matched. No mappable, coherent memory");

					status = vkAllocateMemory(p_device, &info_alloc_gpu,
						nullptr, &this->m_p_device_gpu_memory);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't allocate memory. See status");

					status = vkBindBufferMemory(p_device, this->m_p_gpu_buffer,
						this->m_p_device_gpu_memory, 0);

					KOTEK_ASSERT(
						status == VK_SUCCESS, "can't bind memory. See status");

#endif

					KOTEK_DEBUG_VK_SET_OBJECT_NAME(p_render_device,
						VK_OBJECT_TYPE_DEVICE_MEMORY,
						this->m_p_device_gpu_memory,
						(ktk::string(
							 "Static buffer pool GPU device memory - ") +
							vma_name_allocation)
							.get_as_legacy()
							.c_str());
				}

				KOTEK_DEBUG_VK_SET_OBJECT_NAME(p_render_device,
					VK_OBJECT_TYPE_DEVICE_MEMORY, this->m_p_device_memory,
					((ktk::string("Static buffer pool CPU device memory - ") +
						vma_name_allocation)
							.get_as_legacy()
							.c_str()));

				KOTEK_MESSAGE("allocated static buffer {} pool with {} Mbs",
					vma_name_allocation.get_as_is(),
					total_memory_size / ktk::kMemoryConvertValue_Megabytes);
			}

			void kotek_render_static_buffer_pool::shutdown(
				kotek_render_device* p_render_device)
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				if (this->m_is_use_video_memory)
				{
#ifdef kotek_USE_GPU_ALLOCATOR
					// TODO: VMA
#else
					if (this->m_p_device_gpu_memory)
					{
						vkDestroyBuffer(
							p_device, this->m_p_gpu_buffer, nullptr);
						vkFreeMemory(
							p_device, this->m_p_device_gpu_memory, nullptr);
					}
#endif

					this->m_p_gpu_buffer = nullptr;
					this->m_p_device_gpu_memory = nullptr;
				}

				if (this->m_p_buffer)
				{
#ifdef kotek_USE_GPU_ALLOCATOR
					// TODO: VMA
#else
					vkUnmapMemory(p_device, this->m_p_device_memory);
					vkDestroyBuffer(p_device, this->m_p_buffer, nullptr);
					vkFreeMemory(p_device, this->m_p_device_memory, nullptr);
#endif

					this->m_p_buffer = nullptr;
					this->m_p_device_memory = nullptr;
				}
			}

			bool kotek_render_static_buffer_pool::allocBuffer(
				ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
				void** p_data, VkDescriptorBufferInfo* p_out) noexcept
			{
				// TODO: cpu sync here, because multithreading
				// TODO: add stats for counting allocations

				ktk::uint32_t size = ktk::align_up<ktk::uint32_t>(
					number_of_elements * stride_in_bytes, 256u);

				KOTEK_ASSERT(
					this->m_memory_offset + size < this->m_total_memory_size,
					"Memory is overflowed. You need to increase size of pool "
					"when "
					"initializing");

				*p_data = reinterpret_cast<void*>(
					this->m_p_data + this->m_memory_offset);

				p_out->buffer = this->m_is_use_video_memory
					? this->m_p_gpu_buffer
					: this->m_p_buffer;
				p_out->offset = this->m_memory_offset;
				p_out->range = size;

				this->m_memory_offset += size;

				return true;
			}

			bool kotek_render_static_buffer_pool::allocBuffer(
				ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
				const void** p_init_data,
				VkDescriptorBufferInfo* p_out) noexcept
			{
				void* p_data;

				if (this->allocBuffer(
						number_of_elements, stride_in_bytes, &p_data, p_out))
				{
					memcpy(p_data, p_init_data,
						number_of_elements * stride_in_bytes);
					return true;
				}

				return false;
			}

			void kotek_render_static_buffer_pool::uploadData(
				VkCommandBuffer p_command) noexcept
			{
				KOTEK_ASSERT(p_command, "can't be invalid.");

				VkBufferCopy region;

				region.srcOffset = 0;
				region.dstOffset = 0;
				region.size = this->m_total_memory_size;

				vkCmdCopyBuffer(p_command, this->m_p_buffer,
					this->m_p_gpu_buffer, 1, &region);
			}

			void kotek_render_static_buffer_pool::freeUploadHeap(
				kotek_render_device* p_render_device)
			{
				if (this->m_is_use_video_memory)
				{
					VkDevice p_device = p_render_device->getDevice();

					KOTEK_ASSERT(
						p_device, "you must initialize device (VkDevice)");

					KOTEK_ASSERT(this->m_p_gpu_buffer,
						"you can't upload memory to gpu when you didn't "
						"initialze that buffer");

#ifdef kotek_USE_GPU_ALLOCATOR
					// TODO: VMA
#else
					vkUnmapMemory(p_device, this->m_p_device_memory);
					vkDestroyBuffer(p_device, this->m_p_buffer, nullptr);
					vkFreeMemory(p_device, this->m_p_device_memory, nullptr);
					this->m_p_device_memory = nullptr;
#endif

					this->m_p_buffer = nullptr;
				}
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
