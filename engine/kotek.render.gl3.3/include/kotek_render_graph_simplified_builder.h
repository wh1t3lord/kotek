#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraphSimplified;
			class ktkRenderResourceManager;
			class ktkRenderGraphSimplifiedResourceManager;
			class ktkRenderGraphSimplifiedRenderPass;
		} // namespace gl3_3
	}     // namespace Render

	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraphSimplifiedBuilder
			{
			public:
				ktkRenderGraphSimplifiedBuilder(
					Core::ktkMainManager& main_manager);
				ktkRenderGraphSimplifiedBuilder(void) = delete;
				~ktkRenderGraphSimplifiedBuilder(void);

				ktkRenderGraphSimplifiedBuilder(
					const ktkRenderGraphSimplifiedBuilder&) = delete;
				ktkRenderGraphSimplifiedBuilder& operator=(
					const ktkRenderGraphSimplifiedBuilder&) = delete;

				ktkRenderGraphSimplifiedBuilder(
					ktkRenderGraphSimplifiedBuilder&&) = delete;
				ktkRenderGraphSimplifiedBuilder& operator=(
					ktkRenderGraphSimplifiedBuilder&&) = delete;

				void Initialize(
					ktkRenderGraphSimplifiedResourceManager* p_resource_manager,
					const ktk::string& backbuffer_name,
					const gl::eRenderGraphBuilderType& render_graph_type_id =
						gl::eRenderGraphBuilderType::
							kRenderBuilderFor_Forward_Only,
					const gl::eRenderGraphBuilderPipelineRenderingType&
						rendering_pipeline_type =
							gl::eRenderGraphBuilderPipelineRenderingType::
								kRenderBuilderBasedOnPipeline_Orthodox);

				ktkRenderGraphSimplified Compile(void);

				bool Register_RenderPass(const ktk::string& render_pass_name,
					ktkRenderGraphSimplifiedRenderPass* p_pass) noexcept;

				const ktk::string& Get_BackBufferName(void) const noexcept;

				gl::eRenderGraphBuilderType Get_RenderGraphBuilderType(
					void) const noexcept;

				gl::eRenderGraphBuilderPipelineRenderingType
				Get_RenderGraphPipelineRenderingType(void) const noexcept;

			private:
				gl::eRenderGraphBuilderType m_render_graph_type;
				gl::eRenderGraphBuilderPipelineRenderingType
					m_rendering_pipeline_type;
				ktk::string m_backbuffer_name;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek