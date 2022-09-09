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
						return "Deffered";
					}
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Forward_Only:
					{
						return "Forward_Only";
					}
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Forward_With_Outputs:
					{
						return "Forward_With_Outputs";
					}
					case gl::eRenderGraphBuilderType::
						kRenderBuilderFor_Undefined:
					{
						return "Undefined";
					}
					default:
					{
						return "UNDEFINED_ENUM_OF_RENDER_GRAPH_BUILDER_TYPE";
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
						return "Orthodox";
					}
					case gl::eRenderGraphBuilderPipelineRenderingType::
						kRenderBuilderBasedOnPipeline_RTX:
					{
						return "RTX";
					}
					default:
					{
						return "UNDEFINED_ENUM_OF_RENDER_GRAPH_BUILDER_"
							   "PIPELINE_RENDERING_TYPE";
					}
					}
				}

				ktk::string Translate_ShaderLoadingDataType(
					gl::eShaderLoadingDataType type) noexcept
				{
					switch (type)
					{
					case gl::eShaderLoadingDataType::
						kShaderLoadingDataType_ByteArrayCompiledSPIRV:
					{
						return "ByteArrayCompiledSPIRV";
					}
					case gl::eShaderLoadingDataType::
						kShaderLoadingDataType_ByteArrayFile:
					{
						return "ByteArrayFile";
					}
					case gl::eShaderLoadingDataType::
						kShaderLoadingDataType_FilePathString:
					{
						return "FilePathString";
					}
					case gl::eShaderLoadingDataType::
						kShaderLoadingDataType_NotInitialized:
					{
						return "NotInitialized";
					}
					case gl::eShaderLoadingDataType::
						kShaderLoadingDataType_SourceCode_TextString:
					{
						return "TextString_SourceCode";
					}
					default:
					{
						return "UNDEFINED_ENUM_OF_SHADER_LOADING_DATA_TYPE";
					}
					}
				}
				ktk::string Translate_ShaderType(gl::eShaderType type) noexcept
				{
					switch (type)
					{
					case gl::eShaderType::kShaderType_Compute:
					{
						return "Compute";
					}
					case gl::eShaderType::kShaderType_Fragment:
					{
						return "Fragment";
					}
					case gl::eShaderType::kShaderType_Geometry:
					{
						return "Geometry";
					}
					case gl::eShaderType::kShaderType_Mesh:
					{
						return "Mesh";
					}
					case gl::eShaderType::kShaderType_Task:
					{
						return "Task";
					}
					case gl::eShaderType::kShaderType_TessellationControl:
					{
						return "TessellationControl";
					}
					case gl::eShaderType::kShaderType_TessellationEvaluation:
					{
						return "TessellationEvaluation";
					}
					case gl::eShaderType::kShaderType_Unknown:
					{
						return "Unknown";
					}
					case gl::eShaderType::kShaderType_Vertex:
					{
						return "Vertex";
					}
					default:
					{
						return "UNDEFINED_ENUM_OF_SHADER_TYPE";
					}
					}
				}
			} // namespace helper
		}     // namespace gl
	}         // namespace Render
} // namespace Kotek
