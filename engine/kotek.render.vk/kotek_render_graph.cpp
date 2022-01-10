#include "kotek_render_graph.h"
#include "../kotek.core/kotek_profiler.h"
#include "kotek_render_resource_manager.h"
#include "kotek_render_texture_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_graph::kotek_render_graph(
				const ktk::vector<kotek_render_graph_render_pass*>& passes,
				const ktk::vector<ktkRenderGraphNode>& nodes,
				kotek_render_command_list_ring* p_command_list_ring,
				ktkRenderDevice* p_device,
				Core::ktkProfiler* p_profiler) :
				m_passes(passes),
				m_nodes(nodes), m_p_command_list_ring(p_command_list_ring),
				m_p_render_device(p_device),
				m_p_profiler(p_profiler)
			{
				KOTEK_ASSERT(this->m_passes.empty() == false,
					"you can't create render graph without any passes!");

				KOTEK_ASSERT(this->m_nodes.empty() == false,
					"can't be render graph builder must create at least one "
					"node");

				KOTEK_ASSERT(this->m_passes.size() == this->m_nodes.size(),
					"your nodes and passes must be equal by size!!! Nodes are "
					"based on your pass handles");

				KOTEK_ASSERT(this->m_p_command_list_ring,
					"you must initialize command list ring");

				KOTEK_ASSERT(this->m_p_render_device,
					"you must initialize render device");
			}

			kotek_render_graph::kotek_render_graph(void) : m_p_profiler(nullptr)
			{
			}

			kotek_render_graph::~kotek_render_graph(void) {}

			void kotek_render_graph::initialize(void) {}

			void kotek_render_graph::shutdown(void)
			{
				KOTEK_CPU_PROFILE();

				for (auto*& p_item : this->m_passes)
				{
#ifdef KOTEK_DEBUG
					KOTEK_MESSAGE("deleting render pass {}",
						p_item->getName().get_as_is());
#endif
					delete p_item;
					p_item = nullptr;
				}

				this->m_passes.clear();

				this->m_p_command_list_ring->Shutdown(this->m_p_render_device);
				delete this->m_p_command_list_ring;

				this->m_p_command_list_ring = nullptr;
			}

			void kotek_render_graph::UpdateAll(void)
			{
				for (auto*& p_pass : this->m_passes)
				{
					p_pass->onUpdate();
				}
			}

			void kotek_render_graph::RenderAll(void)
			{
				ktk::size_t index = 0;

				VkCommandBufferBeginInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
				info.pInheritanceInfo = nullptr;

				for (auto*& p_pass : this->m_passes)
				{
					VkCommandBuffer p_command_buffer =
						this->m_p_command_list_ring->GetNewCommandList(this->m_p_render_device);

					auto status = vkBeginCommandBuffer(p_command_buffer, &info);

					KOTEK_ASSERT(status == VkResult::VK_SUCCESS,
						"failed to vkBeginCommandBuffer");

					p_pass->onRender(this->m_nodes.at(index), p_command_buffer);

					++index;
				}

				// TODO: task group for waiting...

				const auto& all_buffers =
					this->m_p_command_list_ring
						->GetAllCommandsBufferForCurrentFrame();
				
				ktk::uint32_t all_count =
					this->m_p_command_list_ring
						->GetCountOfCommandBuffersPerFrame();

				VkResult status = VkResult::VK_SUCCESS;
				for (ktk::uint32_t current_buffer_index = 0;
					 current_buffer_index < all_count; ++current_buffer_index)
				{
					status =
						vkEndCommandBuffer(all_buffers[current_buffer_index]);

					KOTEK_ASSERT(status == VkResult::VK_SUCCESS, "failed to vkEndCommandBuffer");
				}

			}

			ktk::uint32_t kotek_render_graph::GetNodesCount(void) const noexcept
			{
				return this->m_nodes.size();
			}

			kotek_render_command_list_ring*
			kotek_render_graph::GetCommandListRing(void) const noexcept
			{
				return this->m_p_command_list_ring;
			}
		} // namespace vk
	}     // namespace Render
} // namespace Kotek