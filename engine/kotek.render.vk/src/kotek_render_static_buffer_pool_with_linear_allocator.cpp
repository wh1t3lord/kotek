#include "../include/kotek_render_static_buffer_pool_with_linear_allocator.h"
#include "../include/kotek_render_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			ktkRenderStaticBufferPool_LinearAllocator::
				ktkRenderStaticBufferPool_LinearAllocator(void) :
				m_is_need_to_recalculate{false},
				m_memory_offset{}, m_total_memory{}, m_p_buffer{}, m_p_data{},
				m_buffer_allocation{}
			{
			}

			ktkRenderStaticBufferPool_LinearAllocator::
				~ktkRenderStaticBufferPool_LinearAllocator(void)
			{
			}

			void ktkRenderStaticBufferPool_LinearAllocator::Initialize(
				ktkRenderDevice* p_render_device,
				ktk::uint32_t total_memory_size,
				ktk::uint32_t count_of_entity_elements,
				const char* vma_name_allocation)
			{
				VkResult status = VK_ERROR_UNKNOWN;

				this->m_total_memory = total_memory_size;
				this->m_p_data = nullptr;
				this->m_memory_offset = 0;

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				VkBufferCreateInfo info_buffer = {};

				info_buffer.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				info_buffer.size = this->m_total_memory;
				info_buffer.usage =
					VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
					VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

				VmaAllocationCreateInfo info_alloc = {};
				info_alloc.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
				info_alloc.flags =
					VMA_ALLOCATION_CREATE_USER_DATA_COPY_STRING_BIT;
				info_alloc.pUserData = const_cast<char*>(vma_name_allocation);

				status = vmaCreateBuffer(p_render_device->GetAllocator(),
					&info_buffer, &info_alloc, &this->m_p_buffer,
					&this->m_buffer_allocation, nullptr);

				KOTEK_ASSERT(status == VkResult::VK_SUCCESS,
					"failed to vmaCreateBuffer");

				p_render_device->GetHelper().getDebug().setDebugNameToResource(
					p_device, VkObjectType::VK_OBJECT_TYPE_BUFFER,
					this->m_p_buffer, vma_name_allocation);

				status = vmaMapMemory(p_render_device->GetAllocator(),
					this->m_buffer_allocation,
					reinterpret_cast<void**>(&this->m_p_data));

				KOTEK_ASSERT(
					status == VkResult::VK_SUCCESS, "failed to vmaMapMemory");

				this->m_entities_offset.reserve(count_of_entity_elements);
				this->m_entities_vertex_size_with_stride.reserve(
					count_of_entity_elements);

				KOTEK_MESSAGE("allocated static buffer {} pool with {} Mbs",
					ktk::string(vma_name_allocation).get_as_is(),
					total_memory_size / ktk::kMemoryConvertValue_Megabytes);
			}

			void ktkRenderStaticBufferPool_LinearAllocator::Shutdown(
				ktkRenderDevice* p_render_device)
			{
				KOTEK_ASSERT(p_render_device,
					"you have to pass a valid object of ktkRenderDevice");

				if (this->m_p_buffer)
				{
					vmaUnmapMemory(p_render_device->GetAllocator(),
						this->m_buffer_allocation);
					vmaDestroyBuffer(p_render_device->GetAllocator(),
						this->m_p_buffer, this->m_buffer_allocation);
					this->m_p_buffer = nullptr;
				}
			}

			bool ktkRenderStaticBufferPool_LinearAllocator::AllocBuffer(
				ktk::entity_t entity_id, ktk::uint32_t number_of_elements,
				ktk::uint32_t stride_in_bytes, void** p_data,
				VkDescriptorBufferInfo* p_out) noexcept
			{
				return this->AllocBuffer(entity_id,
					ktk::align_up<ktk::uint32_t>(
						number_of_elements * stride_in_bytes, 256u),
					p_data, p_out);
			}

			bool ktkRenderStaticBufferPool_LinearAllocator::Dealloc(
				ktk::entity_t entity_id) noexcept
			{
				if (this->m_entities_offset.find(entity_id) ==
					this->m_entities_offset.end())
					return false;

				KOTEK_ASSERT(
					!(this->m_entities_vertex_size_with_stride.find(
						  entity_id) ==
						this->m_entities_vertex_size_with_stride.end()),
					"can't be");

				this->m_memory_offset = 0;
				this->m_entities_offset.clear();

				this->m_entities_vertex_size_with_stride.erase(entity_id);

				this->m_is_need_to_recalculate = true;

				return true;
			}

			bool ktkRenderStaticBufferPool_LinearAllocator::IsNeedToRecalculate(
				void) const noexcept
			{
				return this->m_is_need_to_recalculate;
			}

			bool ktkRenderStaticBufferPool_LinearAllocator::AllocBuffer(
				ktk::entity_t entity_id, ktk::uint32_t size, void** p_data,
				VkDescriptorBufferInfo* p_out) noexcept
			{
				if (this->m_entities_offset.find(entity_id) !=
					this->m_entities_offset.end())
					return false;

				KOTEK_ASSERT(
					this->m_memory_offset + size < this->m_total_memory,
					"Memory is overflowed. You need to increase size of pool "
					"when initializing");

				*p_data = reinterpret_cast<void*>(
					this->m_p_data + this->m_memory_offset);

				p_out->buffer = this->m_p_buffer;
				p_out->offset = this->m_memory_offset;
				p_out->range = size;

				this->m_entities_offset[entity_id] = this->m_memory_offset;
				this->m_entities_vertex_size_with_stride[entity_id] = size;

				this->m_memory_offset += size;

				return true;
			}
		} // namespace vk
	}     // namespace Render
} // namespace Kotek