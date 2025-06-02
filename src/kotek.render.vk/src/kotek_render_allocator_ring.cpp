#include "../include/kotek_render_allocator_ring.h"
#include "../include/kotek_render_allocator_ring_with_tabs.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_allocator_ring_with_tabs::
				kotek_render_allocator_ring_with_tabs(void) :
				m_frame_buffer_index(0),
				m_frame_buffer_number(0), m_memory_allocated_in_frame(0)
			{
				for (ktk::uint32_t i = 0; i < 3; ++i)
				{
					this->m_p_allocated_memory_per_frame_buffer[i] = 0;
				}
			}

			kotek_render_allocator_ring_with_tabs::
				~kotek_render_allocator_ring_with_tabs(void)
			{
			}

			void kotek_render_allocator_ring_with_tabs::initialize(
				ktk::uint32_t number_of_frame_buffers,
				ktk::uint32_t total_size_memory) noexcept
			{
				this->m_frame_buffer_number = number_of_frame_buffers;
				this->m_allocator.create(total_size_memory);
			}

			void kotek_render_allocator_ring_with_tabs::shutdown(void) noexcept
			{
				this->m_allocator.do_free(this->m_allocator.getSize());
			}

			bool kotek_render_allocator_ring_with_tabs::alloc(
				ktk::uint32_t size, ktk::uint32_t* p_out) noexcept
			{
				ktk::uint32_t padding =
					this->m_allocator.makePaddingToAvoidCrossover(size);

				if (padding > 0)
				{
					this->m_memory_allocated_in_frame += padding;

					if (this->m_allocator.alloc(padding, nullptr) == false)
					{
						// can't allocate padding
						return false;
					}
				}

				if (this->m_allocator.alloc(size, p_out) == true)
				{
					this->m_memory_allocated_in_frame += size;
					return true;
				}

				return false;
			}

			void kotek_render_allocator_ring_with_tabs::OnBeginFrame(
				void) noexcept
			{
				this->m_p_allocated_memory_per_frame_buffer
					[this->m_frame_buffer_index] =
					this->m_memory_allocated_in_frame;
				this->m_memory_allocated_in_frame = 0;

				this->m_frame_buffer_index = (this->m_frame_buffer_index + 1) %
					this->m_frame_buffer_number;

				ktk::uint32_t memory_to_free =
					this->m_p_allocated_memory_per_frame_buffer
						[this->m_frame_buffer_index];

				this->m_allocator.do_free(memory_to_free);
			}

			kotek_render_allocator_ring::kotek_render_allocator_ring(void) :
				m_head(0), m_total_size(0), m_allocated_size(0)
			{
			}

			kotek_render_allocator_ring::~kotek_render_allocator_ring(void) {}

			void kotek_render_allocator_ring::create(
				ktk::uint32_t total_size) noexcept
			{
				this->m_total_size = total_size;
			}

			ktk::uint32_t
			kotek_render_allocator_ring::makePaddingToAvoidCrossover(
				ktk::uint32_t size) const noexcept
			{
				ktk::uint32_t tail = this->getTail();

				if ((tail + size) > this->m_total_size)
				{
					return (this->m_total_size - tail);
				}
				else
				{
					return static_cast<ktk::uint32_t>(0);
				}
			}

			ktk::uint32_t kotek_render_allocator_ring::getSize(
				void) const noexcept
			{
				return this->m_allocated_size;
			}

			ktk::uint32_t kotek_render_allocator_ring::getHead(
				void) const noexcept
			{
				return this->m_head;
			}

			ktk::uint32_t kotek_render_allocator_ring::getTail(
				void) const noexcept
			{
				return (this->m_head + this->m_allocated_size) %
					this->m_total_size;
			}

			bool kotek_render_allocator_ring::alloc(
				ktk::uint32_t size, ktk::uint32_t* p_out) noexcept
			{
				if (this->m_allocated_size + size <= this->m_total_size)
				{
					if (p_out)
					{
						*p_out = this->getTail();
					}

					this->m_allocated_size += size;

					return true;
				}

				KOTEK_ASSERT(false, "something is wrong see condition");

				return false;
			}

			bool kotek_render_allocator_ring::do_free(ktk::uint32_t size)
			{
				if (this->m_allocated_size >= size)
				{
					this->m_head = (this->m_head + size) % this->m_total_size;
					this->m_allocated_size -= size;

					return true;
				}

				return false;
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek