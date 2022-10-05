#include "../include/kotek_render_static_buffer_pool_with_linear_allocator.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl3_3
{
	ktkRenderStaticBufferPool_LinearAllocator::
		ktkRenderStaticBufferPool_LinearAllocator(void) :
		m_is_need_to_recalculate{false},
		m_memory_offset{}, m_total_memory{}, m_p_data{}
	{
	}

	ktkRenderStaticBufferPool_LinearAllocator::
		~ktkRenderStaticBufferPool_LinearAllocator(void)
	{
	}

	void ktkRenderStaticBufferPool_LinearAllocator::Initialize(
		ktk::uint32_t total_memory_size, ktk::uint32_t count_of_entity_elements,
		const char* vma_name_allocation)
	{
	}

	void ktkRenderStaticBufferPool_LinearAllocator::Shutdown() {}

	bool ktkRenderStaticBufferPool_LinearAllocator::AllocBuffer(
		ktk::entity_t entity_id, ktk::uint32_t number_of_elements,
		ktk::uint32_t stride_in_bytes, void** p_data) noexcept
	{
		return this->AllocBuffer(entity_id,
			ktk::align_up<ktk::uint32_t>(
				number_of_elements * stride_in_bytes, 256u),
			p_data);
	}

	bool ktkRenderStaticBufferPool_LinearAllocator::Dealloc(
		ktk::entity_t entity_id) noexcept
	{
		if (this->m_entities_offset.find(entity_id) ==
			this->m_entities_offset.end())
			return false;

		KOTEK_ASSERT(
			!(this->m_entities_vertex_size_with_stride.find(entity_id) ==
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
		ktk::entity_t entity_id, ktk::uint32_t size, void** p_data) noexcept
	{
		if (this->m_entities_offset.find(entity_id) !=
			this->m_entities_offset.end())
			return false;

		KOTEK_ASSERT(this->m_memory_offset + size < this->m_total_memory,
			"Memory is overflowed. You need to increase size of pool "
			"when initializing");

		*p_data =
			reinterpret_cast<void*>(this->m_p_data + this->m_memory_offset);

		/* delete
		                p_out->buffer = this->m_p_buffer;
		                p_out->offset = this->m_memory_offset;
		                p_out->range = size;*/

		this->m_entities_offset[entity_id] = this->m_memory_offset;
		this->m_entities_vertex_size_with_stride[entity_id] = size;

		this->m_memory_offset += size;

		return true;
	}
} // namespace gl3_3
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK