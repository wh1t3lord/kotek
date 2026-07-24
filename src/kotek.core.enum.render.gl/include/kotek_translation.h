#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	enum class eRenderGraphBuilderType;
	enum class eRenderGraphBuilderPipelineRenderingType;
	enum class eShaderLoadingDataType;
	enum class eShaderType;
} // namespace gl
KOTEK_END_NAMESPACE_RENDER

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	namespace helper
	{
        ktk::cstring Translate_RenderGraphBuilderTypeToString(
			gl::eRenderGraphBuilderType type) noexcept;

        ktk::cstring Translate_RenderGraphPipelineTypeToString(
			gl::eRenderGraphBuilderPipelineRenderingType type) noexcept;

        ktk::cstring Translate_ShaderLoadingDataType(
			gl::eShaderLoadingDataType type) noexcept;

        ktk::cstring Translate_ShaderType(gl::eShaderType type) noexcept;

	} // namespace helper
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
