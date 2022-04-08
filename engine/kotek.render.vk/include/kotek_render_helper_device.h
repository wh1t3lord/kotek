#pragma once

#include <kotek.core/include/kotek_std.h>
#include "kotek_render_helper_debug.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_helper_device
			{
			public:
				kotek_render_helper_device(void);
				~kotek_render_helper_device(void);

				/// <summary>
				/// https://vulkan.lunarg.com/doc/view/1.2.135.0/windows/chunked_spec/chap39.html
				/// 39.1.6. Format Compatibility Classes
				///
				/// https://github.com/KhronosGroup/Vulkan-ValidationLayers/blob/master/layers/vk_format_utils.cpp
				///
				/// Total formats: 246 + UNDEFINED enum
				/// </summary>
				/// <param name="image_format"></param>
				/// <returns></returns>
				ktk::uint32_t getSizeInBytesByFormat(
					VkFormat image_format) const noexcept;

				ktk::uint32_t getPixelsPerBlockByFormat(
					VkFormat image_format) const noexcept;

				const kotek_render_helper_debug& getDebug(void) const noexcept;

				void initialize(
					VkDevice p_device, VkInstance p_instance) noexcept;
				void shutdown(void) noexcept;

				template <typename ToCastType>
				bool obtainFunctionFromVulkanAPI(ToCastType& p_callback,
					VkDevice p_device, VkInstance p_instance,
					const char* function_name) const noexcept
				{
					KOTEK_ASSERT(
						p_device, "you can't pass invalid VkDevice here");
					KOTEK_ASSERT(
						p_instance, "you can't pass invalid VkInstance here");
					KOTEK_ASSERT(
						function_name, "you can't pass invalid pointer string");

					bool is_obtained_successfully = true;

					p_callback = reinterpret_cast<ToCastType>(
						vkGetDeviceProcAddr(p_device, function_name));

					if (p_callback == nullptr)
					{
						p_callback = reinterpret_cast<ToCastType>(
							vkGetInstanceProcAddr(p_instance, function_name));

						if (p_callback == nullptr)
						{
							is_obtained_successfully = false;
						}
					}

					return is_obtained_successfully;
				}

			private:
				kotek_render_helper_debug m_helper_debug;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek