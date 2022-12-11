#pragma once

#include "kotek_render_allocator_ring.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class kotek_render_allocator_ring_with_tabs
	{
	public:
		kotek_render_allocator_ring_with_tabs(void);
		~kotek_render_allocator_ring_with_tabs(void);

		void initialize(ktk::uint32_t number_of_frame_buffers,
			ktk::uint32_t total_size_memory) noexcept;

		void shutdown(void) noexcept;

		bool alloc(ktk::uint32_t size, ktk::uint32_t* p_out) noexcept;

		void OnBeginFrame(void) noexcept;

	private:
		ktk::uint32_t m_frame_buffer_index;
		ktk::uint32_t m_frame_buffer_number;
		ktk::uint32_t m_memory_allocated_in_frame;
		kotek_render_allocator_ring m_allocator;

		// TODO: load info from sys_info.json
		ktk::uint32_t m_p_allocated_memory_per_frame_buffer[3];
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
