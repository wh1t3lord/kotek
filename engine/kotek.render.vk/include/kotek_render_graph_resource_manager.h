#pragma once

#include "kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Core
	{
		class ktkProfiler;
		class ktkMainManager;
	} // namespace Core
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
            constexpr const char* kBackBufferName = "KOTEK_BACKBUFFER_VK_NAME";

			// TODO: add aliases for human readable design, because we need to
			// read types and understand what we place there and what that key
			// or value means
			class ktkRenderGraphResourceManager
			{
			public:
				ktkRenderGraphResourceManager(
					Core::ktkMainManager& main_manager);
				~ktkRenderGraphResourceManager(void);

				void Initialize(eRenderGraphBuilderType type_of_framebuffer,
					eRenderGraphBuilderPipelineRenderingType
						type_videocard_pipeline);
				void Shutdown(void);

				void CreateShadersAndLayoutsWithDescriptorSets(
					const ktkRenderGraphStorageInput&
						render_graph_builder_data) noexcept;

				void CreateSynchronizationPrimitivesAndRenderPass(
					const ktk::ustring& render_pass_name,
					const ktkRenderGraphStorageInput&
						storage_of_render_pass_input,
					const ktkRenderGraphStorageOutput&
						storage_of_render_pass_output,
					const ktk::unordered_map<ktk::texture_id_t,
						ktkRenderGraphResourceInfo<ktkRenderTextureInfo>>&
						texture_to_create,
					const ktk::unordered_map<ktk::ustring,
						ktkRenderGraphResourceInfo<VkBufferCreateInfo>>&
						buffer_to_create) noexcept;

				void CreateTexture(
					const ktkRenderGraphResourceInfo<ktkRenderTextureInfo>&
						info) noexcept;

				void CreateBackBuffer(
					const ktk::ustring& backbuffer_name) noexcept;

				const ktkRenderTexture* GetTexture(
					const ktk::ustring& render_pass_name,
					const ktk::ustring& texture_name) const noexcept;

				const ktk::unordered_map<ktk::render_pass_id_t,
					ktk::unordered_map<ktk::texture_id_t,
						ktkRenderGraphTexture*>>&
				GetRenderGraph_RenderPasses_Textures(void) const noexcept;

				void UploadTextureWithData(
					const ktk::ustring& texture_name, void* p_data) noexcept;

				ktk::vector<VkDescriptorSet> GetDescriptorSets(
					const ktk::ustring& pipeline_name) const noexcept;

				VkRenderPass GetRenderPass(
					const ktk::ustring& render_pass_name) const noexcept;

				VkFramebuffer GetFrameBuffer(
					const ktk::ustring& render_pass_name) const noexcept;

				VkPipeline GetPipeline(
					const ktk::ustring& pipeline_name) const noexcept;

				VkPipelineLayout GetPipelineLayout(
					const ktk::ustring& pipeline_name) const noexcept;

				const ktkRenderTexture* GetBackBufferTexture(
					void) const noexcept;

			private:
				void DestroyShaders(void) noexcept;
				void DestroyTextures(void) noexcept;
				void DestroyRenderPasses(void) noexcept;
				void DestroyFrameBuffers(void) noexcept;
				void DestroyPipelines(void) noexcept;

				// TRUE - file | FALSE - source code
				bool IsFileOrSourceCodeString(
                    const ktk::cstring& string_to_analyze) noexcept;

                bool IsFileWithFormat(const ktk::cstring& path_name) noexcept;

				void CreateShaders_Modules(const ktk::unordered_map<
					ktk::pipeline_id_t,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
						render_graph_builder_data) noexcept;

				ktk::vector<VkSubpassDependency> CreateSubpassDependencies(
					const ktkRenderGraphStorageOutput& storage_output,
					const ktk::unordered_map<ktk::texture_id_t,
						ktkRenderGraphResourceInfo<ktkRenderTextureInfo>>&
						texture_to_create) noexcept;
				void createDescriptorSetLayouts_And_PipelineLayouts(
					const ktkRenderGraphStorageInput& storage) noexcept;
				void CreateDescriptorSets(
					const ktkRenderGraphStorageInput& storage) noexcept;
				void CreateFrameBuffers(const ktk::ustring& render_pass_name,
					const ktkRenderGraphStorageOutput& storage) noexcept;
				void CreateRenderPass(const ktk::ustring& render_pass_name,
					const ktk::vector<VkSubpassDependency>& dependencies,
					const ktkRenderGraphStorageOutput& storage_output) noexcept;
				void CreatePipelines(const ktk::ustring& render_pass_name,
					const ktkRenderGraphStorageInput& storage) noexcept;

				ktk::vector<VkAttachmentReference>
				CreateRenderPassAttachmentReferences(
					const ktkRenderGraphStorageOutput& storage) noexcept;

				// TODO: update for depth
				ktk::vector<VkSubpassDescription>
				CreateRenderPassSubpassDescriptions(
					const ktkRenderGraphStorageOutput& storage,
					const ktk::vector<VkAttachmentReference>&
						color_references) noexcept;

				ktk::vector<VkAttachmentDescription>
				CreateRenderPassAttachmentDescription(
					const ktkRenderGraphStorageOutput& storage) noexcept;

				void CreateBarriers(void) noexcept;

				ktk::vector<VkDescriptorSetLayoutBinding>
				CollectDescriptorSetLayoutBingings(
					const kotek_render_shader_manager::shader_module_t&
						your_module) noexcept;

				ktk::unordered_map<ktk::uint32_t,
					ktk::vector<descriptor_set_info_t>>
				CollectValidationData(
					const kotek_render_shader_manager::shader_module_t&
						your_module) noexcept;

				void ValidateInputDataForShaders(
					const ktk::unordered_map<ktk::ustring,
						ktk::unordered_map<ktk::uint32_t,
							ktk::vector<shader_input_data_t>>>& storage,
					const ktk::unordered_map<ktk::ustring,
						ktk::unordered_map<ktk::uint32_t,
							ktk::vector<descriptor_set_info_t>>>&
						bindings_for_whole_pipeline) noexcept;

				bool IsUseTesselationInPipeline(
					const ktk::ustring& pipeline_name) const noexcept;

			private:
				ktkRenderDevice* m_p_render_device;
				ktkRenderResourceManager* m_p_manager_resource;
				Core::ktkProfiler* m_p_profiler;

				ktk::unordered_map<ktk::pipeline_id_t, VkDescriptorSetLayout>
					m_storage_descriptor_set_layouts;

				ktk::unordered_map<ktk::pipeline_id_t, VkPipelineLayout>
					m_storage_pipeline_layouts;

				ktk::unordered_map<ktk::pipeline_id_t,
					ktk::unordered_map<shader_type_t,
						kotek_render_shader_manager::shader_module_t>>
					m_storage_shaders;

				ktk::unordered_map<ktk::pipeline_id_t, VkPipeline>
					m_storage_pipelines;

				ktk::unordered_map<ktk::texture_id_t, ktkRenderGraphTexture>
					m_all_render_graph_textures;

				ktk::unordered_map<ktk::render_pass_id_t,
					ktk::unordered_map<ktk::texture_id_t,
						ktkRenderGraphTexture*>>
					m_storage_render_passes_textures;

				ktk::unordered_map<ktk::pipeline_id_t,
					ktk::vector<VkDescriptorSet>>
					m_storage_descriptor_sets;

				ktk::unordered_map<ktk::render_pass_id_t, VkFramebuffer>
					m_storage_render_passes_framebuffers;

				ktk::unordered_map<ktk::render_pass_id_t, VkRenderPass>
					m_storage_render_passes_render_passes_handles;

				ktk::unordered_map<ktk::pipeline_id_t,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<descriptor_set_info_t>>>
					m_validation_info_for_descriptor_sets_about_whole_user_pipeline;

				ktkRenderTexture m_backbuffer_texture;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
