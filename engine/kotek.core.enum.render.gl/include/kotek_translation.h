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
		}
	} // namespace Render
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
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek
