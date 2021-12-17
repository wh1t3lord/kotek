#include "kotek_render_helper_debug.h"
#include "kotek_render_helper_device.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			kotek_render_helper_debug::kotek_render_helper_debug(
				kotek_render_helper_device* p_helper) :
				m_p_callback_marker_begin(nullptr),
				m_p_callback_marker_insert(nullptr),
				m_p_callback_marker_end(nullptr),
				m_p_callback_set_debug_name(nullptr),
				m_p_callback_set_tag_object(nullptr), m_p_helper(p_helper)
			{
			}

			kotek_render_helper_debug::~kotek_render_helper_debug(void) {}

			void kotek_render_helper_debug::initialize(
				VkDevice p_device, VkInstance p_instance)
			{
				KOTEK_ASSERT(p_device, "your VkDevice is invalid!");

				KOTEK_ASSERT(this->m_p_helper,
					"you can't have invalid helper device class");

				KOTEK_ASSERT(this->m_p_helper->obtainFunctionFromVulkanAPI<
								 PFN_vkSetDebugUtilsObjectNameEXT>(
								 this->m_p_callback_set_debug_name, p_device,
								 p_instance, "vkSetDebugUtilsObjectNameEXT"),
					"can't obtain function vkSetDebugUtilsObjectNameEXT from "
					"Vulkan API "
					"(made both attempts "
					"from VkDevice and VkInstance)");

				KOTEK_ASSERT(this->m_p_helper->obtainFunctionFromVulkanAPI<
								 PFN_vkCmdDebugMarkerBeginEXT>(
								 this->m_p_callback_marker_begin, p_device,
								 p_instance, "vkCmdDebugMarkerBeginEXT"),
					"can't obtain function vkCmdDebugMarkerBeginEXT from "
					"Vulkan API "
					"(made both attempts "
					"from VkDevice and VkInstance)");

				KOTEK_ASSERT(this->m_p_helper->obtainFunctionFromVulkanAPI<
								 PFN_vkCmdDebugMarkerEndEXT>(
								 this->m_p_callback_marker_end, p_device,
								 p_instance, "vkCmdDebugMarkerEndEXT"),
					"can't obtain function vkCmdDebugMarkerEndEXT from Vulkan "
					"API "
					"(made both attempts "
					"from VkDevice and VkInstance)");

				KOTEK_ASSERT(this->m_p_helper->obtainFunctionFromVulkanAPI<
								 PFN_vkCmdDebugMarkerInsertEXT>(
								 this->m_p_callback_marker_insert, p_device,
								 p_instance, "vkCmdDebugMarkerInsertEXT"),
					"can't obtain function vkCmdDebugMarkerInsertEXT from "
					"Vulkan API "
					"(made both attempts "
					"from VkDevice and VkInstance)");

				KOTEK_ASSERT(this->m_p_helper->obtainFunctionFromVulkanAPI<
								 PFN_vkDebugMarkerSetObjectTagEXT>(
								 this->m_p_callback_set_tag_object, p_device,
								 p_instance, "vkDebugMarkerSetObjectTagEXT"),
					"can't obtain function vkDebugMarkerSetObjectTagEXT from "
					"Vulkan API "
					"(made both attempts "
					"from VkDevice and VkInstance)");
			}

			void kotek_render_helper_debug::shutdown(void) {}

			void kotek_render_helper_debug::setDebugNameToResource(
				VkDevice p_device, VkObjectType resource_type, void* p_resource,
				const char* debug_name) const noexcept
			{
#ifdef KOTEK_DEBUG
				KOTEK_ASSERT(p_device, "must be valid device (VkDevice)");
				KOTEK_ASSERT(p_resource, "object must be valid");

				VkDebugUtilsObjectNameInfoEXT info = {};

				info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
				info.objectType = resource_type;
				info.objectHandle = reinterpret_cast<ktk::uint64_t>(p_resource);
				info.pObjectName = debug_name;

				this->m_p_callback_set_debug_name(p_device, &info);
#endif
			}

			void kotek_render_helper_debug::setDebugTagToResource(
				VkDevice p_device, ktk::uint64_t casted_object_to_number,
				VkDebugReportObjectTypeEXT type, ktk::uint64_t name,
				const void* p_tag, ktk::size_t size_of_p_tag) const noexcept
			{
#ifdef KOTEK_DEBUG
				KOTEK_ASSERT(p_device, "must be a valid device (VkDevice)");

				VkDebugMarkerObjectTagInfoEXT info = {};

				info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
				info.objectType = type;
				info.object = casted_object_to_number;
				info.tagName = name;
				info.tagSize = size_of_p_tag;
				info.pTag = p_tag;

				this->m_p_callback_set_tag_object(p_device, &info);
#endif
			}

			void kotek_render_helper_debug::debugMarkerBegin(
				VkCommandBuffer p_buffer,
				const char* marker_name) const noexcept
			{
#ifdef KOTEK_DEBUG
				KOTEK_ASSERT(p_buffer, "invalid buffer (VkCommandBuffer)");
				KOTEK_ASSERT(marker_name, "you string pointer must be valid!");

				VkDebugMarkerMarkerInfoEXT info = {};

				info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
				info.pMarkerName = marker_name;

				this->m_p_callback_marker_begin(p_buffer, &info);
#endif
			}

			void kotek_render_helper_debug::debugMarkerInsert(
				VkCommandBuffer p_buffer,
				const char* marker_name) const noexcept
			{
#ifdef KOTEK_DEBUG
				KOTEK_ASSERT(p_buffer, "invalid buffer (VkCommandBuffer)");
				KOTEK_ASSERT(marker_name, "you string pointer must be valid!");

				VkDebugMarkerMarkerInfoEXT info = {};

				info.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
				info.pMarkerName = marker_name;

				this->m_p_callback_marker_insert(p_buffer, &info);
#endif
			}

			void kotek_render_helper_debug::debugMarkerEnd(
				VkCommandBuffer p_buffer) const noexcept
			{
#ifdef KOTEK_DEBUG
				this->m_p_callback_marker_end(p_buffer);
#endif
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek