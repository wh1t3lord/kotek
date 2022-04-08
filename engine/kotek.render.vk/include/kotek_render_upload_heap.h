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
			class kotek_render_upload_heap
			{
			public:
				kotek_render_upload_heap(void);
				~kotek_render_upload_heap(void);

				void initialize(
					ktkRenderDevice* p_render_device, ktk::uint32_t size);
				void shutdown(ktkRenderDevice* p_render_device);

				ktk::uint8_t* subAllocate(ktk::size_t size) noexcept;
				ktk::uint8_t* beginSubAllocate(
					ktkRenderDevice* p_render_device,
					ktk::size_t size) noexcept;

				void endSubAllocate(void);

				void addCopy(
					VkImage p_image, VkBufferImageCopy p_image_copy) noexcept;
				void addPreBarrier(VkImageMemoryBarrier p_barrier) noexcept;
				void addPostBarrier(VkImageMemoryBarrier p_barrier) noexcept;

				void flush(ktkRenderDevice* p_render_device) noexcept;
				void flushAndFinish(
					ktkRenderDevice* p_render_device) noexcept;

				ktk::size_t getOffset(
					const ktk::uint8_t* const p_allocated_part_from_heap)
					const noexcept;

				ktk::uint8_t* getDataBegin(void) const noexcept;

				VkBuffer getBuffer(void) const noexcept;

				VkCommandBuffer getCommandBuffer(void) const noexcept;

			private:
				void createCommandPool(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyCommandPool(
					ktkRenderDevice* p_render_device) noexcept;

				void createBuffer(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyBuffer(
					ktkRenderDevice* p_render_device) noexcept;

				void createCommandBuffer(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyCommandBuffer(
					ktkRenderDevice* p_render_device) noexcept;

				void createFence(ktkRenderDevice* p_render_device) noexcept;
				void destroyFence(
					ktkRenderDevice* p_render_device) noexcept;

				void beginCommandBuffer(
					ktkRenderDevice* p_render_device) noexcept;

			private:
				ktk::uint32_t m_total_size;
				ktk::uint8_t* m_p_data_begin;
				ktk::uint8_t* m_p_data_current;
				ktk::uint8_t* m_p_data_end;
				ktk::size_t m_alignment;
				VkCommandPool m_p_command_pool;
				VkCommandBuffer m_p_command_buffer;
				VkBuffer m_p_buffer;
				VkDeviceMemory m_p_device_memory;
				VkFence m_p_fence;
				ktk::vector<VkImageMemoryBarrier> m_pre_barrier;
				ktk::vector<VkImageMemoryBarrier> m_post_barrier;
				ktk::vector<ktk::pair<VkImage, VkBufferImageCopy>>
					m_buffer_image_copies;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
