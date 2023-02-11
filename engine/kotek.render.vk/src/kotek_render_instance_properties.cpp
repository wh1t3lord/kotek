#include "../include/kotek_render_instance_properties.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_instance_properties::kotek_render_instance_properties()
			{
			}

			kotek_render_instance_properties::
				~kotek_render_instance_properties()
			{
			}

			bool kotek_render_instance_properties::initialize()
			{
				this->queryInstanceLayers();
				this->queryInstanceExtensions();

				return true;
			}

			bool kotek_render_instance_properties::isLayerPresent(
				const char* p_extension_name) noexcept
			{
				return std::find_if(this->m_layer_properties.begin(),
						   this->m_layer_properties.end(),
						   [p_extension_name](
							   const VkLayerProperties& prop) -> bool {
							   return strcmp(prop.layerName,
										  p_extension_name) == 0;
						   }) != this->m_layer_properties.end();
			}

			bool kotek_render_instance_properties::isExtensionPresent(
				const char* p_extension_name) noexcept
			{
				return std::find_if(this->m_extension_properties.begin(),
						   this->m_extension_properties.end(),
						   [p_extension_name](
							   const VkExtensionProperties& prop) -> bool {
							   return strcmp(prop.extensionName,
										  p_extension_name) == 0;
						   }) != this->m_extension_properties.end();
			}

			bool kotek_render_instance_properties::addExtensionName(
				const char* p_instance_extension_name) noexcept
			{
				if (this->isExtensionPresent(p_instance_extension_name))
				{
#ifdef KOTEK_DEBUG
                    KOTEK_MESSAGE(
                        "add extension: [{}]", p_instance_extension_name);
#endif

					this->m_extension_names.push_back(
						p_instance_extension_name);
					return true;
				}

				KOTEK_ASSERT(false, "extension doesn't exist in vulkan: [{}]",
                    p_instance_extension_name);

				return false;
			}

			bool kotek_render_instance_properties::addLayerName(
				const char* p_instance_layer_name) noexcept
			{
				if (this->isLayerPresent(p_instance_layer_name))
				{
#ifdef KOTEK_DEBUG
                    KOTEK_MESSAGE("add layer: [{}]", p_instance_layer_name);
#endif

					this->m_layer_names.push_back(p_instance_layer_name);
					return true;
				}

				KOTEK_ASSERT(false, "layer doesn't exist in vulkan: [{}]",
                    p_instance_layer_name);

				return false;
			}

			void* kotek_render_instance_properties::getNext(void) const noexcept
			{
				if (this->m_p_next.has_value())
					return std::any_cast<void*>(this->m_p_next);

				return static_cast<void*>(nullptr);
			}

			void kotek_render_instance_properties::setNext(
				void* p_data) noexcept
			{
				this->m_p_next = p_data;
			}

			ktk::uint32_t kotek_render_instance_properties::getCountLayersName(
				void) const noexcept
			{
				return this->m_layer_names.size();
			}

			ktk::uint32_t
			kotek_render_instance_properties::getCountExtensionsName(
				void) const noexcept
			{
				return this->m_extension_names.size();
			}

			const char* const*
			kotek_render_instance_properties::getDataLayersName(
				void) const noexcept
			{
				return this->m_layer_names.data();
			}

			const char* const*
			kotek_render_instance_properties::getDataExtensionsName(
				void) const noexcept
			{
				return this->m_extension_names.data();
			}

			void
			kotek_render_instance_properties::queryInstanceLayers() noexcept
			{
				ktk::uint32_t instance_layer_property_count = 0;

				VkResult status = vkEnumerateInstanceLayerProperties(
					&instance_layer_property_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"invalid operation vkEnumerateInstanceLayerProperties. See "
					"status code");

				this->m_layer_properties.resize(instance_layer_property_count);

				if (instance_layer_property_count)
				{
					status = vkEnumerateInstanceLayerProperties(
						&instance_layer_property_count,
						this->m_layer_properties.data());

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't fill vector of VkLayerProperties by "
						"vkEnumerateInstanceLayerProperties. See status code");
				}
			}

			void
			kotek_render_instance_properties::queryInstanceExtensions() noexcept
			{
				ktk::uint32_t instance_extension_property_count = 0;

				VkResult status = vkEnumerateInstanceExtensionProperties(
					nullptr, &instance_extension_property_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"invalid operation vkEnumerateInstanceExtensionProperties. "
					"See "
					"status code");

				this->m_extension_properties.resize(
					instance_extension_property_count);

				if (instance_extension_property_count)
				{
					status = vkEnumerateInstanceExtensionProperties(nullptr,
						&instance_extension_property_count,
						this->m_extension_properties.data());

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't fill vector of VkExtensionProperties by "
						"vkEnumerateInstanceExtensionProperties");
				}

				ktk::uint32_t temp_count = 0;

				// @ obtain information about every layer, because
				// default vkEnumerateInstanceExtensionProperties(nullptr,
				// &variable, p_data) can't obtain every extensions of every
				// layers, thus we do this loop
				for (const auto& layer : this->m_layer_properties)
				{
					status = vkEnumerateInstanceExtensionProperties(
						layer.layerName, &temp_count, nullptr);
					if (status == VK_SUCCESS)
					{
						if (temp_count)
						{
							ktk::vector<VkExtensionProperties> temp_data;

							temp_data.resize(temp_count);

							status = vkEnumerateInstanceExtensionProperties(
								layer.layerName, &temp_count, temp_data.data());

							if (status == VK_SUCCESS)
							{
								KOTEK_MESSAGE("obtained extensions for layer: "
											  "[{}], count:{}",
                                    layer.layerName, temp_data.size());

								for (const auto& extension : temp_data)
								{
									if (this->isExtensionPresent(
											extension.extensionName) == false)
									{
                                        KOTEK_MESSAGE("new extension added: {}",
                                            extension.extensionName);

										this->m_extension_properties.push_back(
											extension);
									}
								}
							}
						}
					}
					else
					{
						KOTEK_MESSAGE(
							"! can't obtain extensions for layer: [{}]",
                            layer.layerName);
					}
				}
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
