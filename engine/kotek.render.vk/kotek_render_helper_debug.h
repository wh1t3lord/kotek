#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_helper_device;
		}
	} // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_helper_debug
			{
			public:
				kotek_render_helper_debug(kotek_render_helper_device* p_helper);
				~kotek_render_helper_debug(void);

				void initialize(VkDevice p_device, VkInstance p_instance);
				void shutdown(void);

				void setDebugNameToResource(VkDevice p_device,
					VkObjectType resource_type, void* p_resource,
					const char* debug_name) const noexcept;

				void setDebugTagToResource(VkDevice p_device,
					ktk::uint64_t casted_object_to_number,
					VkDebugReportObjectTypeEXT type, ktk::uint64_t name,
					const void* p_tag,
					ktk::size_t size_of_p_tag) const noexcept;

				void debugMarkerBegin(VkCommandBuffer p_buffer,
					const char* marker_name) const noexcept;

				void debugMarkerInsert(VkCommandBuffer p_buffer,
					const char* marker_name) const noexcept;

				void debugMarkerEnd(VkCommandBuffer p_buffer) const noexcept;

			private:
				kotek_render_helper_device* m_p_helper;
				PFN_vkSetDebugUtilsObjectNameEXT m_p_callback_set_debug_name;
				PFN_vkDebugMarkerSetObjectTagEXT m_p_callback_set_tag_object;
				PFN_vkCmdDebugMarkerBeginEXT m_p_callback_marker_begin;
				PFN_vkCmdDebugMarkerEndEXT m_p_callback_marker_end;
				PFN_vkCmdDebugMarkerInsertEXT m_p_callback_marker_insert;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek
