#pragma once

#include "kotek_render_device_properties.h"
#include "kotek_render_helper_device.h"
#include "kotek_render_instance_properties.h"
#include "vk_enum_string_helper.h"

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
                ktk::cstring TranslateVkColorSpaceToString(
					VkColorSpaceKHR color_space) noexcept;
                ktk::cstring TranslateVkFormatToString(
                    VkFormat format) noexcept;
                ktk::cstring TranslateVkResultToString(
                    VkResult result) noexcept;
				ktk::uint32_t TranslateEnumVersionToInstanceVersion(
					Core::eEngineSupportedVulkanVersion version) noexcept;
			} // namespace helper

			class ktkRenderDevice : public Core::ktkIRenderDevice
			{
			public:
				ktkRenderDevice(Core::eEngineSupportedVulkanVersion version);
				~ktkRenderDevice(void);

				void Initialize(Core::ktkMainManager* main_manager) override;
				void Shutdown(void) override;
				void Resize(Core::ktkIRenderSwapchain* p_raw_swapchain,
					Core::kotek_i_renderer* p_raw_renderer,
					Core::ktkIRenderResourceManager* p_raw_resource_manager,
					int width, int height) override;
				int GetWidth(void) const noexcept override;
				int GetHeight(void) const noexcept override;

				void GPUFlush(void) override;

				VmaAllocator GetAllocator(void) const noexcept;

				ktk::uint32_t GetFamilyQueueIndex_Graphics(void) const noexcept;

				ktk::uint32_t GetFamilyQueueIndex_Present(void) const noexcept;

				ktk::uint32_t GetFamilyQueueIndex_Compute(void) const noexcept;

				VkDevice GetDevice(void) const noexcept;

				VkPhysicalDevice GetCurrentPhysicalDevice(void) const noexcept;

				VkSurfaceKHR GetSurface(void) const noexcept;
				void SetWidth(int width) noexcept;
				void SetHeight(int height) noexcept;

				bool IsMemoryTypeFromProperties(
					const VkPhysicalDeviceMemoryProperties& memory_properties,
					ktk::uint32_t type_bits, VkFlags mask_requirements,
					ktk::uint32_t* p_type_index) noexcept;

				const VkPhysicalDeviceProperties&
				GetCurrentPhysicalDeviceProperties(void) const noexcept;

				const VkPhysicalDeviceProperties2&
				GetCurrentPhysicalDeviceProperties2(void) const noexcept;

				const VkPhysicalDeviceMemoryProperties&
				GetCurrentPhysicalDeviceMemoryProperties(void) const noexcept;

				VkSurfaceFormatKHR GetCurrentPhysicalDeviceSurfaceFormat(
					void) const noexcept;

				VkQueue GetQueue_Graphics(void) const noexcept;
				VkQueue GetQueue_Compute(void) const noexcept;
				VkQueue GetQueue_Present(void) const noexcept;
				const VkInstance GetInstance(void) const noexcept;
				const kotek_render_helper_device& GetHelper(
					void) const noexcept;

			private:
				void InitializeAllocator(VkDevice p_device,
					VkPhysicalDevice p_physical_device,
					VkInstance p_instance) noexcept;
				void DestroyAllocator(void) noexcept;
				void InitializeInstance() noexcept;

				// This initialized both and physical and non physical just all
				void InitializeDevice(
					Core::ktkMainManager* main_manager) noexcept;

				void InitializeIndeciesOfQueueFamilies(
					ktk::uint32_t queue_count,
					const ktk::vector<VkQueueFamilyProperties>&
						queue_props) noexcept;

				// This enumerates and chooses the physical device, method in
				// initializeDevice
				void InitializePhysicalDevice(void) noexcept;

				void InitializeHelper(void) noexcept;

				// TODO: try to add feature for changing videocard from user
				// menu GPU only
				// TODO: try to add console command for switching GPU by
				// indexing
				// TODO: refactor these methods
				bool ChooseDiscretePhysicalDevice(
					const ktk::vector<VkPhysicalDevice>& devices) noexcept;

				bool ChooseIntegratePhysicalDevice(
					const ktk::vector<VkPhysicalDevice>& devices) noexcept;

				void InitializeQueues(void) noexcept;

				kotek_render_instance_properties CreateInstanceProperties(
					void) noexcept;

				ktkRenderDeviceProperties CreateDeviceProperties(void) noexcept;

				bool CheckExtensionFP16(
					ktkRenderDeviceProperties* p_prop) noexcept;

				void CreateSurface(Core::ktkMainManager* main_manager) noexcept;

				ktk::uint32_t GetApiVersion(void) const noexcept;

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
                void PrintApiVersion(const ktk::cstring& pattern,
					ktk::uint32_t api_version) const noexcept;

				void PrintSurfaceFormats(
					const ktk::vector<VkSurfaceFormatKHR>& formats)
					const noexcept;

				void PrintInformationAboutPhysicalDevice(
					const VkPhysicalDeviceProperties& props) const noexcept;

			private:
				bool m_is_use_fp16;
				bool m_is_use_validation_layer;
				int m_width;
				int m_height;
				ktk::uint32_t m_queue_index_present;
				ktk::uint32_t m_queue_index_graphics;
				ktk::uint32_t m_queue_index_compute;

				Core::eEngineSupportedVulkanVersion m_current_version;

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
				kotek_render_helper_device m_helper;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

// TODO: remove because of tracy
#ifdef KOTEK_DEBUG

	#define KOTEK_DEBUG_VK_SET_OBJECT_NAME(your_device_class_pointer,       \
		object_type, p_resource, legacy_string_name)                        \
		your_device_class_pointer->GetHelper()                              \
			.getDebug()                                                     \
			.setDebugNameToResource(your_device_class_pointer->GetDevice(), \
				object_type, p_resource, legacy_string_name);

	#define KOTEK_DEBUG_VK_BEGIN_MARKER(                                    \
		your_device_class_pointer, p_vk_command_buffer, legacy_string_name) \
		your_device_class_pointer->GetHelper().getDebug().debugMarkerBegin( \
			p_vk_command_buffer, legacy_string_name);

	#define KOTEK_DEBUG_VK_INSERT_MARKER(                                    \
		your_device_class_pointer, p_vk_command_buffer, legacy_string_name)  \
		your_device_class_pointer->GetHelper().getDebug().debugMarkerInsert( \
			p_vk_command_buffer, legacy_string_name);

	#define KOTEK_DEBUG_VK_END_MARKER(                                    \
		your_device_class_pointer, p_vk_command_buffer)                   \
		your_device_class_pointer->GetHelper().getDebug().debugMarkerEnd( \
			p_vk_command_buffer);

	#define KOTEK_DEBUG_VK_SET_TAG(your_device_class_pointer,                  \
		casted_object_to_uint64_t, debug_report_object_type_ext_value,         \
		numeric_name, p_data, size_of_your_p_data)                             \
		your_device_class_pointer->GetHelper()                                 \
			.getDebug()                                                        \
			.setDebugTagToResource(your_device_class_pointer->GetDevice(),     \
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
