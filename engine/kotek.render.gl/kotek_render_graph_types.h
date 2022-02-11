#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
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

			// TODO: think about array textures, because in VkImageCreateInfo we
			// need to specify arrayLayers
			/// <summary>
			/// This enum uses when we want to create a texture from
			/// texture_manager Because user must specify what type of texture
			/// is using by creation function In that case we can't detect type
			/// of view by format if we don't know what user wants from us
			///
			/// Single means we create a texture for 1D, 2D, 3D type and that's
			/// texture is single it means just one file and one information
			/// Array means we have multiple textures and we use view type for
			/// array it's 1D or 2D Cubemap means you have a cubemap which is
			/// had a type 2D from image and from view it's CUBEMAP
			/// </summary>
			enum class eTextureType : ktk::enum_base_t
			{
				kTextureType_Single,
				kTextureType_Array,
				kTextureType_Cubemap_Single,
				kTextureType_Cubemap_Array,
				kTextureType_Unknown = -1
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek