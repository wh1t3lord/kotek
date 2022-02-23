#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class kotek_render_static_buffer_pool
			{
			public:
				kotek_render_static_buffer_pool(void);
				~kotek_render_static_buffer_pool(void);

				void initialize(ktk::uint32_t total_memory_size, bool is_use_gpu_memory,
					const ktk::string& vma_name_allocation);

				void shutdown();

				bool allocBuffer(ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, void** p_data) noexcept;

				bool allocBuffer(ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, const void** p_init_data) noexcept;

				void uploadData() noexcept;

				void freeUploadHeap();

			private:
				bool m_is_use_video_memory;
				ktk::uint32_t m_memory_offset;
				ktk::uint32_t m_total_memory_size;
				char* m_p_data;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
