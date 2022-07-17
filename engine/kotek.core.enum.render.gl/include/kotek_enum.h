#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			// TODO: move to one project that will be shared to other gl
			// versions and do it for other GAPIs
			enum class eRenderGraphBuilderType : ktk::enum_base_t
			{
				/// <summary>
				/// Uses backbuffer only, so you have only one render target for
				/// all passes
				/// </summary>
				kRenderBuilderFor_Forward_Only,
				// TODO: implement for outputs but we need to merge into back
				// buffer?
				kRenderBuilderFor_Forward_With_Outputs,
				// TODO: implement for deferred sometime...
				kRenderBuilderFor_Deferred,
				kRenderBuilderFor_Undefined
			};

			enum class eRenderGraphBuilderPipelineRenderingType : ktk::
				enum_base_t
			{
				kRenderBuilderBasedOnPipeline_Orthodox,

				// TODO: add support for RTX in new version
				kRenderBuilderBasedOnPipeline_RTX
			};

			enum class eResourceSynchronizationStatus : ktk::enum_base_t
			{
				kEmpty,
				kFromOutputToInput,
				kToInputOnly
			};

			enum class eShaderLoadingDataType : ktk::enum_base_t
			{
				kShaderLoadingDataType_FilePathString,
				kShaderLoadingDataType_SourceCode_TextString,
				kShaderLoadingDataType_ByteArrayFile,
				kShaderLoadingDataType_ByteArrayCompiledSPIRV,
				kShaderLoadingDataType_NotInitialized = -1
			};

			enum class eShaderType : ktk::enum_base_t
			{
				kShaderType_Vertex,
				// @ fragment
				kShaderType_Pixel,
				kShaderType_Geometry,
				kShaderType_Compute,
				kShaderType_Mesh,
				kShaderType_Task,
				kShaderType_TessellationControl,
				kShaderType_TessellationEvaluation,
				kShaderType_RTX_Generation,
				kShaderType_RTX_Intersection,
				kShaderType_RTX_AnyHit,
				kShaderType_RTX_ClosesHit,
				kShaderType_RTX_Miss,
				kShaderType_RTX_Callable,

				kShaderType_Unknown = -1
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek