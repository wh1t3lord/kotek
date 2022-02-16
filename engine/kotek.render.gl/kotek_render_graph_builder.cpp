#include "kotek_render_graph_builder.h"
#include "kotek_render_graph.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphBuilder::ktkRenderGraphBuilder(
				Core::ktkMainManager& main_manager) :
				m_render_graph_type{},
				m_rendering_pipeline_type{}
			{
			}

			ktkRenderGraphBuilder::~ktkRenderGraphBuilder(void) {}

			void ktkRenderGraphBuilder::Initialize(
				ktkRenderGraphResourceManager* p_resource_manager,
				const ktk::string& backbuffer_name,
				const eRenderGraphBuilderType& render_graph_type_id =
					eRenderGraphBuilderType::kRenderBuilderFor_Forward_Only,
				const eRenderGraphBuilderPipelineRenderingType&
					rendering_pipeline_type =
						eRenderGraphBuilderPipelineRenderingType::
							kRenderBuilderBasedOnPipeline_Orthodox)
			{
			}

			ktkRenderGraph ktkRenderGraphBuilder::Compile(void)
			{
				return ktkRenderGraph();
			}

			bool ktkRenderGraphBuilder::RegisterRenderPass(
				const ktk::string& render_pass_name,
				ktkRenderGraphRenderPass* p_pass) noexcept
			{
				return true;
			}

			const ktk::string& ktkRenderGraphBuilder::GetBackBufferName(
				void) const noexcept
			{
				return this->m_backbuffer_name;
			}

			eRenderGraphBuilderType
			ktkRenderGraphBuilder::GetRenderGraphBuilderType(
				void) const noexcept
			{
				return this->m_render_graph_type;
			}

			eRenderGraphBuilderPipelineRenderingType
			ktkRenderGraphBuilder::GetRenderGraphPipelineRenderingType(
				void) const noexcept
			{
				return this->m_rendering_pipeline_type;
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek