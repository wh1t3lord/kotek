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
				const eRenderGraphBuilderType& render_graph_type_id,
				const eRenderGraphBuilderPipelineRenderingType&
					rendering_pipeline_type)
			{
				KOTEK_ASSERT(p_resource_manager,
					"you can't pass an invalid pointer of resource manager");

				KOTEK_ASSERT(backbuffer_name.empty() == false,
					"you can't pass an empty string for backbuffer name");

				this->m_backbuffer_name = backbuffer_name;
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