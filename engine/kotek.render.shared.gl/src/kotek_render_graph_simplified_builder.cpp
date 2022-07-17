#include "../include/kotek_render_graph_simplified_builder.h"
#include "../include/kotek_render_graph_simplified.h"
#include "../include/kotek_render_graph_simplified_render_pass.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphSimplifiedBuilder::ktkRenderGraphSimplifiedBuilder(
				Core::ktkMainManager& main_manager) :
				m_render_graph_type{},
				m_rendering_pipeline_type{}
			{
			}

			ktkRenderGraphSimplifiedBuilder::~ktkRenderGraphSimplifiedBuilder(
				void)
			{
			}

			void ktkRenderGraphSimplifiedBuilder::Initialize(
				Core::ktkIRenderGraphResourceManager* p_resource_manager,
				const ktk::string& backbuffer_name,
				const gl::eRenderGraphBuilderType& render_graph_type_id,
				const gl::eRenderGraphBuilderPipelineRenderingType&
					rendering_pipeline_type)
			{
				KOTEK_ASSERT(p_resource_manager,
					"you can't pass an invalid pointer of resource manager");

				KOTEK_ASSERT(backbuffer_name.empty() == false,
					"you can't pass an empty string for backbuffer name");

				this->m_backbuffer_name = backbuffer_name;
				this->m_render_graph_type = render_graph_type_id;
				this->m_rendering_pipeline_type = rendering_pipeline_type;
			}

			gl::ktkRenderGraphSimplified
			ktkRenderGraphSimplifiedBuilder::Compile(void)
			{
				return gl::ktkRenderGraphSimplified();
			}

			bool ktkRenderGraphSimplifiedBuilder::Register_RenderPass(
				const ktk::string& render_pass_name,
				gl::ktkRenderGraphSimplifiedRenderPass* p_pass) noexcept
			{
				return true;
			}

			const ktk::string&
			ktkRenderGraphSimplifiedBuilder::Get_BackBufferName(
				void) const noexcept
			{
				return this->m_backbuffer_name;
			}

			gl::eRenderGraphBuilderType
			ktkRenderGraphSimplifiedBuilder::Get_RenderGraphBuilderType(
				void) const noexcept
			{
				return this->m_render_graph_type;
			}

			gl::eRenderGraphBuilderPipelineRenderingType
			ktkRenderGraphSimplifiedBuilder::
				Get_RenderGraphPipelineRenderingType(void) const noexcept
			{
				return this->m_rendering_pipeline_type;
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek