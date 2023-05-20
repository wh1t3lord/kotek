#include "../include/kotek_render_static_buffer_pool.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	kotek_render_static_buffer_pool::kotek_render_static_buffer_pool() :
		m_memory_offset(0), m_total_memory_size(0), m_p_data(nullptr)

	{
	}

	kotek_render_static_buffer_pool::~kotek_render_static_buffer_pool() {}

	void kotek_render_static_buffer_pool::initialize(
		ktk::uint32_t total_memory_size, bool is_use_gpu_memory,
		const ktk::ustring& vma_name_allocation)
	{
	}

	void kotek_render_static_buffer_pool::shutdown() {}

	bool kotek_render_static_buffer_pool::allocBuffer(
		ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
		void** p_data) noexcept
	{
		// TODO: cpu sync here, because multithreading
		// TODO: add stats for counting allocations

		return true;
	}

	bool kotek_render_static_buffer_pool::allocBuffer(
		ktk::uint32_t number_of_elements, ktk::uint32_t stride_in_bytes,
		const void** p_init_data) noexcept
	{
		return false;
	}

	void kotek_render_static_buffer_pool::uploadData() noexcept {}

	void kotek_render_static_buffer_pool::freeUploadHeap() {}

} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK