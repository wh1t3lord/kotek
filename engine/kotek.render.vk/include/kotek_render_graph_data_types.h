#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderGraphNode
			{
			public:
				ktkRenderGraphNode(const ktk::string& render_pass_name,
					VkRenderPass p_pass, VkFramebuffer p_frame_buffer,
					const ktk::unordered_map<ktk::string, VkPipeline>&
						pipelines,
					const ktk::unordered_map<ktk::string,
						ktk::vector<VkDescriptorSet>>&
						pipelines_descriptor_sets,
					const ktk::unordered_map<ktk::string, VkPipelineLayout>&
						pipelines_layout);

				ktkRenderGraphNode(void);
				~ktkRenderGraphNode(void);

				VkPipeline GetPipeline(
					const ktk::string& pipeline_name) const noexcept;

				VkPipelineLayout GetPipelineLayout(
					const ktk::string& pipeline_name) const noexcept;

				const ktk::vector<VkDescriptorSet>& GetDescriptorSets(
					const ktk::string& pipeline_name) const noexcept;

				VkRenderPass GetRenderPass(void) const noexcept;

				VkFramebuffer GetFrameBuffer(void) const noexcept;

				const ktk::string& GetRenderPassName(void) const noexcept;

			private:
				VkRenderPass m_p_render_pass;
				VkFramebuffer m_p_frame_buffer;
				ktk::string m_render_pass_name;
				ktk::unordered_map<ktk::string, VkPipeline> m_pipelines;
				ktk::unordered_map<ktk::string, VkPipelineLayout>
					m_pipelines_layout;
				ktk::unordered_map<ktk::string, ktk::vector<VkDescriptorSet>>
					m_pipeline_descriptor_sets;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek