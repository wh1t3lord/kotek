#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl3_3
{
	class kotek_render_allocator_ring
	{
	public:
		kotek_render_allocator_ring(void);
		~kotek_render_allocator_ring(void);

		void create(ktk::uint32_t total_size) noexcept;

		ktk::uint32_t makePaddingToAvoidCrossover(
			ktk::uint32_t size) const noexcept;

		ktk::uint32_t getSize(void) const noexcept;
		ktk::uint32_t getHead(void) const noexcept;
		ktk::uint32_t getTail(void) const noexcept;

		bool alloc(ktk::uint32_t size, ktk::uint32_t* p_out) noexcept;

		bool do_free(ktk::uint32_t size);

	private:
		ktk::uint32_t m_head;
		ktk::uint32_t m_total_size;
		ktk::uint32_t m_allocated_size;
	};
} // namespace gl3_3
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
