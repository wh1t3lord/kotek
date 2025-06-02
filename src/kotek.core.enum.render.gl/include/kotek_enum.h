#pragma once

#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

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

	enum class eRenderGraphBuilderPipelineRenderingType : ktk::enum_base_t
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

	// TODO: replace all old shader_type_t enums and use one global for
	// every API but from appropriate shared like you can't use
	// eShaderType from gl in vk
	enum class eShaderType : ktk::enum_base_t
	{
		kShaderType_Vertex,
		kShaderType_Fragment,

		kShaderType_Geometry,
		kShaderType_Compute,
		kShaderType_Mesh,
		kShaderType_Task,
		kShaderType_TessellationControl,
		kShaderType_TessellationEvaluation,
		kShaderType_Unknown = -1
	};
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK