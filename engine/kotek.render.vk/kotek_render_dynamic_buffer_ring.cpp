#include "kotek_render_dynamic_buffer_ring.h"
#include "kotek_render_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_dynamic_buffer_ring::kotek_render_dynamic_buffer_ring()
			{
			}

			kotek_render_dynamic_buffer_ring::
				~kotek_render_dynamic_buffer_ring()
			{
			}

			void kotek_render_dynamic_buffer_ring::initialize(
				kotek_render_device* p_render_device,
				ktk::uint32_t number_of_back_buffers,
				ktk::uint32_t memory_total_size,
				const ktk::string& debug_name) noexcept
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				this->m_memory_total_size =
					ktk::align_up(memory_total_size, 256u);
				this->m_allocator.initialize(
					number_of_back_buffers, this->m_memory_total_size);

#ifdef kotek_USE_GPU_ALLOCATOR
				// TODO: VMA
#else
				VkBufferCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				info.pNext = nullptr;
				info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
					VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
					VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
				info.size = this->m_memory_total_size;
				info.queueFamilyIndexCount = 0;
				info.pQueueFamilyIndices = nullptr;
				info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				info.flags = 0;

				VkResult status =
					vkCreateBuffer(p_device, &info, nullptr, &this->m_p_buffer);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't create buffer. See status");

				VkMemoryRequirements memory_requirements;

				vkGetBufferMemoryRequirements(
					p_device, this->m_p_buffer, &memory_requirements);

				VkMemoryAllocateInfo info_alloc = {};

				info_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				info_alloc.pNext = nullptr;
				info_alloc.allocationSize = memory_requirements.size;
				info_alloc.memoryTypeIndex = 0;

				bool is_valid = p_render_device->isMemoryTypeFromProperties(
					p_render_device->getCurrentPhysicalDeviceMemoryProperties(),
					memory_requirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
						VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					&info_alloc.memoryTypeIndex);

				KOTEK_ASSERT(is_valid, "no mappable, coherent memory");

				status = vkAllocateMemory(
					p_device, &info_alloc, nullptr, &this->m_p_memory);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't allocate memory. See status");

				status = vkMapMemory(p_device, this->m_p_memory, 0,
					memory_requirements.size, 0,
					reinterpret_cast<void**>(&this->m_p_data));

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't map memory. See status");

				status = vkBindBufferMemory(
					p_device, this->m_p_buffer, this->m_p_memory, 0);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't bind memory. See status");
#endif
			}

			void kotek_render_dynamic_buffer_ring::shutdown(
				kotek_render_device* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

#ifdef kotek_USE_GPU_ALLOCATOR
				// TODO: VMA
#else
				vkUnmapMemory(p_device, this->m_p_memory);
				vkDestroyBuffer(p_device, this->m_p_buffer, nullptr);
				vkFreeMemory(p_device, this->m_p_memory, nullptr);

#endif

				this->m_allocator.shutdown();
			}

			bool kotek_render_dynamic_buffer_ring::allocConstantBuffer(
				ktk::uint32_t size, void** p_data,
				VkDescriptorBufferInfo* p_out) noexcept
			{
				size = ktk::align_up(size, 256u);

				ktk::uint32_t memory_offset = 0;

				if (this->m_allocator.alloc(size, &memory_offset) == false)
				{
					KOTEK_ASSERT(false,
						"Ran out of mem for 'dynamic' buffers, please increase "
						"the allocated size");

					return false;
				}

				*p_data =
					reinterpret_cast<void*>(this->m_p_data + memory_offset);

				p_out->buffer = this->m_p_buffer;
				p_out->offset = memory_offset;
				p_out->range = size;

				return true;
			}

			bool kotek_render_dynamic_buffer_ring::allocVertexBuffer(
				ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
				void** p_data, VkDescriptorBufferInfo* p_out) noexcept
			{
				return this->allocConstantBuffer(
					number_of_elements * stride_in_bytes, p_data, p_out);
			}

			bool kotek_render_dynamic_buffer_ring::allocIndexBuffer(
				ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
				void** p_data, VkDescriptorBufferInfo* p_out) noexcept
			{
				return this->allocConstantBuffer(
					number_of_elements * stride_in_bytes, p_data, p_out);
			}

			void kotek_render_dynamic_buffer_ring::OnBeginFrame()
			{
				this->m_allocator.OnBeginFrame();
			}

			void kotek_render_dynamic_buffer_ring::SetDescriptorSet(
				kotek_render_device* p_render_device,
				ktk::uint32_t binding_index, ktk::uint32_t size,
				VkDescriptorType descriptor_type,
				VkDescriptorSet p_set) noexcept
			{
				KOTEK_ASSERT(
					p_render_device, "you can't pass invalid render device");

				KOTEK_ASSERT(
					p_set, "you can't pass an invalid VkDescriptorSet pointer");

				VkDescriptorBufferInfo info = {};

				info.buffer = this->m_p_buffer;
				info.offset = 0;
				info.range = size;

				VkWriteDescriptorSet write = {};

				write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				write.pNext = nullptr;
				write.dstSet = p_set;
				write.descriptorCount = 1;
				write.descriptorType =
					descriptor_type;
				write.pBufferInfo = &info;
				write.dstArrayElement = 0;
				write.dstBinding = binding_index;

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkUpdateDescriptorSets(p_device, 1, &write, 0, nullptr);
			}

			void kotek_render_dynamic_buffer_ring::SetDescriptorSet(
				kotek_render_device* p_render_device,
				ktk::uint32_t binding_index, VkSampler p_sampler,
				VkImageLayout layout, VkImageView p_view,
				VkDescriptorType descriptor_type,
				VkDescriptorSet p_set) noexcept
			{
				KOTEK_ASSERT(
					p_render_device, "you can't pass an invalid render device");

				KOTEK_ASSERT(p_sampler, "you can't pass an invalid VkSampler");

				KOTEK_ASSERT(p_view, "you can't pass an invalid VkImageView");

				KOTEK_ASSERT(p_set, "you can't pass an invalid VkDescritorSet");

				VkDescriptorImageInfo info = {};

				info.sampler = p_sampler;
				info.imageLayout = layout;
				info.imageView = p_view;

				VkWriteDescriptorSet writes[1];

				writes[0] = {};

				writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				writes[0].pNext = nullptr;
				writes[0].descriptorType =
					descriptor_type;
				writes[0].descriptorCount = 1;
				writes[0].dstSet = p_set;
				writes[0].dstBinding = binding_index;
				writes[0].dstArrayElement = 0;
				writes[0].pImageInfo = &info;

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you can't have an invalid VkDevice instance, initialize "
					"render device first!");

				vkUpdateDescriptorSets(p_device, 1, writes, 0, nullptr);
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
