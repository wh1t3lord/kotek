#include "../include/kotek_render_graph_data_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			ktkRenderGraphNode::ktkRenderGraphNode(
				const ktk::string& render_pass_name, VkRenderPass p_pass,
				VkFramebuffer p_frame_buffer,
				const ktk::unordered_map<ktk::string, VkPipeline>& pipelines,
				const ktk::unordered_map<ktk::string,
					ktk::vector<VkDescriptorSet>>& pipelines_descriptor_sets,
				const ktk::unordered_map<ktk::string, VkPipelineLayout>&
					pipelines_layout) :
				m_p_render_pass(p_pass),
				m_p_frame_buffer(p_frame_buffer),
				m_render_pass_name(render_pass_name), m_pipelines(pipelines),
				m_pipeline_descriptor_sets(pipelines_descriptor_sets),
				m_pipelines_layout(pipelines_layout)
			{
			}

			ktkRenderGraphNode::ktkRenderGraphNode(void) :
				m_p_frame_buffer(nullptr), m_p_render_pass(nullptr)
			{
			}

			ktkRenderGraphNode::~ktkRenderGraphNode(void) {}

			VkPipeline ktkRenderGraphNode::GetPipeline(
				const ktk::string& pipeline_name) const noexcept
			{
				KOTEK_ASSERT(pipeline_name.empty() == false,
					"you can't pass an empty string");

				KOTEK_ASSERT(this->m_pipelines.find(pipeline_name) !=
						this->m_pipelines.end(),
					"you must contain your VkPipeline by pipeline name: {}",
                    reinterpret_cast<const char*>(pipeline_name.c_str()));

				return this->m_pipelines.at(pipeline_name);
			}

			VkPipelineLayout ktkRenderGraphNode::GetPipelineLayout(
				const ktk::string& pipeline_name) const noexcept
			{
				KOTEK_ASSERT(pipeline_name.empty() == false,
					"you can't pass an empty string here, can't find by empty "
					"pipeline name");

				KOTEK_ASSERT(this->m_pipelines_layout.find(pipeline_name) !=
						this->m_pipelines_layout.end(),
					"you must contain your VkPipelineLayout by pipeline name: "
					"{}",
                    reinterpret_cast<const char*>(pipeline_name.c_str()));

				return this->m_pipelines_layout.at(pipeline_name);
			}

			const ktk::vector<VkDescriptorSet>&
			ktkRenderGraphNode::GetDescriptorSets(
				const ktk::string& pipeline_name) const noexcept
			{
				KOTEK_ASSERT(pipeline_name.empty() == false,
					"you can't pass an empty string");

				KOTEK_ASSERT(
					this->m_pipeline_descriptor_sets.find(pipeline_name) !=
						this->m_pipeline_descriptor_sets.end(),
					"you must contain your VkPipeline by pipeline name: {}",
                    reinterpret_cast<const char*>(pipeline_name.c_str()));

				return this->m_pipeline_descriptor_sets.at(pipeline_name);
			}

			VkRenderPass ktkRenderGraphNode::GetRenderPass(void) const noexcept
			{
				return this->m_p_render_pass;
			}

			VkFramebuffer ktkRenderGraphNode::GetFrameBuffer(
				void) const noexcept
			{
				return this->m_p_frame_buffer;
			}

			const ktk::string& ktkRenderGraphNode::GetRenderPassName(
				void) const noexcept
			{
				return this->m_render_pass_name;
			}
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
