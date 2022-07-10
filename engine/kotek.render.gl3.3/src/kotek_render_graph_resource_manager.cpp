#include "../include/kotek_render_graph_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderGraphResourceManager::ktkRenderGraphResourceManager(
				Core::ktkMainManager& main_manager)
			{
			}

			ktkRenderGraphResourceManager::~ktkRenderGraphResourceManager(void)
			{
			}

			void ktkRenderGraphResourceManager::Initialize(
				eRenderGraphBuilderType type_of_framebuffer,
				eRenderGraphBuilderPipelineRenderingType
					type_videocard_pipeline)
			{
			}

			void ktkRenderGraphResourceManager::Shutdown(void) {}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek