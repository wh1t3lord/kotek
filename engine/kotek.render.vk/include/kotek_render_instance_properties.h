#pragma once

#include <kotek.core/include/kotek_std.h>

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_instance_properties
			{
			public:
				kotek_render_instance_properties(void);
				kotek_render_instance_properties(
					const kotek_render_instance_properties&) = default;

				~kotek_render_instance_properties(void);

				bool initialize(void);

				bool isLayerPresent(const char* p_extension_name) noexcept;

				bool isExtensionPresent(const char* p_extension_name) noexcept;

				bool addExtensionName(
					const char* p_instance_extension_name) noexcept;

				bool addLayerName(const char* p_instance_layer_name) noexcept;

				void* getNext(void) const noexcept;

				void setNext(void* p_data) noexcept;

				ktk::uint32_t getCountLayersName(void) const noexcept;

				ktk::uint32_t getCountExtensionsName(void) const noexcept;

				const char* const* getDataLayersName(void) const noexcept;

				const char* const* getDataExtensionsName(void) const noexcept;

			private:
				void queryInstanceLayers(void) noexcept;
				void queryInstanceExtensions(void) noexcept;

			private:
				ktk::vector<VkLayerProperties> m_layer_properties;
				ktk::vector<VkExtensionProperties> m_extension_properties;
				ktk::vector<const char*> m_layer_names;
				ktk::vector<const char*> m_extension_names;
				ktk::any m_p_next;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
