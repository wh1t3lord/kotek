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
				ktkRenderGraphNode(const ktk::ustring& render_pass_name,
					VkRenderPass p_pass, VkFramebuffer p_frame_buffer,
					const ktk::unordered_map<ktk::ustring, VkPipeline>&
						pipelines,
					const ktk::unordered_map<ktk::ustring,
						ktk::vector<VkDescriptorSet>>&
						pipelines_descriptor_sets,
					const ktk::unordered_map<ktk::ustring, VkPipelineLayout>&
						pipelines_layout);

				ktkRenderGraphNode(void);
				~ktkRenderGraphNode(void);

				VkPipeline GetPipeline(
					const ktk::ustring& pipeline_name) const noexcept;

				VkPipelineLayout GetPipelineLayout(
					const ktk::ustring& pipeline_name) const noexcept;

				const ktk::vector<VkDescriptorSet>& GetDescriptorSets(
					const ktk::ustring& pipeline_name) const noexcept;

				VkRenderPass GetRenderPass(void) const noexcept;

				VkFramebuffer GetFrameBuffer(void) const noexcept;

				const ktk::ustring& GetRenderPassName(void) const noexcept;

			private:
				VkRenderPass m_p_render_pass;
				VkFramebuffer m_p_frame_buffer;
				ktk::ustring m_render_pass_name;
				ktk::unordered_map<ktk::ustring, VkPipeline> m_pipelines;
				ktk::unordered_map<ktk::ustring, VkPipelineLayout>
					m_pipelines_layout;
				ktk::unordered_map<ktk::ustring, ktk::vector<VkDescriptorSet>>
					m_pipeline_descriptor_sets;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek