#pragma once

#include "kotek_render_graph_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraph;
			class ktkRenderResourceManager;
			class ktkRenderGraphResourceManager;
			class ktkRenderGraphRenderPass;
		}
	} // namespace Render

	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl
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
				eRenderGraphBuilderType m_render_graph_type;
				eRenderGraphBuilderPipelineRenderingType
					m_rendering_pipeline_type;
				ktk::string m_backbuffer_name;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek