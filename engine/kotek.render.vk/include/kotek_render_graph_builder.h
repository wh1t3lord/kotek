#pragma once

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
			class ktkRenderGraph;
			class ktkRenderResourceManager;
			class ktkRenderDevice;
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
			class ktkRenderGraphBuilder
			{
			public:
				ktkRenderGraphBuilder(Core::ktkMainManager& main_manager);
				ktkRenderGraphBuilder(void) = delete;
				~ktkRenderGraphBuilder(void);

				ktkRenderGraphBuilder(const ktkRenderGraphBuilder&) = delete;
				ktkRenderGraphBuilder& operator=(
					const ktkRenderGraphBuilder&) = delete;

				ktkRenderGraphBuilder(ktkRenderGraphBuilder&&) = delete;
				ktkRenderGraphBuilder& operator=(
					ktkRenderGraphBuilder&&) = delete;

				// TODO: delete default arguments see gl implementation and
				// initialize method
				void Initialize(
					ktkRenderGraphResourceManager* p_resource_manager,
					const ktk::string& backbuffer_name,
					const eRenderGraphBuilderType& render_graph_type_id =
						eRenderGraphBuilderType::kRenderBuilderFor_Forward_Only,
					const eRenderGraphBuilderPipelineRenderingType&
						rendering_pipeline_type =
							eRenderGraphBuilderPipelineRenderingType::
								kRenderBuilderBasedOnPipeline_Orthodox);

				ktkRenderGraph Compile(void);

				bool RegisterRenderPass(const ktk::string& render_pass_name,
					ktkRenderGraphRenderPass* p_pass) noexcept;

				const ktk::string& GetBackBufferName(void) const noexcept;

				eRenderGraphBuilderType GetRenderGraphBuilderType(
					void) const noexcept;

				eRenderGraphBuilderPipelineRenderingType
				GetRenderGraphPipelineRenderingType(void) const noexcept;

			private:
				void Shutdown(void);

				ktk::unordered_map<ktk::string, ktkRenderGraphStorageInput>
				CompileInputs(void) noexcept;

				ktk::unordered_map<ktk::string, ktkRenderGraphStorageOutput>
				CompileOutputs(void) noexcept;

				void CompileInput(
					const ktkRenderGraphStorageInput& storage) noexcept;

				ktk::vector<ktkRenderGraphNode> Analyze(
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphStorageInput>& input_storage,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphStorageOutput>& output_storage) noexcept;

				void CreateBackBuffer(void) noexcept;

				void CreateTexturesAndBuffers(
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<ktkRenderTextureInfo>>&
						images,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<VkBufferCreateInfo>>&
						buffers) noexcept;

				void CreateShadersAndLayouts(
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphStorageInput>& storages) noexcept;

				// also create VkPipeline too
				void CreateSynchronizationPrimitivesAndRenderPass(
					const ktk::unordered_map<ktk::render_pass_id_t,
						ktkRenderGraphStorageInput>& input_storage,
					const ktk::unordered_map<ktk::render_pass_id_t,
						ktkRenderGraphStorageOutput>& output_storage,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<ktkRenderTextureInfo>>&
						images,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<VkBufferCreateInfo>>&
						buffers) noexcept;

				void ValidateShaders(const ktk::unordered_map<ktk::string,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
						input_shaders) noexcept;

				void CreateBarriers(void) noexcept;

			private:
				eRenderGraphBuilderType m_render_graph_type;
				eRenderGraphBuilderPipelineRenderingType
					m_rendering_pipeline_type;
				ktkRenderResourceManager* m_p_manager_render_resource;
				Core::ktkProfiler* m_p_profiler;
				Core::ktkMainManager* m_p_main_manager;
				ktkRenderDevice* m_p_device;
				ktkRenderGraphResourceManager*
					m_p_manager_render_graph_resource;
				ktk::string m_backbuffer_name;
				ktk::vector<ktkRenderGraphRenderPass*> m_failed_add_passes;
				ktk::vector<ktkRenderGraphRenderPass*>
					m_temporary_storage_render_passes;
				ktk::unordered_map<ktk::string, ktkRenderGraphStorageInput>
					m_storage_inputs;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
