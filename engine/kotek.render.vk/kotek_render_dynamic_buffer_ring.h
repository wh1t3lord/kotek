#pragma once

#include "../kotek.core/kotek_std.h"
#include "kotek_render_allocator_ring_with_tabs.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_device;
		}
	} // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			// TODO: should user specifies his descriptor type when he updates
			// descriptor???
			class kotek_render_dynamic_buffer_ring
			{
			public:
				kotek_render_dynamic_buffer_ring(void);
				~kotek_render_dynamic_buffer_ring(void);

				void initialize(kotek_render_device* p_render_device,
					ktk::uint32_t number_of_back_buffers,
					ktk::uint32_t memory_total_size,
					const ktk::string& debug_name) noexcept;

				void shutdown(kotek_render_device* p_render_device) noexcept;

				bool allocConstantBuffer(ktk::uint32_t size, void** p_data,
					VkDescriptorBufferInfo* p_out) noexcept;

				bool allocVertexBuffer(ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, void** p_data,
					VkDescriptorBufferInfo* p_out) noexcept;

				bool allocIndexBuffer(ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, void** p_data,
					VkDescriptorBufferInfo* p_out) noexcept;

				void OnBeginFrame(void);

				void SetDescriptorSet(kotek_render_device* p_render_device,
					ktk::uint32_t binding_index, ktk::uint32_t size, VkDescriptorType descriptor_type,
					VkDescriptorSet p_set) noexcept;

				void SetDescriptorSet(kotek_render_device* p_render_device,
					ktk::uint32_t binding_index, VkSampler p_sampler,
					VkImageLayout layout, VkImageView p_view, VkDescriptorType descriptor_type,
					VkDescriptorSet p_set) noexcept;

			private:
				ktk::uint32_t m_memory_total_size;
				char* m_p_data;
				VkBuffer m_p_buffer;
#ifdef kotek_USE_GPU_ALLOCATOR
#else
				VkDeviceMemory m_p_memory;
#endif
				kotek_render_allocator_ring_with_tabs m_allocator;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
