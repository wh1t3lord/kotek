#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderResourceManager;
			class ktkRenderDevice;
			class ktkRenderSwapchain;
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			// TODO: delete this manager and move to pass for imgui
			class kotek_render_imgui_manager : public Core::kotek_i_render_imgui
			{
			public:
				kotek_render_imgui_manager(void);
				~kotek_render_imgui_manager(void);

				void initialize(
					Core::ktkMainManager& main_manager) noexcept override;
				void shutdown(Core::ktkIRenderDevice*
						p_raw_device) noexcept override;
				void draw(VkCommandBuffer p_cmd,
					ktkRenderDevice* p_render_device,
					ktkRenderResourceManager*
						p_render_resource_manager) noexcept;

			private:
				void createFontTexture(ktkRenderDevice* p_render_device,
					ktkRenderResourceManager*
						p_render_resource_manager) noexcept;
				void destroyFontTexture(
					ktkRenderDevice* p_render_device) noexcept;

				void createImageView(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyImageView(
					ktkRenderDevice* p_render_device) noexcept;

				void createImage(ktkRenderDevice* p_render_device) noexcept;
				void destroyImage(
					ktkRenderDevice* p_render_device) noexcept;

				void createImageMemoryAndBind(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyImageMemory(
					ktkRenderDevice* p_render_device) noexcept;

				void copyBufferToImage(ktkRenderResourceManager*
						p_render_resource_manager) noexcept;
				void writeDataToSuballocatedPartOfHeap(
					ktkRenderResourceManager*
						p_render_resource_manager) noexcept;
				void flushHeap(
					ktkRenderResourceManager* p_render_resource_manager,
					ktkRenderDevice* p_render_device) noexcept;

				void createSampler(
					ktkRenderDevice* p_render_device) noexcept;
				void destroySampler(
					ktkRenderDevice* p_render_device) noexcept;

				void compileShaders(ktkRenderDevice* p_render_device,
					ktkRenderResourceManager*
						p_render_resource_manager) noexcept;

				void destroyPipelineLayout(
					ktkRenderDevice* p_render_device) noexcept;
				void destroyPipeline(
					ktkRenderDevice* p_render_device) noexcept;

				void destroyDescriptorSetLayout(
					ktkRenderDevice* p_render_device) noexcept;

				void updatePipeline(VkRenderPass p_render_pass,
					ktkRenderDevice* p_render_device) noexcept;

			private:
				ktk::uint32_t m_current_descriptor_index;
				VkImage m_p_image;
				VkImageView m_p_image_view;
				VkDeviceMemory m_p_device_memory;
				VkSampler m_p_sampler;
				VkDescriptorSetLayout m_descriptor_layout;
				VkPipelineLayout m_pipeline_layout;
				VkPipeline m_p_pipeline;
				VkDescriptorSet m_descriptor_sets[128];
				ktk::vector<VkPipelineShaderStageCreateInfo> m_shader_stages;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
