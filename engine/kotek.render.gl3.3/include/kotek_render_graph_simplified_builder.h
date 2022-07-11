#pragma once

#include "kotek_render_graph_simplified_types.h"

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
		namespace gl3_3
		{
			class ktkRenderGraphSimplifiedBuilder
			{
			public:
				ktkRenderGraphSimplifiedBuilder(
					Core::ktkMainManager& main_manager);
				ktkRenderGraphSimplifiedBuilder(void) = delete;
				~ktkRenderGraphSimplifiedBuilder(void);

				ktkRenderGraphSimplifiedBuilder(const ktkRenderGraphSimplifiedBuilder&) = delete;
				ktkRenderGraphSimplifiedBuilder& operator=(
					const ktkRenderGraphSimplifiedBuilder&) = delete;

				ktkRenderGraphSimplifiedBuilder(ktkRenderGraphSimplifiedBuilder&&) = delete;
				ktkRenderGraphSimplifiedBuilder& operator=(
					ktkRenderGraphSimplifiedBuilder&&) = delete;

				void Initialize(
					ktkRenderGraphSimplifiedResourceManager* p_resource_manager,
					const ktk::string& backbuffer_name,
					const eRenderGraphBuilderType& render_graph_type_id =
						eRenderGraphBuilderType::kRenderBuilderFor_Forward_Only,
					const eRenderGraphBuilderPipelineRenderingType&
						rendering_pipeline_type =
							eRenderGraphBuilderPipelineRenderingType::
								kRenderBuilderBasedOnPipeline_Orthodox);

				ktkRenderGraphSimplified Compile(void);

				bool RegisterRenderPass(const ktk::string& render_pass_name,
					ktkRenderGraphSimplifiedRenderPass* p_pass) noexcept;

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
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek