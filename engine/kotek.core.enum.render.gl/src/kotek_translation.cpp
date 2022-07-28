#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			namespace helper
			{
				ktk::string Translate_RenderGraphBuilderTypeToString(
					gl::eRenderGraphBuilderType type) noexcept
				{
					switch (type)
					{
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Deferred:
					{
						return "deffered";
					}
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Forward_Only:
					{
						return "forward only";
					}
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Forward_With_Outputs:
					{
						return "forward with outputs";
					}
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Undefined:
					{
						return "undefined";
					}
					default:
					{
						return "BUILDER_TYPE_UNKNOWN";
					}
					}
				}

				ktk::string Translate_RenderGraphPipelineTypeToString(
					gl::eRenderGraphBuilderPipelineRenderingType type) noexcept
				{
					switch (type)
					{
					case gl::eRenderGraphBuilderPipelineRenderingType::
						kRenderBuilderBasedOnPipeline_Orthodox:
					{
						return "orthodox";
					}
					case gl::eRenderGraphBuilderPipelineRenderingType::
						kRenderBuilderBasedOnPipeline_RTX:
					{
						return "RTX";
					}
					default:
					{
						return "PIPELINE_RENDERING_TYPE_UNKNOWN";
					}
					}
				}
			} // namespace helper
		}     // namespace gl
	}         // namespace Render
} // namespace Kotek
