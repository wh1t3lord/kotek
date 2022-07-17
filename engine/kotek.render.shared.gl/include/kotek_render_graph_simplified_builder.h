#pragma once

namespace Kotek
{
	namespace Core
	{
		class ktkIRenderResourceManager;
		class ktkIRenderGraphResourceManager;
	} // namespace Core

	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraphSimplified;
			class ktkRenderGraphSimplifiedRenderPass;

			enum class eRenderGraphBuilderType;
			enum class eRenderGraphBuilderPipelineRenderingType;
		} // namespace gl
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
		namespace gl
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
					Core::ktkIRenderGraphResourceManager* p_resource_manager,
					const ktk::string& backbuffer_name,
					const eRenderGraphBuilderType& render_graph_type_id,
					const eRenderGraphBuilderPipelineRenderingType&
						rendering_pipeline_type);

				ktkRenderGraphSimplified Compile(void);

				bool Register_RenderPass(const ktk::string& render_pass_name,
					ktkRenderGraphSimplifiedRenderPass* p_pass) noexcept;

				const ktk::string& Get_BackBufferName(void) const noexcept;

				eRenderGraphBuilderType Get_RenderGraphBuilderType(
					void) const noexcept;

				eRenderGraphBuilderPipelineRenderingType
				Get_RenderGraphPipelineRenderingType(void) const noexcept;

			private:
				eRenderGraphBuilderType m_render_graph_type;
				eRenderGraphBuilderPipelineRenderingType
					m_rendering_pipeline_type;
				ktk::string m_backbuffer_name;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek