#include "../include/kotek_translation.h"
#include "../include/kotek_enum.h"

#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	namespace helper
	{
        ktk::cstring Translate_RenderGraphBuilderTypeToString(
			gl::eRenderGraphBuilderType type) noexcept
		{
			switch (type)
			{
			case gl::eRenderGraphBuilderType::kRenderBuilderFor_Deferred:
			{
                return KOTEK_TEXTU("Deffered");
			}
			case gl::eRenderGraphBuilderType::kRenderBuilderFor_Forward_Only:
			{
                return KOTEK_TEXTU("Forward_Only");
			}
			case gl::eRenderGraphBuilderType::
				kRenderBuilderFor_Forward_With_Outputs:
			{
                return KOTEK_TEXTU("Forward_With_Outputs");
			}
			case gl::eRenderGraphBuilderType::kRenderBuilderFor_Undefined:
			{
                return KOTEK_TEXTU("Undefined");
			}
			default:
			{
                return KOTEK_TEXTU("UNDEFINED_ENUM_OF_RENDER_GRAPH_BUILDER_TYPE");
			}
			}
		}

        ktk::cstring Translate_RenderGraphPipelineTypeToString(
			gl::eRenderGraphBuilderPipelineRenderingType type) noexcept
		{
			switch (type)
			{
			case gl::eRenderGraphBuilderPipelineRenderingType::
				kRenderBuilderBasedOnPipeline_Orthodox:
			{
                return KOTEK_TEXTU("Orthodox");
			}
			case gl::eRenderGraphBuilderPipelineRenderingType::
				kRenderBuilderBasedOnPipeline_RTX:
			{
                return KOTEK_TEXTU("RTX");
			}
			default:
			{
                return KOTEK_TEXTU("UNDEFINED_ENUM_OF_RENDER_GRAPH_BUILDER_"
                       "PIPELINE_RENDERING_TYPE");
			}
			}
		}

        ktk::cstring Translate_ShaderLoadingDataType(
			gl::eShaderLoadingDataType type) noexcept
		{
			switch (type)
			{
			case gl::eShaderLoadingDataType::
				kShaderLoadingDataType_ByteArrayCompiledSPIRV:
			{
                return KOTEK_TEXTU("ByteArrayCompiledSPIRV");
			}
			case gl::eShaderLoadingDataType::
				kShaderLoadingDataType_ByteArrayFile:
			{
                return KOTEK_TEXTU("ByteArrayFile");
			}
			case gl::eShaderLoadingDataType::
				kShaderLoadingDataType_FilePathString:
			{
                return KOTEK_TEXTU("FilePathString");
			}
			case gl::eShaderLoadingDataType::
				kShaderLoadingDataType_NotInitialized:
			{
                return KOTEK_TEXTU("NotInitialized");
			}
			case gl::eShaderLoadingDataType::
				kShaderLoadingDataType_SourceCode_TextString:
			{
                return KOTEK_TEXTU("TextString_SourceCode");
			}
			default:
			{
                return KOTEK_TEXTU("UNDEFINED_ENUM_OF_SHADER_LOADING_DATA_TYPE");
			}
			}
		}

        ktk::cstring Translate_ShaderType(gl::eShaderType type) noexcept
		{
			switch (type)
			{
			case gl::eShaderType::kShaderType_Compute:
			{
                return KOTEK_TEXTU("Compute");
			}
			case gl::eShaderType::kShaderType_Fragment:
			{
                return KOTEK_TEXTU("Fragment");
			}
			case gl::eShaderType::kShaderType_Geometry:
			{
                return KOTEK_TEXTU("Geometry");
			}
			case gl::eShaderType::kShaderType_Mesh:
			{
                return KOTEK_TEXTU("Mesh");
			}
			case gl::eShaderType::kShaderType_Task:
			{
                return KOTEK_TEXTU("Task");
			}
			case gl::eShaderType::kShaderType_TessellationControl:
			{
                return KOTEK_TEXTU("TessellationControl");
			}
			case gl::eShaderType::kShaderType_TessellationEvaluation:
			{
                return KOTEK_TEXTU("TessellationEvaluation");
			}
			case gl::eShaderType::kShaderType_Unknown:
			{
                return KOTEK_TEXTU("Unknown");
			}
			case gl::eShaderType::kShaderType_Vertex:
			{
                return KOTEK_TEXTU("Vertex");
			}
			default:
			{
                return KOTEK_TEXTU("UNDEFINED_ENUM_OF_SHADER_TYPE");
			}
			}
		}
	} // namespace helper
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
