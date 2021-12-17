#include "kotek_render_device_properties.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_device_properties::kotek_render_device_properties() {}

			kotek_render_device_properties::~kotek_render_device_properties() {}

			bool kotek_render_device_properties::initialize(
				VkPhysicalDevice p_device) noexcept
			{
				ktk::uint32_t extension_count = 0;

				VkResult status = vkEnumerateDeviceExtensionProperties(
					p_device, nullptr, &extension_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkEnumerateDeviceExtensionProperties");

				this->m_device_extension_properties.resize(extension_count);

				status = vkEnumerateDeviceExtensionProperties(p_device, nullptr,
					&extension_count,
					this->m_device_extension_properties.data());

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to fill the device extension properties by "
					"vkEnumerateDeviceExtensionProperties");

				// @ Detecting device extensions in layers of instance
				// Because for some OSs Vulkan doesn't obtain extensions well
				// for both instance and device Thus we need manually checking
				// yourself for that fact Did we get all extensions??? For this
				// case we have KOTEK_MESSAGE("new extension added from layer:
				// ") or something similar;

				ktk::uint32_t instance_layer_property_count = 0;

				ktk::vector<VkLayerProperties> layers;

				status = vkEnumerateInstanceLayerProperties(
					&instance_layer_property_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"invalid operation vkEnumerateInstanceLayerProperties. See "
					"status code");

				layers.resize(instance_layer_property_count);

				if (instance_layer_property_count)
				{
					status = vkEnumerateInstanceLayerProperties(
						&instance_layer_property_count, layers.data());

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't fill vector of VkLayerProperties by "
						"vkEnumerateInstanceLayerProperties. See status code");

					if (layers.empty() == false)
					{
						for (const auto& layer : layers)
						{
							extension_count = 0;

							status =
								vkEnumerateDeviceExtensionProperties(p_device,
									layer.layerName, &extension_count, nullptr);

							KOTEK_ASSERT(status == VK_SUCCESS,
								"failed to get count from "
								"vkEnumerateDeviceExtensionProperties");

							if (extension_count)
							{
								ktk::vector<VkExtensionProperties>
									new_extensions;

								new_extensions.resize(extension_count);

								status = vkEnumerateDeviceExtensionProperties(
									p_device, layer.layerName, &extension_count,
									new_extensions.data());

								KOTEK_ASSERT(status == VK_SUCCESS,
									"failed to fill vector from "
									"vkEnumerateDeviceExtensionProperties");

								if (new_extensions.empty() == false)
								{
									for (const auto& extension : new_extensions)
									{
										if (this->isExtensionPresent(
												extension.extensionName) ==
											false)
										{
											KOTEK_MESSAGE(
												"obtained new device extension "
												"from layer[{}]: {}",
												ktk::cast::to_string(
													layer.layerName),
												ktk::cast::to_string(
													extension.extensionName));

											this->m_device_extension_properties
												.push_back(extension);
										}
									}
								}
							}
						}
					}
				}

				return true;
			}

			bool kotek_render_device_properties::isExtensionPresent(
				const char* extension_name) noexcept
			{
				return std::find_if(this->m_device_extension_properties.begin(),
						   this->m_device_extension_properties.end(),
						   [extension_name](
							   const VkExtensionProperties& prop) -> bool {
							   return strcmp(extension_name,
										  prop.extensionName) == 0;
						   }) != this->m_device_extension_properties.end();
			}

			bool kotek_render_device_properties::addExtensionName(
				const char* extension_name) noexcept
			{
				if (this->isExtensionPresent(extension_name))
				{
					this->m_device_extension_names.push_back(extension_name);
					return true;
				}

				KOTEK_ASSERT(false, "can't add extension: [{}]",
					ktk::cast::to_string(extension_name));

				return false;
			}

			void* kotek_render_device_properties::getNext(void) const noexcept
			{
				if (this->m_p_next.has_value())
					return std::any_cast<void*>(this->m_p_next);

				return static_cast<void*>(nullptr);
			}

			void kotek_render_device_properties::setNext(void* p_data) noexcept
			{
				this->m_p_next = p_data;
			}

			ktk::uint32_t
			kotek_render_device_properties::getCountExtensionsName(
				void) const noexcept
			{
				return this->m_device_extension_names.size();
			}

			const char* const*
			kotek_render_device_properties::getDataExtensionsName(
				void) const noexcept
			{
				return this->m_device_extension_names.data();
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
