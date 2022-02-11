#pragma once

#include "kotek_render_graph_types.h"

namespace Sandbox
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraphBuilder
			{
			public:
				ktkRenderGraphBuilder(void);
				~ktkRenderGraphBuilder(void);

			private:
				eRenderGraphBuilderType m_render_graph_type;
				eRenderGraphBuilderPipelineRenderingType
					m_rendering_pipeline_type;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Sandbox