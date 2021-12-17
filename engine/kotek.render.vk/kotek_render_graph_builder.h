#pragma once

#include "../kotek.core/kotek_profiler.h"
#include "../kotek.core/kotek_std.h"
#include "kotek_render_texture_manager.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_graph;
			class ktkRenderResourceManager;
			class kotek_render_device;
			class ktkRenderGraphResourceManager;
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_graph_builder
			{
			public:
				kotek_render_graph_builder(Core::ktkMainManager& main_manager);
				kotek_render_graph_builder(void) = delete;
				~kotek_render_graph_builder(void);

				kotek_render_graph_builder(
					const kotek_render_graph_builder&) = delete;
				kotek_render_graph_builder& operator=(
					const kotek_render_graph_builder&) = delete;

				kotek_render_graph_builder(
					kotek_render_graph_builder&&) = delete;
				kotek_render_graph_builder& operator=(
					kotek_render_graph_builder&&) = delete;

				void initialize(
					ktkRenderGraphResourceManager* p_resource_manager,
					const ktk::string& backbuffer_name,
					const e_kotek_render_graph_builder_type_t&
						render_graph_type_id =
							e_kotek_render_graph_builder_type_t::
								kRenderBuilderFor_Forward_Only,
					const e_kotek_render_graph_builder_pipeline_rendering_type_t&
						rendering_pipeline_type =
							e_kotek_render_graph_builder_pipeline_rendering_type_t::
								kRenderBuilderBasedOnPipeline_Orthodox);

				kotek_render_graph compile(void);

				bool registerRenderPass(const ktk::string& render_pass_name,
					kotek_render_graph_render_pass* p_pass) noexcept;

				const ktk::string& getBackBufferName(void) const noexcept;

				e_kotek_render_graph_builder_type_t getRenderGraphBuilderType(
					void) const noexcept;

				e_kotek_render_graph_builder_pipeline_rendering_type_t
				getRenderGraphPipelineRenderingType(void) const noexcept;

			private:
				void shutdown(void);

				ktk::unordered_map<ktk::string,
					kotek_render_graph_storage_input>
				compileInputs(void) noexcept;

				ktk::unordered_map<ktk::string,
					kotek_render_graph_storage_output>
				compileOutputs(void) noexcept;

				void compileInput(
					const kotek_render_graph_storage_input& storage) noexcept;

				ktk::vector<ktkRenderGraphNode> analyze(
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_storage_input>& input_storage,
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_storage_output>&
						output_storage) noexcept;

				void createBackBuffer(void) noexcept;

				void createTexturesAndBuffers(
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_resource_info_t<
							kotek_render_texture_info_t>>& images,
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_resource_info_t<VkBufferCreateInfo>>&
						buffers) noexcept;

				void CreateShadersAndLayouts(
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_storage_input>& storages) noexcept;

				// also create VkPipeline too
				void CreateSynchronizationPrimitivesAndRenderPass(
					const ktk::unordered_map<ktk::render_pass_id_t,
						kotek_render_graph_storage_input>& input_storage,
					const ktk::unordered_map<ktk::render_pass_id_t,
						kotek_render_graph_storage_output>& output_storage,
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_resource_info_t<
							kotek_render_texture_info_t>>& images,
					const ktk::unordered_map<ktk::string,
						kotek_render_graph_resource_info_t<VkBufferCreateInfo>>&
						buffers) noexcept;

				void validateShaders(const ktk::unordered_map<ktk::string,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
						input_shaders) noexcept;

				void createBarriers(void) noexcept;

			private:
				e_kotek_render_graph_builder_type_t m_render_graph_type;
				e_kotek_render_graph_builder_pipeline_rendering_type_t
					m_rendering_pipeline_type;
				ktkRenderResourceManager* m_p_manager_render_resource;
				Core::ktkProfiler* m_p_profiler;
				Core::ktkMainManager* m_p_main_manager;
				kotek_render_device* m_p_device;
				ktkRenderGraphResourceManager*
					m_p_manager_render_graph_resource;
				ktk::string m_backbuffer_name;
				ktk::vector<kotek_render_graph_render_pass*>
					m_failed_add_passes;
				ktk::vector<kotek_render_graph_render_pass*>
					m_temporary_storage_render_passes;
				ktk::unordered_map<ktk::string,
					kotek_render_graph_storage_input>
					m_storage_inputs;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
