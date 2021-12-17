#pragma once

#include "../kotek.core.api/kotek_api.h"
#include "../kotek.core/kotek_std.h"
#include "kotek_render_device_properties.h"
#include "kotek_render_helper_device.h"
#include "kotek_render_instance_properties.h"

namespace Kotek
{
	namespace Core
	{
		class ktkProfiler;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			namespace helper
			{
				ktk::string translateVkColorSpaceToString(
					VkColorSpaceKHR color_space) noexcept;
				ktk::string translateVkFormatToString(VkFormat format) noexcept;
				ktk::string translateVkResultToString(VkResult result) noexcept;
			} // namespace helper

			class kotek_render_device : public Core::kotek_i_render_device
			{
			public:
				kotek_render_device(void);
				~kotek_render_device(void);

				void initialize(Core::ktkMainManager& main_manager) override;
				void shutdown(void) override;
				void resize(Core::kotek_i_render_swapchain* p_raw_swapchain,
					Core::kotek_i_renderer* p_raw_renderer,
					Core::kotek_i_render_resource_manager*
						p_raw_resource_manager,
					int width, int height) override;
				int getWidth(void) const noexcept override;
				int getHeight(void) const noexcept override;

				void GPUFlush(void) override;

				VmaAllocator getAllocator(void) const noexcept;

				ktk::uint32_t getFamilyQueueIndex_Graphics(void) const noexcept;

				ktk::uint32_t getFamilyQueueIndex_Present(void) const noexcept;

				ktk::uint32_t getFamilyQueueIndex_Compute(void) const noexcept;

				VkDevice getDevice(void) const noexcept;

				VkPhysicalDevice getCurrentPhysicalDevice(void) const noexcept;

				VkSurfaceKHR getSurface(void) const noexcept;
				void setWidth(int width) noexcept;
				void setHeight(int height) noexcept;

				bool isMemoryTypeFromProperties(
					const VkPhysicalDeviceMemoryProperties& memory_properties,
					ktk::uint32_t type_bits, VkFlags mask_requirements,
					ktk::uint32_t* p_type_index) noexcept;

				const VkPhysicalDeviceProperties&
				getCurrentPhysicalDeviceProperties(void) const noexcept;
				const VkPhysicalDeviceProperties2&
				getCurrentPhysicalDeviceProperties2(void) const noexcept;
				const VkPhysicalDeviceMemoryProperties&
				getCurrentPhysicalDeviceMemoryProperties(void) const noexcept;

				VkSurfaceFormatKHR getCurrentPhysicalDeviceSurfaceFormat(
					void) const noexcept;

				VkQueue getQueue_Graphics(void) const noexcept;
				VkQueue getQueue_Compute(void) const noexcept;
				VkQueue getQueue_Present(void) const noexcept;
				const VkInstance getInstance(void) const noexcept;
				const kotek_render_helper_device& getHelper(
					void) const noexcept;

			private:
				void initializeAllocator(VkDevice p_device,
					VkPhysicalDevice p_physical_device,
					VkInstance p_instance) noexcept;
				void destroyAllocator(void) noexcept;
				void initializeInstance(void) noexcept;

				// This initialized both and physical and non physical just all
				void initializeDevice(
					Core::ktkMainManager& main_manager) noexcept;

				void initializeIndeciesOfQueueFamilies(
					ktk::uint32_t queue_count,
					const ktk::vector<VkQueueFamilyProperties>&
						queue_props) noexcept;

				// This enumerates and chooses the physical device, method in
				// initializeDevice
				void initializePhysicalDevice(void) noexcept;

				void initializeHelper(void) noexcept;

				// TODO: try to add feature for changing videocard from user
				// menu GPU only
				// TODO: try to add console command for switching GPU by
				// indexing
				// TODO: refactor these methods
				bool chooseDiscretePhysicalDevice(
					const ktk::vector<VkPhysicalDevice>& devices) noexcept;
				bool chooseIntegratePhysicalDevice(
					const ktk::vector<VkPhysicalDevice>& devices) noexcept;

				void initializeQueues(void) noexcept;

				kotek_render_instance_properties createInstanceProperties(
					void) noexcept;
				kotek_render_device_properties createDeviceProperties(
					void) noexcept;

				bool checkExtensionFP16(
					kotek_render_device_properties* p_prop) noexcept;

				void createSurface(Core::ktkMainManager& main_manager) noexcept;

				ktk::uint32_t getApiVersion(void) const noexcept;

				/// <summary>
				/// Prints your api version by formatted string where pattern is
				/// "Some text for describing this message but {}.{}.{}.{}
				/// brackets are my formatted version" To understand how to
				/// handle for formatting api version in Vulkan use
				/// specification
				/// https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#extendingvulkan-coreversions-versionnumbers
				/// </summary>
				/// <param name="pattern">your format string</param>
				/// <param name="api_version">your api version for
				/// formatting</param> <returns></returns>
				void printApiVersion(const ktk::string& pattern,
					ktk::uint32_t api_version) const noexcept;

				void printSurfaceFormats(
					const ktk::vector<VkSurfaceFormatKHR>& formats)
					const noexcept;

				void printInformationAboutPhysicalDevice(
					const VkPhysicalDeviceProperties& props) const noexcept;

			private:
				bool m_is_use_fp16;
				bool m_is_use_validation_layer;
				int m_width;
				int m_height;
				ktk::uint32_t m_queue_index_present;
				ktk::uint32_t m_queue_index_graphics;
				ktk::uint32_t m_queue_index_compute;

				VkInstance m_p_instance;
				VkDevice m_p_device;
				VmaAllocator m_p_allocator;
				VkSurfaceKHR m_p_surface;

				ktk::vector<VkPhysicalDevice> m_physical_devices;

				VkPhysicalDevice m_p_current_physical_device;
				VkPhysicalDeviceMemoryProperties
					m_current_physical_device_memory_properties;
				VkPhysicalDeviceProperties m_current_physical_device_properties;
				VkPhysicalDeviceProperties2
					m_current_physical_device_properties2;
				VkPhysicalDeviceSubgroupProperties
					m_current_physical_device_subgroup_properties;

				VkQueue m_p_queue_present;
				VkQueue m_p_queue_graphics;
				VkQueue m_p_queue_compute;

				VkDebugReportCallbackEXT m_debug_report_callback_instance;

				Core::ktkProfiler* m_p_profiler;

				kotek_render_helper_device m_helper;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

#ifdef KOTEK_DEBUG

	#define KOTEK_DEBUG_VK_SET_OBJECT_NAME(your_device_class_pointer,       \
		object_type, p_resource, legacy_string_name)                        \
		your_device_class_pointer->getHelper()                              \
			.getDebug()                                                     \
			.setDebugNameToResource(your_device_class_pointer->getDevice(), \
				object_type, p_resource, legacy_string_name);

	#define KOTEK_DEBUG_VK_BEGIN_MARKER(                                    \
		your_device_class_pointer, p_vk_command_buffer, legacy_string_name) \
		your_device_class_pointer->getHelper().getDebug().debugMarkerBegin( \
			p_vk_command_buffer, legacy_string_name);

	#define KOTEK_DEBUG_VK_INSERT_MARKER(                                    \
		your_device_class_pointer, p_vk_command_buffer, legacy_string_name)  \
		your_device_class_pointer->getHelper().getDebug().debugMarkerInsert( \
			p_vk_command_buffer, legacy_string_name);

	#define KOTEK_DEBUG_VK_END_MARKER(                                    \
		your_device_class_pointer, p_vk_command_buffer)                   \
		your_device_class_pointer->getHelper().getDebug().debugMarkerEnd( \
			p_vk_command_buffer);

	#define KOTEK_DEBUG_VK_SET_TAG(your_device_class_pointer,                  \
		casted_object_to_uint64_t, debug_report_object_type_ext_value,         \
		numeric_name, p_data, size_of_your_p_data)                             \
		your_device_class_pointer->getHelper()                                 \
			.getDebug()                                                        \
			.setDebugTagToResource(your_device_class_pointer->getDevice(),     \
				casted_object_to_uint64_t, debug_report_object_type_ext_value, \
				numeric_name, p_data, size_of_your_p_data);

#else

	#define KOTEK_DEBUG_VK_SET_OBJECT_NAME(your_device_class_pointer, \
		object_type, p_resource, legacy_string_name)

	#define KOTEK_DEBUG_VK_BEGIN_MARKER( \
		your_device_class_pointer, p_vk_command_buffer, legacy_string_name)

	#define KOTEK_DEBUG_VK_INSERT_MARKER( \
		your_device_class_pointer, p_vk_command_buffer, legacy_string_name)

	#define KOTEK_DEBUG_VK_END_MARKER( \
		your_device_class_pointer, p_vk_command_buffer)

	#define KOTEK_DEBUG_VK_SET_TAG(your_device_class_pointer,          \
		casted_object_to_uint64_t, debug_report_object_type_ext_value, \
		numeric_name, p_data, size_of_your_p_data)

#endif