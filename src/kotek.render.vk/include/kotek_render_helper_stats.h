#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_helper_stats
			{
			public:
				kotek_render_helper_stats(void);
				~kotek_render_helper_stats(void);

			private:
				ktk::uint64_t m_total_count_of_textures;
				ktk::uint64_t m_total_count_of_geometry_by_models;
				ktk::uint64_t m_total_memory_textures;
				ktk::uint64_t m_total_memory_geometry;
				ktk::uint64_t m_total_memory_size;
				ktk::uint64_t m_the_most_smallest_texture_size;
				ktk::uint64_t m_the_most_highest_texture_size;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek