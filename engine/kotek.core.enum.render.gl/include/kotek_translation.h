#pragma once

namespace Kotek
{
	namespace ktk
	{
		class string;
	}

	namespace Render
	{
		namespace gl
		{
			enum class eRenderGraphBuilderType;
			enum class eRenderGraphBuilderPipelineRenderingType;
			enum class eShaderLoadingDataType;
			enum class eShaderType;
		} // namespace gl
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			namespace helper
			{
				ktk::string Translate_RenderGraphBuilderTypeToString(
					gl::eRenderGraphBuilderType type) noexcept;

				ktk::string Translate_RenderGraphPipelineTypeToString(
					gl::eRenderGraphBuilderPipelineRenderingType type) noexcept;

				ktk::string Translate_ShaderLoadingDataType(
					gl::eShaderLoadingDataType type) noexcept;

				ktk::string Translate_ShaderType(gl::eShaderType type) noexcept;

			} // namespace helper
		}     // namespace gl
	}         // namespace Render
} // namespace Kotek
