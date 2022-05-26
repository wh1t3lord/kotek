#pragma once

#include "kotek_render_graph_types.h"

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
		namespace gl
		{
			constexpr const char* kBackBufferName = "KOTEK_BACKBUFFER_GL_NAME";

			class ktkRenderGraphResourceManager
			{
			public:
				ktkRenderGraphResourceManager(
					Core::ktkMainManager& main_manager);
				~ktkRenderGraphResourceManager(void);

				void Initialize(eRenderGraphBuilderType type_of_framebuffer,
					eRenderGraphBuilderPipelineRenderingType
						type_videocard_pipeline);
				void Shutdown(void);

			private:

			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek