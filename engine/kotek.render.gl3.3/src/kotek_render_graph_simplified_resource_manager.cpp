#include "../include/kotek_render_graph_simplified_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderGraphSimplifiedResourceManager::
				ktkRenderGraphSimplifiedResourceManager(
					Core::ktkMainManager& main_manager)
			{
			}

			ktkRenderGraphSimplifiedResourceManager::
				~ktkRenderGraphSimplifiedResourceManager(void)
			{
			}

			void ktkRenderGraphSimplifiedResourceManager::Initialize(
				gl::eRenderGraphBuilderType type_of_framebuffer,
				gl::eRenderGraphBuilderPipelineRenderingType
					type_videocard_pipeline)
			{
				if (type_of_framebuffer ==
					gl::eRenderGraphBuilderType::kRenderBuilderFor_Forward_Only)
				{
				}
				else
				{
					KOTEK_ASSERT(false, "not implemented!");
				}
			}

			void ktkRenderGraphSimplifiedResourceManager::Shutdown(void) {}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek