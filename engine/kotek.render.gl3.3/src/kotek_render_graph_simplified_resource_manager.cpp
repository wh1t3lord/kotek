#include "../include/kotek_render_graph_simplified_resource_manager.h"
#include "../include/kotek_render_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderGraphSimplifiedResourceManager::
				ktkRenderGraphSimplifiedResourceManager(
					Core::ktkMainManager* p_main_manager) :
				m_p_render_device{static_cast<ktkRenderDevice*>(
					p_main_manager->getRenderDevice())},
				m_p_manager_resource{static_cast<Core::ktkResourceManager*>(
					p_main_manager->GetResourceManager())}
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
				KOTEK_ASSERT(this->m_p_render_device,
					"you must initialize ktkRenderDevice");
				KOTEK_ASSERT(this->m_p_manager_resource,
					"you must initialize ktkResourceManager");

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