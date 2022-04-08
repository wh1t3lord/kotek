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
			// TODO: make multithreded safety here, some atomics are required
			class kotek_render_command_list_ring
			{
				class command_buffer_per_frame_t
				{
				public:
					command_buffer_per_frame_t(void);
					~command_buffer_per_frame_t(void);

					ktk::uint32_t GetUsedCalls(void) const noexcept;

					void SetUsedCalls(ktk::uint32_t number) noexcept;

					void SetCountCommandListsAndPools(
						ktk::uint32_t number) noexcept;

					const ktk::vector<VkCommandPool>& GetCommandPools(void) const noexcept;

					const ktk::vector<VkCommandBuffer>& GetCommandBuffers(void) const noexcept;

					void AddCommandPools(
						VkCommandPool p_command_pool) noexcept;

					void AddCommandBuffers(VkCommandBuffer p_buffer) noexcept;

				private:
					ktk::uint32_t m_used_calls;
					ktk::uint32_t m_number_per_frame_command_lists;
					ktk::vector<VkCommandPool> m_command_pools;
					ktk::vector<VkCommandBuffer> m_command_buffers;
				};

			public:
				kotek_render_command_list_ring(void);
				~kotek_render_command_list_ring(void);

				void initialize(ktkRenderDevice* p_render_device,
					ktk::uint32_t number_of_back_buffers,
					ktk::uint32_t command_list_per_frame,
					bool is_compute = false) noexcept;

				void Shutdown(ktkRenderDevice* p_render_device);

				void OnBeginFrame();

				VkCommandBuffer GetNewCommandList(ktkRenderDevice* p_device);

				const ktk::vector<VkCommandBuffer>& GetAllCommandsBufferForCurrentFrame(
					void) const noexcept;

				ktk::uint32_t GetCountOfCommandBuffersPerFrame(
					void) const noexcept;

			private:
				ktk::uint32_t m_frame_index;
				ktk::uint32_t m_number_of_frames;
				ktk::uint32_t m_command_lists_per_frame;

				ktk::vector<command_buffer_per_frame_t> m_frames;
				command_buffer_per_frame_t* m_p_current_frame;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
