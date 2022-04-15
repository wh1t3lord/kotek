#include "../include/kotek_render_helper_device.h"

namespace Kotek
{
	constexpr ktk::int32_t _kTexelBlockEncodesAs_2x1 = 2;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_4x4 = 16;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_5x4 = 20;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_5x5 = 25;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_6x5 = 30;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_6x6 = 36;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_8x4 = 32;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_8x5 = 40;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_8x6 = 48;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_8x8 = 64;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_10x5 = 50;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_10x6 = 60;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_10x8 = 80;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_10x10 = 100;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_12x10 = 120;
	constexpr ktk::int32_t _kTexelBlockEncodesAs_12x12 = 144;
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_helper_device::kotek_render_helper_device(void) :
				m_helper_debug(this)
			{
			}

			kotek_render_helper_device::~kotek_render_helper_device(void) {}

			ktk::uint32_t kotek_render_helper_device::getSizeInBytesByFormat(
				VkFormat image_format) const noexcept
			{
				switch (image_format)
				{
				case VkFormat::VK_FORMAT_R4G4_UNORM_PACK8:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_SINT:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_SNORM:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_SRGB:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_SSCALED:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_UINT:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_UNORM:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8_USCALED:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_S8_UINT:
				{
					return 1;
				}
				case VkFormat::VK_FORMAT_R8G8_SINT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R8G8_SNORM:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R8G8_SRGB:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R8G8_SSCALED:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R8G8_UINT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R8G8_UNORM:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R8G8_USCALED:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_B4G4R4A4_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_B5G5R5A1_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_B5G6R5_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_D16_UNORM:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R10X6_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R12X4_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_SFLOAT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_SINT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_SNORM:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_SSCALED:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_UINT:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_UNORM:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R16_USCALED:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R4G4B4A4_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R5G5B5A1_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_R5G6B5_UNORM_PACK16:
				{
					return 2;
				}
				case VkFormat::VK_FORMAT_B8G8R8_SINT:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_B8G8R8_SNORM:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_B8G8R8_SRGB:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_B8G8R8_SSCALED:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_B8G8R8_UINT:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_B8G8R8_UNORM:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_B8G8R8_USCALED:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_D16_UNORM_S8_UINT:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_SINT:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_SNORM:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_SRGB:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_SSCALED:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_UINT:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_UNORM:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_R8G8B8_USCALED:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM:
				{
					return 3;
				}
				case VkFormat::VK_FORMAT_A2B10G10R10_SINT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2B10G10R10_SNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2B10G10R10_SSCALED_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2B10G10R10_UINT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2B10G10R10_UNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2B10G10R10_USCALED_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2R10G10B10_SINT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2R10G10B10_SNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2R10G10B10_SSCALED_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2R10G10B10_UINT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2R10G10B10_UNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A2R10G10B10_USCALED_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_SINT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_SNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_SSCALED_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_UINT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_UNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_A8B8G8R8_USCALED_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B10G11R11_UFLOAT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_SINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_SNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_SRGB:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_SSCALED:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_UINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_UNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8A8_USCALED:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_B8G8R8G8_422_UNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_D24_UNORM_S8_UINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_D32_SFLOAT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_E5B9G9R9_UFLOAT_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R10X6G10X6_UNORM_2PACK16:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R12X4G12X4_UNORM_2PACK16:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_SFLOAT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_SINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_SNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_SSCALED:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_UINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_UNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R16G16_USCALED:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R32_SFLOAT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R32_SINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R32_UINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_SINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_SNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_SRGB:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_SSCALED:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_UINT:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_UNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_R8G8B8A8_USCALED:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_X8_D24_UNORM_PACK32:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_G8_B8R8_2PLANE_422_UNORM:
				{
					return 4;
				}
				case VkFormat::VK_FORMAT_G8B8G8R8_422_UNORM:
				{
					return 4;
				}
				case VkFormat::
					VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16:
				{
					return 6;
				}
				case VkFormat::
					VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT:
				{
					return 6;
				}
				case VkFormat::
					VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16:
				{
					return 6;
				}
				case VkFormat::
					VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_SFLOAT:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_SINT:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_SNORM:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_SSCALED:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_UINT:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_UNORM:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_R16G16B16_USCALED:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM:
				{
					return 6;
				}
				case VkFormat::VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_B16G16R16G16_422_UNORM:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_BC1_RGB_SRGB_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_BC1_RGB_UNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_BC4_SNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_BC4_UNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_D32_SFLOAT_S8_UINT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_EAC_R11_SNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_EAC_R11_UNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK:
				{
					return 8;
				}
				case VkFormat::
					VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16:
				{
					return 8;
				}
				case VkFormat::
					VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16:
				{
					return 8;
				}
				case VkFormat::
					VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16:
				{
					return 8;
				}
				case VkFormat::
					VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_G16_B16R16_2PLANE_422_UNORM:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_G16B16G16R16_422_UNORM:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_SINT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_SNORM:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_SSCALED:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_UINT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_UNORM:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R16G16B16A16_USCALED:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R32G32_SFLOAT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R32G32_SINT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R32G32_UINT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R64_SFLOAT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R64_SINT:
				{
					return 8;
				}
				case VkFormat::VK_FORMAT_R64_UINT:
				{
					return 8;
				}
				case VkFormat::
					VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16:
				{
					return 12;
				}
				case VkFormat::
					VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16:
				{
					return 12;
				}
				case VkFormat::
					VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16:
				{
					return 12;
				}
				case VkFormat::
					VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16:
				{
					return 12;
				}
				case VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM:
				{
					return 12;
				}
				case VkFormat::VK_FORMAT_G16_B16R16_2PLANE_420_UNORM:
				{
					return 12;
				}
				case VkFormat::VK_FORMAT_R32G32B32_SFLOAT:
				{
					return 12;
				}
				case VkFormat::VK_FORMAT_R32G32B32_SINT:
				{
					return 12;
				}
				case VkFormat::VK_FORMAT_R32G32B32_UINT:
				{
					return 12;
				}
				case VkFormat::VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x10_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x10_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x5_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x5_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x6_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x6_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x8_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_10x8_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_12x10_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_12x10_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_12x12_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_12x12_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_4x4_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_4x4_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_5x4_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_5x4_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_5x5_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_5x5_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_6x5_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_6x5_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_6x6_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_6x6_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x5_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x5_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x6_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x6_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x8_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ASTC_8x8_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC2_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC2_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC3_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC3_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC5_SNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC5_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC6H_SFLOAT_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC6H_UFLOAT_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC7_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_BC7_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_EAC_R11G11_SNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_EAC_R11G11_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R32G32B32A32_SINT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R32G32B32A32_UINT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R64G64_SFLOAT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R64G64_SINT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R64G64_UINT:
				{
					return 16;
				}
				case VkFormat::VK_FORMAT_R64G64B64_SFLOAT:
				{
					return 24;
				}
				case VkFormat::VK_FORMAT_R64G64B64_SINT:
				{
					return 24;
				}
				case VkFormat::VK_FORMAT_R64G64B64_UINT:
				{
					return 24;
				}
				case VkFormat::VK_FORMAT_R64G64B64A64_SFLOAT:
				{
					return 32;
				}
				case VkFormat::VK_FORMAT_R64G64B64A64_SINT:
				{
					return 32;
				}
				case VkFormat::VK_FORMAT_R64G64B64A64_UINT:
				{
					return 32;
				}
				case VkFormat::VK_FORMAT_UNDEFINED:
				{
					KOTEK_ASSERT(false, "undefined format, return ZERO (0)!!!");
					return 0;
				}
				default:
				{
					KOTEK_ASSERT(false,
						"invalid format or system doesn't support it: {}",
						image_format);
					return 0;
				}
				}
			}

			ktk::uint32_t kotek_render_helper_device::getPixelsPerBlockByFormat(
				VkFormat image_format) const noexcept
			{
				switch (image_format)
				{
				case VkFormat::VK_FORMAT_G8B8G8R8_422_UNORM:
				case VkFormat::VK_FORMAT_B8G8R8G8_422_UNORM:
				case VkFormat::VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16:
				case VkFormat::VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16:
				case VkFormat::VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16:
				case VkFormat::VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16:
				case VkFormat::VK_FORMAT_G16B16G16R16_422_UNORM:
				case VkFormat::VK_FORMAT_B16G16R16G16_422_UNORM:
					return _kTexelBlockEncodesAs_2x1;
				case VkFormat::VK_FORMAT_BC1_RGB_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC1_RGB_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_BC2_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC2_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_BC3_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC3_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_BC4_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC4_SNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC5_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC5_SNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC6H_UFLOAT_BLOCK:
				case VkFormat::VK_FORMAT_BC6H_SFLOAT_BLOCK:
				case VkFormat::VK_FORMAT_BC7_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_BC7_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_EAC_R11_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_EAC_R11_SNORM_BLOCK:
				case VkFormat::VK_FORMAT_EAC_R11G11_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_EAC_R11G11_SNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_4x4_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_4x4_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT:
				case VkFormat::VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG:
				case VkFormat::VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG:
				case VkFormat::VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG:
				case VkFormat::VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG:
					return _kTexelBlockEncodesAs_4x4;
				case VkFormat::VK_FORMAT_ASTC_5x4_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_5x4_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_5x4;
				case VkFormat::VK_FORMAT_ASTC_5x5_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_5x5_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_5x5;
				case VkFormat::VK_FORMAT_ASTC_6x5_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_6x5_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_6x5;
				case VkFormat::VK_FORMAT_ASTC_6x6_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_6x6_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_6x6;
				case VkFormat::VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG:
				case VkFormat::VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG:
				case VkFormat::VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG:
				case VkFormat::VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG:
					return _kTexelBlockEncodesAs_8x4;
				case VkFormat::VK_FORMAT_ASTC_8x5_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_8x5_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_8x5;
				case VkFormat::VK_FORMAT_ASTC_8x6_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_8x6_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_8x6;
				case VkFormat::VK_FORMAT_ASTC_8x8_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_8x8_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_8x8;
				case VkFormat::VK_FORMAT_ASTC_10x5_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x5_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_10x5;
				case VkFormat::VK_FORMAT_ASTC_10x6_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x6_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_10x6;
				case VkFormat::VK_FORMAT_ASTC_10x8_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x8_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_10x8;
				case VkFormat::VK_FORMAT_ASTC_10x10_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x10_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_10x10;
				case VkFormat::VK_FORMAT_ASTC_12x10_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_12x10_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_12x10;
				case VkFormat::VK_FORMAT_ASTC_12x12_UNORM_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_12x12_SRGB_BLOCK:
				case VkFormat::VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT:
					return _kTexelBlockEncodesAs_12x12;
				default:
				{
					return 1;
				}
				}
			}

			const kotek_render_helper_debug&
			kotek_render_helper_device::getDebug(void) const noexcept
			{
				return this->m_helper_debug;
			}

			void kotek_render_helper_device::initialize(
				VkDevice p_device, VkInstance p_instance) noexcept
			{
				this->m_helper_debug.initialize(p_device, p_instance);
			}

			void kotek_render_helper_device::shutdown(void) noexcept
			{
				this->m_helper_debug.shutdown();
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek