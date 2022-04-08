#pragma once

#include <kotek.core/include/kotek_std.h>

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderDevice;
		}
	} // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderStaticBufferPool_LinearAllocator
			{
			public:
				ktkRenderStaticBufferPool_LinearAllocator(void);
				~ktkRenderStaticBufferPool_LinearAllocator(void);

				void Initialize(ktkRenderDevice* p_render_device,
					ktk::uint32_t total_memory_size,
					ktk::uint32_t count_of_entity_elements,
					const char* vma_name_allocation);

				void Shutdown(ktkRenderDevice* p_render_device);

				bool AllocBuffer(ktk::entity_t entity_id,
					ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, void** p_data,
					VkDescriptorBufferInfo* p_out) noexcept;

				bool Dealloc(ktk::entity_t entity_id) noexcept;

				bool IsNeedToRecalculate(void) const noexcept;

			private:
				bool AllocBuffer(ktk::entity_t entity_id, ktk::uint32_t size,
					void** p_data, VkDescriptorBufferInfo* p_out) noexcept;

			private:
				bool m_is_need_to_recalculate;
				ktk::uint32_t m_memory_offset;
				ktk::uint32_t m_total_memory;
				VkBuffer m_p_buffer;
				char* m_p_data;
				ktk::unordered_map<ktk::entity_t, ktk::uint32_t>
					m_entities_offset;
				ktk::unordered_map<ktk::entity_t, ktk::uint32_t>
					m_entities_vertex_size_with_stride;
				VmaAllocation m_buffer_allocation;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
