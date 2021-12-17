#pragma once

#include "../kotek.core/kotek_std.h"

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
			class kotek_render_static_buffer_pool
			{
			public:
				kotek_render_static_buffer_pool(void);
				~kotek_render_static_buffer_pool(void);

				void initialize(kotek_render_device* p_render_device,
					ktk::uint32_t total_memory_size, bool is_use_gpu_memory,
					const ktk::string& vma_name_allocation);

				void shutdown(kotek_render_device* p_render_device);

				bool allocBuffer(ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, void** p_data,
					VkDescriptorBufferInfo* p_out) noexcept;

				bool allocBuffer(ktk::uint32_t number_of_elements,
					ktk::uint32_t stride_in_bytes, const void** p_init_data,
					VkDescriptorBufferInfo* p_out) noexcept;

				void uploadData(VkCommandBuffer p_command) noexcept;

				void freeUploadHeap(kotek_render_device* p_render_device);

			private:
				bool m_is_use_video_memory;
				ktk::uint32_t m_memory_offset;
				ktk::uint32_t m_total_memory_size;
				char* m_p_data;
				VkBuffer m_p_buffer;
				VkBuffer m_p_gpu_buffer;

#ifdef kotek_USE_GPU_ALLOCATOR
				// TODO: VMA here
#else
				VkDeviceMemory m_p_device_memory;
				VkDeviceMemory m_p_device_gpu_memory;
#endif
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
