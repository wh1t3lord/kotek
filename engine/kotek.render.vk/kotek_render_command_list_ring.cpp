#include "kotek_render_command_list_ring.h"
#include "kotek_render_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_command_list_ring::kotek_render_command_list_ring() :
				m_p_current_frame(nullptr)
			{
			}

			kotek_render_command_list_ring::~kotek_render_command_list_ring() {}

			void kotek_render_command_list_ring::initialize(
				kotek_render_device* p_render_device,
				ktk::uint32_t number_of_back_buffers,
				ktk::uint32_t command_list_per_frame, bool is_compute) noexcept
			{
				KOTEK_ASSERT(number_of_back_buffers, "must be positive number");

				this->m_number_of_frames = number_of_back_buffers;
				this->m_command_lists_per_frame = command_list_per_frame;

				this->m_frames.resize(this->m_number_of_frames);

				for (ktk::uint32_t current_frame_index = 0;
					 current_frame_index < this->m_number_of_frames;
					 ++current_frame_index)
				{
					command_buffer_per_frame_t* p_current_buffer =
						&this->m_frames[current_frame_index];

					p_current_buffer->SetCountCommandListsAndPools(
						command_list_per_frame);

					for (ktk::uint32_t current_command_buffer_index = 0;
						 current_command_buffer_index <
						 this->m_command_lists_per_frame;
						 ++current_command_buffer_index)
					{
						VkCommandPoolCreateInfo info_pool = {};

						info_pool.sType =
							VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
						info_pool.pNext = nullptr;

						if (is_compute)
						{
							info_pool.queueFamilyIndex =
								p_render_device->getFamilyQueueIndex_Compute();
						}
						else
						{
							info_pool.queueFamilyIndex =
								p_render_device->getFamilyQueueIndex_Graphics();
						}

						info_pool.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

						VkCommandPool p_pool = nullptr;

						VkResult status =
							vkCreateCommandPool(p_render_device->getDevice(),
								&info_pool, nullptr, &p_pool);

						KOTEK_ASSERT(
							status == VK_SUCCESS, "can't create command pool");

						p_current_buffer->AddCommandPools(p_pool);

						VkCommandBufferAllocateInfo info_buffer = {};

						info_buffer.sType =
							VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
						info_buffer.pNext = nullptr;
						info_buffer.commandPool =
							p_current_buffer->GetCommandPools()
								[current_command_buffer_index];
						info_buffer.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
						info_buffer.commandBufferCount = 1;

						VkCommandBuffer p_buffer = nullptr;

						status = vkAllocateCommandBuffers(
							p_render_device->getDevice(), &info_buffer,
							&p_buffer);

						KOTEK_ASSERT(status == VK_SUCCESS,
							"failed to fill command buffers");

						p_current_buffer->AddCommandBuffers(p_buffer);
					}
				}

				this->m_frame_index = 0;
				this->m_p_current_frame = &this->m_frames[this->m_frame_index %
					this->m_number_of_frames];

				this->m_p_current_frame->SetUsedCalls(0);
			}

			void kotek_render_command_list_ring::Shutdown(
				kotek_render_device* p_render_device)
			{
				for (ktk::uint32_t i = 0; i < this->m_number_of_frames; ++i)
				{
					for (ktk::uint32_t j = 0;
						 j < this->m_command_lists_per_frame; ++j)
					{
						vkFreeCommandBuffers(p_render_device->getDevice(),
							this->m_frames.at(i).GetCommandPools().at(j), 1,
							&this->m_frames[i].GetCommandBuffers().at(j));

						vkDestroyCommandPool(p_render_device->getDevice(),
							this->m_frames.at(i).GetCommandPools().at(j),
							nullptr);
					}
				}
			}

			void kotek_render_command_list_ring::OnBeginFrame()
			{
				this->m_p_current_frame = &this->m_frames.at(
					this->m_frame_index % this->m_number_of_frames);

				this->m_p_current_frame->SetUsedCalls(0);

				++this->m_frame_index;
			}

			VkCommandBuffer kotek_render_command_list_ring::GetNewCommandList(
				kotek_render_device* p_device)
			{
				ktk::uint32_t current_call =
					this->m_p_current_frame->GetUsedCalls();

				auto status = vkResetCommandPool(p_device->getDevice(),
					this->m_p_current_frame->GetCommandPools().at(current_call),
					0);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "failed to vkResetCommandPool");

				VkCommandBuffer result =
					this->m_p_current_frame->GetCommandBuffers().at(
						current_call);

				KOTEK_ASSERT(this->m_p_current_frame->GetUsedCalls() <
						this->m_command_lists_per_frame,
					"! overflow, you must call getNewCommandList only for that "
					"count "
					"of real callings. For example if you have only two calls "
					"of "
					"getNewCommandList your must initialize this class with "
					"command_list_per_frame=2");

				++current_call;
				this->m_p_current_frame->SetUsedCalls(current_call);

				return result;
			}

			const ktk::vector<VkCommandBuffer>&
			kotek_render_command_list_ring::GetAllCommandsBufferForCurrentFrame(
				void) const noexcept
			{
				KOTEK_ASSERT(this->m_p_current_frame,
					"you must have a current frame's valid pointer");

				return this->m_p_current_frame->GetCommandBuffers();
			}

			ktk::uint32_t
			kotek_render_command_list_ring::GetCountOfCommandBuffersPerFrame(
				void) const noexcept
			{
				return this->m_command_lists_per_frame;
			}

			kotek_render_command_list_ring::command_buffer_per_frame_t::
				command_buffer_per_frame_t(void) :
				m_used_calls(0),
				m_number_per_frame_command_lists(0)
			{
			}

			kotek_render_command_list_ring::command_buffer_per_frame_t::
				~command_buffer_per_frame_t(void)
			{
			}

			ktk::uint32_t kotek_render_command_list_ring::
				command_buffer_per_frame_t::GetUsedCalls(void) const noexcept
			{
				return this->m_used_calls;
			}

			void kotek_render_command_list_ring::command_buffer_per_frame_t::
				SetUsedCalls(ktk::uint32_t number) noexcept
			{
				this->m_used_calls = number;
			}

			void kotek_render_command_list_ring::command_buffer_per_frame_t::
				SetCountCommandListsAndPools(ktk::uint32_t number) noexcept
			{
				this->m_number_per_frame_command_lists = number;
			}

			const ktk::vector<VkCommandPool>& kotek_render_command_list_ring::
				command_buffer_per_frame_t::GetCommandPools(void) const noexcept
			{
				return this->m_command_pools;
			}

			const ktk::vector<VkCommandBuffer>& kotek_render_command_list_ring::
				command_buffer_per_frame_t::GetCommandBuffers(
					void) const noexcept
			{
				return this->m_command_buffers;
			}

			void kotek_render_command_list_ring::command_buffer_per_frame_t::
				AddCommandPools(VkCommandPool p_command_pool) noexcept
			{
				this->m_command_pools.push_back(p_command_pool);
			}

			void kotek_render_command_list_ring::command_buffer_per_frame_t::
				AddCommandBuffers(VkCommandBuffer p_buffer) noexcept
			{
				this->m_command_buffers.push_back(p_buffer);
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
