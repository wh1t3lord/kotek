#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl3_3
{
	class ktkRenderStaticBufferPool_LinearAllocator
	{
	public:
		ktkRenderStaticBufferPool_LinearAllocator(void);
		~ktkRenderStaticBufferPool_LinearAllocator(void);

		void Initialize(ktk::uint32_t total_memory_size,
			ktk::uint32_t count_of_entity_elements,
			const char* vma_name_allocation);

		void Shutdown();

		bool AllocBuffer(ktk::entity_t entity_id,
			ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
			void** p_data) noexcept;

		bool Dealloc(ktk::entity_t entity_id) noexcept;

		bool IsNeedToRecalculate(void) const noexcept;

	private:
		bool AllocBuffer(ktk::entity_t entity_id, ktk::uint32_t size,
			void** p_data) noexcept;

	private:
		bool m_is_need_to_recalculate;
		ktk::uint32_t m_memory_offset;
		ktk::uint32_t m_total_memory;
		char* m_p_data;
		ktk::unordered_map<ktk::entity_t, ktk::uint32_t> m_entities_offset;
		ktk::unordered_map<ktk::entity_t, ktk::uint32_t>
			m_entities_vertex_size_with_stride;
	};
} // namespace gl3_3
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK