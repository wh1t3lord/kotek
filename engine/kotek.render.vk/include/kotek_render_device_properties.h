#pragma once

#include <kotek.core/include/kotek_std.h>

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderDeviceProperties
			{
			public:
				ktkRenderDeviceProperties(void);
				ktkRenderDeviceProperties(
					const ktkRenderDeviceProperties&) = default;

				~ktkRenderDeviceProperties(void);

				bool initialize(VkPhysicalDevice p_device) noexcept;

				bool isExtensionPresent(const char* extension_name) noexcept;

				bool addExtensionName(const char* extension_name) noexcept;

				void* getNext(void) const noexcept;

				void setNext(void* p_data) noexcept;

				ktk::uint32_t getCountExtensionsName(void) const noexcept;

				const char* const* getDataExtensionsName(void) const noexcept;

			private:
				ktk::vector<const char*> m_device_extension_names;
				ktk::vector<VkExtensionProperties>
					m_device_extension_properties;
				ktk::any m_p_next;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
