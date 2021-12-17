#pragma once

#include "../kotek.core/kotek_std.h"
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
			constexpr const char* kBackBufferName =
				"KOTEK_BACKBUFFER_SYSTEM_NAME";

			// TODO: add aliases for human readable design, because we need to
			// read types and understand what we place there and what that key
			// or value means
			class ktkRenderGraphResourceManager
			{
			public:
				ktkRenderGraphResourceManager(
					Core::ktkMainManager& main_manager);
				~ktkRenderGraphResourceManager(void);

				void initialize(
					e_kotek_render_graph_builder_type_t type_of_framebuffer,
					e_kotek_render_graph_builder_pipeline_rendering_type_t
						type_videocard_pipeline);
				void shutdown(void);

				void CreateShadersAndLayoutsWithDescriptorSets(
					const kotek_render_graph_storage_input&
						render_graph_builder_data) noexcept;

				void CreateSynchronizationPrimitivesAndRenderPass(
					const ktk::string& render_pass_name,
					const kotek_render_graph_storage_input&
						storage_of_render_pass_input,
					const kotek_render_graph_storage_output&
						storage_of_render_pass_output,
					const ktk::unordered_map<ktk::texture_id_t,
						kotek_render_graph_resource_info_t<
							kotek_render_texture_info_t>>& texture_to_create,
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_resource_info_t<VkBufferCreateInfo>>&
						buffer_to_create) noexcept;

				void createTexture(const kotek_render_graph_resource_info_t<
					kotek_render_texture_info_t>& info) noexcept;

				void createBackBuffer(
					const ktk::string& backbuffer_name) noexcept;

				const kotek_render_texture* getTexture(
					const ktk::string& render_pass_name,
					const ktk::string& texture_name) const noexcept;

				const ktk::unordered_map<ktk::render_pass_id_t,
					ktk::unordered_map<ktk::texture_id_t,
						kotek_render_graph_texture*>>&
				getRenderGraph_RenderPasses_Textures(void) const noexcept;

				void uploadTextureWithData(
					const ktk::string& texture_name, void* p_data) noexcept;

				ktk::vector<VkDescriptorSet> GetDescriptorSets(
					const ktk::string& pipeline_name) const noexcept;

				VkRenderPass GetRenderPass(
					const ktk::string& render_pass_name) const noexcept;

				VkFramebuffer GetFrameBuffer(
					const ktk::string& render_pass_name) const noexcept;

				VkPipeline GetPipeline(
					const ktk::string& pipeline_name) const noexcept;

				VkPipelineLayout GetPipelineLayout(
					const ktk::string& pipeline_name) const noexcept;

				const kotek_render_texture* GetBackBufferTexture(
					void) const noexcept;

			private:
				void destroyShaders(void) noexcept;
				void destroyTextures(void) noexcept;
				void DestroyRenderPasses(void) noexcept;
				void DestroyFrameBuffers(void) noexcept;
				void DestroyPipelines(void) noexcept;

				// TRUE - file | FALSE - source code
				bool isFileOrSourceCodeString(
					const ktk::string& string_to_analyze) noexcept;

				bool isFileWithFormat(const ktk::string& path_name) noexcept;

				void createShaders_Modules(const ktk::unordered_map<
					ktk::pipeline_id_t,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
						render_graph_builder_data) noexcept;

				ktk::vector<VkSubpassDependency> CreateSubpassDependencies(
					const kotek_render_graph_storage_output& storage_output,
					const ktk::unordered_map<ktk::texture_id_t,
						kotek_render_graph_resource_info_t<
							kotek_render_texture_info_t>>&
						texture_to_create) noexcept;
				void createDescriptorSetLayouts_And_PipelineLayouts(
					const kotek_render_graph_storage_input& storage) noexcept;
				void CreateDescriptorSets(
					const kotek_render_graph_storage_input& storage) noexcept;
				void CreateFrameBuffers(const ktk::string& render_pass_name,
					const kotek_render_graph_storage_output& storage) noexcept;
				void CreateRenderPass(const ktk::string& render_pass_name,
					const ktk::vector<VkSubpassDependency>&
						dependencies,
					const kotek_render_graph_storage_output& storage_output) noexcept;
				void CreatePipelines(const ktk::string& render_pass_name,
					const kotek_render_graph_storage_input& storage) noexcept;

				ktk::vector<VkAttachmentReference>
				CreateRenderPassAttachmentReferences(const kotek_render_graph_storage_output& storage) noexcept;

				// TODO: update for depth
				ktk::vector<VkSubpassDescription>
				CreateRenderPassSubpassDescriptions(
					const kotek_render_graph_storage_output& storage,
					const ktk::vector<VkAttachmentReference>& color_references) noexcept;

				ktk::vector<VkAttachmentDescription>
				CreateRenderPassAttachmentDescription(
					const kotek_render_graph_storage_output& storage) noexcept;

				void CreateBarriers(void) noexcept;

				ktk::vector<VkDescriptorSetLayoutBinding>
				collectDescriptorSetLayoutBingings(
					const kotek_render_shader_manager::shader_module_t&
						your_module) noexcept;

				ktk::unordered_map<ktk::uint32_t,
					ktk::vector<descriptor_set_info_t>>
				collectValidationData(
					const kotek_render_shader_manager::shader_module_t&
						your_module) noexcept;

				void validateInputDataForShaders(
					const ktk::unordered_map<ktk::string,
						ktk::unordered_map<ktk::uint32_t,
							ktk::vector<shader_input_data_t>>>& storage,
					const ktk::unordered_map<ktk::string,
						ktk::unordered_map<ktk::uint32_t,
							ktk::vector<descriptor_set_info_t>>>&
						bindings_for_whole_pipeline) noexcept;

				bool IsUseTesselationInPipeline(
					const ktk::string& pipeline_name) const noexcept;

			private:
				kotek_render_device* m_p_render_device;
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

				ktk::unordered_map<ktk::texture_id_t,
					kotek_render_graph_texture>
					m_all_render_graph_textures;

				ktk::unordered_map<ktk::render_pass_id_t,
					ktk::unordered_map<ktk::texture_id_t,
						kotek_render_graph_texture*>>
					m_storage_render_passes_textures;

				ktk::unordered_map<ktk::pipeline_id_t,
					ktk::vector<VkDescriptorSet>>
					m_storage_descriptor_sets;

				ktk::unordered_map<ktk::render_pass_id_t,
					VkFramebuffer>
					m_storage_render_passes_framebuffers;

				ktk::unordered_map<ktk::render_pass_id_t, VkRenderPass>
					m_storage_render_passes_render_passes_handles;

				ktk::unordered_map<ktk::pipeline_id_t,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<descriptor_set_info_t>>>
					m_validation_info_for_descriptor_sets_about_whole_user_pipeline;

				kotek_render_texture m_backbuffer_texture;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek