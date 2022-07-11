#pragma once

#include "kotek_render_graph_simplified_types.h"

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
		namespace gl3_3
		{
			constexpr const char* kBackBufferName = "KOTEK_BACKBUFFER_GL_NAME";

			class ktkRenderGraphSimplifiedResourceManager
			{
			public:
				ktkRenderGraphSimplifiedResourceManager(
					Core::ktkMainManager& main_manager);
				~ktkRenderGraphSimplifiedResourceManager(void);

				void Initialize(eRenderGraphBuilderType type_of_framebuffer,
					eRenderGraphBuilderPipelineRenderingType
						type_videocard_pipeline);
				void Shutdown(void);

			private:

			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek