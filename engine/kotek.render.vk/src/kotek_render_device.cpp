#include "../include/kotek_render_device.h"
#include "../include/kotek_render_instance_properties.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			static VKAPI_ATTR VkBool32 VKAPI_CALL MyDebugReportCallback(
				VkDebugReportFlagsEXT flags,
				VkDebugReportObjectTypeEXT objectType, uint64_t object,
				size_t location, int32_t messageCode, const char* pLayerPrefix,
				const char* pMessage, void* pUserData)
			{
				if (messageCode &
						VkDebugReportFlagBitsEXT::
							VK_DEBUG_REPORT_INFORMATION_BIT_EXT ||
					messageCode &
						VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT)
				{
					return VK_FALSE;
				}

				KOTEK_MESSAGE("|||VALIDATION_MESSAGE||| "
							  "[object:{}][messageCode:{}][location:{}][{}][{}]"
							  "[{}][{}] {} \n\n\n",
					object, messageCode, location,
					ktk::cast::to_string(pLayerPrefix), flags, objectType,
					pUserData, ktk::cast::to_string(pMessage));

				return VK_FALSE;
			}

			VkValidationFeaturesEXT debug_validation_features_ext = {};
			VkValidationFeatureEnableEXT
				debug_validation_features_ext_requested[] = {
					VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
					VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
					VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT};

			VkPhysicalDeviceFloat16Int8FeaturesKHR features_fp16 = {};
			VkPhysicalDevice16BitStorageFeatures features_storage_16bit = {};

			ktkRenderDevice::ktkRenderDevice() :
				m_p_surface(nullptr), m_width(-1), m_height(-1),
				m_p_allocator(nullptr)
			{
			}

			ktkRenderDevice::~ktkRenderDevice() {}

			void ktkRenderDevice::Initialize(Core::ktkMainManager& main_manager)
			{
				this->m_p_profiler = main_manager.GetProfiler();

				KOTEK_CPU_PROFILE();

				this->InitializeInstance();
				this->InitializeDevice(main_manager);
				this->InitializeAllocator(this->m_p_device,
					this->m_p_current_physical_device, this->m_p_instance);
				this->InitializeHelper();
			}

			void ktkRenderDevice::Shutdown()
			{
				this->m_helper.shutdown();
				this->DestroyAllocator();

				if (this->m_p_surface)
				{
					vkDestroySurfaceKHR(
						this->m_p_instance, this->m_p_surface, nullptr);
				}

				if (this->m_p_device)
				{
					vkDestroyDevice(this->m_p_device, nullptr);
				}

#ifdef KOTEK_DEBUG
				PFN_vkDestroyDebugReportCallbackEXT p_destroy_callback =
					(PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(
						this->m_p_instance, "vkDestroyDebugReportCallbackEXT");

				if (p_destroy_callback)
				{
					p_destroy_callback(this->m_p_instance,
						this->m_debug_report_callback_instance, nullptr);
				}
#endif

				if (this->m_p_instance)
				{
					vkDestroyInstance(this->m_p_instance, nullptr);
				}
			}

			void ktkRenderDevice::Resize(
				Core::ktkIRenderSwapchain* p_raw_swapchain,
				Core::kotek_i_renderer* p_raw_renderer,
				Core::ktkIRenderResourceManager* p_raw_resource_manager,
				int width, int height)
			{
				this->m_width = width;
				this->m_height = height;

				if (width == 0 || height == 0)
					return;

				ktkRenderResourceManager* p_render_resource_manager =
					static_cast<ktkRenderResourceManager*>(
						p_raw_resource_manager);

				p_raw_swapchain->Resize(this, width, height);
				p_render_resource_manager->Resize(
					this, p_raw_swapchain);
				p_raw_renderer->Resize();
			}

			int ktkRenderDevice::GetWidth() const noexcept
			{
				return this->m_width;
			}

			int ktkRenderDevice::GetHeight() const noexcept
			{
				return this->m_height;
			}

			void ktkRenderDevice::GPUFlush()
			{
				vkDeviceWaitIdle(this->m_p_device);
			}

			VmaAllocator ktkRenderDevice::GetAllocator(void) const noexcept
			{
				return this->m_p_allocator;
			}

			ktk::uint32_t ktkRenderDevice::GetFamilyQueueIndex_Graphics(
				void) const noexcept
			{
				return this->m_queue_index_graphics;
			}

			ktk::uint32_t ktkRenderDevice::GetFamilyQueueIndex_Present(
				void) const noexcept
			{
				return this->m_queue_index_present;
			}

			ktk::uint32_t ktkRenderDevice::GetFamilyQueueIndex_Compute(
				void) const noexcept
			{
				return this->m_queue_index_compute;
			}

			VkDevice ktkRenderDevice::GetDevice(void) const noexcept
			{
				return this->m_p_device;
			}

			VkPhysicalDevice ktkRenderDevice::GetCurrentPhysicalDevice(
				void) const noexcept
			{
				return this->m_p_current_physical_device;
			}

			VkSurfaceKHR ktkRenderDevice::GetSurface(void) const noexcept
			{
				return this->m_p_surface;
			}

			void ktkRenderDevice::SetWidth(int width) noexcept
			{
				this->m_width = width;
			}

			void ktkRenderDevice::SetHeight(int height) noexcept
			{
				this->m_height = height;
			}

			bool ktkRenderDevice::IsMemoryTypeFromProperties(
				const VkPhysicalDeviceMemoryProperties& memory_properties,
				ktk::uint32_t type_bits, VkFlags mask_requirements,
				ktk::uint32_t* p_type_index) noexcept
			{
				for (ktk::uint32_t i = 0; i < memory_properties.memoryTypeCount;
					 ++i)
				{
					if ((type_bits & 1) == 1)
					{
						if ((memory_properties.memoryTypes[i].propertyFlags &
								mask_requirements) == mask_requirements)
						{
							*p_type_index = i;
							return true;
						}
					}
				}

				// No memory types are matched
				return false;
			}

			const VkPhysicalDeviceProperties&
			ktkRenderDevice::GetCurrentPhysicalDeviceProperties(
				void) const noexcept
			{
				return this->m_current_physical_device_properties;
			}

			const VkPhysicalDeviceProperties2&
			ktkRenderDevice::GetCurrentPhysicalDeviceProperties2(
				void) const noexcept
			{
				return this->m_current_physical_device_properties2;
			}

			const VkPhysicalDeviceMemoryProperties&
			ktkRenderDevice::GetCurrentPhysicalDeviceMemoryProperties(
				void) const noexcept
			{
				return this->m_current_physical_device_memory_properties;
			}

			// TODO: support hdr
			VkSurfaceFormatKHR
			ktkRenderDevice::GetCurrentPhysicalDeviceSurfaceFormat(
				void) const noexcept
			{
				KOTEK_ASSERT(this->m_p_current_physical_device,
					"you must initialize your physical device (too early "
					"calling)");

				KOTEK_ASSERT(this->m_p_surface,
					"you must initialize your surface (too early calling)");

				ktk::uint32_t surface_count = 0;
				auto status = vkGetPhysicalDeviceSurfaceFormatsKHR(
					this->m_p_current_physical_device, this->m_p_surface,
					&surface_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkGetPhysicalDeviceSurfaceFormatsKHR");

				ktk::vector<VkSurfaceFormatKHR> formats(surface_count);

				status = vkGetPhysicalDeviceSurfaceFormatsKHR(
					this->m_p_current_physical_device, this->m_p_surface,
					&surface_count, formats.data());

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkGetPhysicalDeviceSurfaceFormatsKHR (filling "
					"vector "
					"of VkSurfaceFormatKHR)");

				this->PrintSurfaceFormats(formats);

				return formats.front();
			}

			VkQueue ktkRenderDevice::GetQueue_Graphics(void) const noexcept
			{
				return this->m_p_queue_graphics;
			}

			VkQueue ktkRenderDevice::GetQueue_Compute(void) const noexcept
			{
				return this->m_p_queue_compute;
			}

			VkQueue ktkRenderDevice::GetQueue_Present(void) const noexcept
			{
				return this->m_p_queue_present;
			}

			const VkInstance ktkRenderDevice::GetInstance(void) const noexcept
			{
				return this->m_p_instance;
			}

			const kotek_render_helper_device& ktkRenderDevice::GetHelper(
				void) const noexcept
			{
				return this->m_helper;
			}

			void ktkRenderDevice::InitializeAllocator(VkDevice p_device,
				VkPhysicalDevice p_physical_device,
				VkInstance p_instance) noexcept
			{
				KOTEK_CPU_PROFILE();

				KOTEK_ASSERT(p_device, "you can't pass invalid VkDevice");
				KOTEK_ASSERT(p_physical_device,
					"you can't pass invalid VkPhysicalDevice");
				KOTEK_ASSERT(p_instance, "you can't pass invalid VkInstance");

				VmaAllocatorCreateInfo info = {};

				info.vulkanApiVersion = VK_API_VERSION_1_0;
				info.device = p_device;
				info.instance = p_instance;
				info.physicalDevice = p_physical_device;

				VkResult status =
					vmaCreateAllocator(&info, &this->m_p_allocator);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vmaCreateAllocator. See status");
			}

			void ktkRenderDevice::DestroyAllocator(void) noexcept
			{
				vmaDestroyAllocator(this->m_p_allocator);
			}

			void ktkRenderDevice::InitializeInstance() noexcept
			{
				KOTEK_CPU_PROFILE();

				constexpr ktk::uint32_t required_version = VK_API_VERSION_1_1;

				const ktk::uint32_t user_version = this->GetApiVersion();

				this->PrintApiVersion(
					"Required version of Vulkan INSTANCE: {}.{}.{}.{}",
					required_version);

				this->PrintApiVersion(
					"User version of Vulkan INSTANCE: {}.{}.{}.{}",
					user_version);

				KOTEK_ASSERT(required_version <= user_version,
					"This engine doesn't support your machine");

				VkApplicationInfo info = {};
				info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				info.pNext = nullptr;
				info.pApplicationName = "Kotek Engine Application";
				info.applicationVersion = 1;
				info.pEngineName = "Kotek Engine";
				info.engineVersion = 1;
				info.apiVersion = required_version;

				kotek_render_instance_properties props_instance =
					this->CreateInstanceProperties();

				VkInstanceCreateInfo info_instance = {};

				info_instance.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				info_instance.pNext = props_instance.getNext();
				info_instance.flags = 0;
				info_instance.pApplicationInfo = &info;
				info_instance.enabledExtensionCount =
					props_instance.getCountExtensionsName();
				info_instance.ppEnabledExtensionNames =
					props_instance.getDataExtensionsName();
				info_instance.enabledLayerCount =
					props_instance.getCountLayersName();
				info_instance.ppEnabledLayerNames =
					props_instance.getDataLayersName();

				VkResult status = vkCreateInstance(
					&info_instance, nullptr, &this->m_p_instance);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "failed to create VkInstance!");

#ifdef KOTEK_DEBUG
				VkDebugReportCallbackCreateInfoEXT info_debug_callback = {};

				info_debug_callback.sType =
					VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
				info_debug_callback.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |
					VK_DEBUG_REPORT_WARNING_BIT_EXT |
					VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
				info_debug_callback.pfnCallback = MyDebugReportCallback;

				PFN_vkCreateDebugReportCallbackEXT
					p_callback_debug_callback_creation = VK_NULL_HANDLE;

				p_callback_debug_callback_creation =
					reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(
						vkGetInstanceProcAddr(this->m_p_instance,
							"vkCreateDebugReportCallbackEXT"));

				status = p_callback_debug_callback_creation(this->m_p_instance,
					&info_debug_callback, nullptr,
					&this->m_debug_report_callback_instance);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't create debug report callback");
#endif
			}

			void ktkRenderDevice::InitializeDevice(
				Core::ktkMainManager& main_manager) noexcept
			{
				KOTEK_CPU_PROFILE();

				this->InitializePhysicalDevice();

				ktkRenderDeviceProperties props =
					this->CreateDeviceProperties();

				VkResult status = VK_SUCCESS;

				ktk::uint32_t queue_family_count = 0;

				vkGetPhysicalDeviceQueueFamilyProperties(
					this->m_p_current_physical_device, &queue_family_count,
					nullptr);

				KOTEK_ASSERT(queue_family_count >= 1,
					"failed to get the right value for queue_family_count by "
					"vkGetPhysicalDeviceQueueFamilyProperties");

				ktk::vector<VkQueueFamilyProperties> queue_props;

				queue_props.resize(queue_family_count);

				vkGetPhysicalDeviceQueueFamilyProperties(
					this->m_p_current_physical_device, &queue_family_count,
					queue_props.data());

				KOTEK_ASSERT(queue_family_count >= 1,
					"failed to fill data by "
					"vkGetPhysicalDeviceQueueFamilyProperties");

				vkGetPhysicalDeviceMemoryProperties(
					this->m_p_current_physical_device,
					&this->m_current_physical_device_memory_properties);

				vkGetPhysicalDeviceProperties(this->m_p_current_physical_device,
					&this->m_current_physical_device_properties);

				this->m_current_physical_device_subgroup_properties.sType =
					VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES;
				this->m_current_physical_device_subgroup_properties.pNext =
					nullptr;

				this->m_current_physical_device_properties2.sType =
					VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
				this->m_current_physical_device_properties2.pNext = nullptr;

				vkGetPhysicalDeviceProperties2(
					this->m_p_current_physical_device,
					&this->m_current_physical_device_properties2);

				this->CreateSurface(main_manager);

				this->InitializeIndeciesOfQueueFamilies(
					queue_family_count, queue_props);

				float queue_priorities[1] = {0.0f};

				VkDeviceQueueCreateInfo info_queue[2] = {};

				info_queue[0].sType =
					VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				info_queue[0].pNext = nullptr;
				info_queue[0].queueCount = 1;
				info_queue[0].pQueuePriorities = queue_priorities;
				info_queue[0].queueFamilyIndex = this->m_queue_index_graphics;

				info_queue[1].sType =
					VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				info_queue[1].pNext = nullptr;
				info_queue[1].queueCount = 1;
				info_queue[1].pQueuePriorities = queue_priorities;
				info_queue[1].queueFamilyIndex = this->m_queue_index_compute;

				VkPhysicalDeviceFeatures features_physical_device = {};

				features_physical_device.fillModeNonSolid = true;
				features_physical_device.pipelineStatisticsQuery = true;
				features_physical_device.fragmentStoresAndAtomics = true;
				features_physical_device.vertexPipelineStoresAndAtomics = true;
				features_physical_device.shaderImageGatherExtended = true;
				features_physical_device.wideLines = true;

				VkPhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR
					shader_subgroup_extended_type = {};

				shader_subgroup_extended_type.sType =
					VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SUBGROUP_EXTENDED_TYPES_FEATURES_KHR;
				shader_subgroup_extended_type.pNext = props.getNext();
				shader_subgroup_extended_type.shaderSubgroupExtendedTypes =
					VK_TRUE;

				VkPhysicalDeviceFeatures2 features_physical_device2 = {};

				features_physical_device2.sType =
					VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
				features_physical_device2.features = features_physical_device;
				features_physical_device2.pNext =
					&shader_subgroup_extended_type;

				VkDeviceCreateInfo info_device = {};

				info_device.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				info_device.pNext = &features_physical_device2;
				info_device.queueCreateInfoCount = 2;
				info_device.pQueueCreateInfos = info_queue;
				info_device.enabledExtensionCount =
					props.getCountExtensionsName();
				info_device.ppEnabledExtensionNames =
					info_device.enabledExtensionCount
					? props.getDataExtensionsName()
					: nullptr;
				info_device.pEnabledFeatures = nullptr;

				status = vkCreateDevice(this->m_p_current_physical_device,
					&info_device, nullptr, &this->m_p_device);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreateDevice see status code");

				this->InitializeQueues();
			}

			void ktkRenderDevice::InitializeIndeciesOfQueueFamilies(
				ktk::uint32_t queue_count,
				const ktk::vector<VkQueueFamilyProperties>&
					queue_props) noexcept
			{
				KOTEK_ASSERT(queue_count >= 1,
					"invalid count, get from "
					"vkGetPhysicalDeviceQueueFamilyProperties for "
					"obtain the real number of queues");

				KOTEK_ASSERT(
					!queue_props.empty(), "can't pass an empty vector");

				KOTEK_ASSERT(this->m_p_surface,
					"you must initialize surface before call this method");

				this->m_queue_index_compute = ktk::kMax_UINT32;
				this->m_queue_index_graphics = ktk::kMax_UINT32;
				this->m_queue_index_present = ktk::kMax_UINT32;

				for (ktk::uint32_t i = 0; i < queue_count; ++i)
				{
					if ((queue_props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) !=
						0)
					{
						if (this->m_queue_index_graphics == ktk::kMax_UINT32)
							this->m_queue_index_graphics = i;

						VkBool32 is_support_present;

						vkGetPhysicalDeviceSurfaceSupportKHR(
							this->m_p_current_physical_device, i,
							this->m_p_surface, &is_support_present);
						if (is_support_present == VK_TRUE)
						{
							this->m_queue_index_graphics = i;
							this->m_queue_index_present =
								this->m_queue_index_graphics;
							break;
						}
					}
				}

				if (this->m_queue_index_present == ktk::kMax_UINT32)
				{
					KOTEK_MESSAGE(
						"your system doesn't support present and graphics "
						"queue in "
						"one. Finding separeted present family index of queue");

					for (ktk::uint32_t i = 0; i < queue_count; ++i)
					{
						VkBool32 is_support_present;

						vkGetPhysicalDeviceSurfaceSupportKHR(
							this->m_p_current_physical_device, i,
							this->m_p_surface, &is_support_present);

						if (is_support_present == VK_TRUE)
						{
							this->m_queue_index_present = i;
							break;
						}
					}
				}

				for (ktk::uint32_t i = 0; i < queue_count; ++i)
				{
					if ((queue_props.at(i).queueFlags & VK_QUEUE_COMPUTE_BIT) !=
						0)
					{
						if (this->m_queue_index_compute == ktk::kMax_UINT32)
							this->m_queue_index_compute = i;

						if (i != this->m_queue_index_graphics)
						{
							this->m_queue_index_compute = i;
							break;
						}
					}
				}

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("your indecies family queues: graphics[{}] | "
							  "present[{}] | compute[{}]",
					this->m_queue_index_graphics, this->m_queue_index_present,
					this->m_queue_index_compute);
#endif
			}

			void ktkRenderDevice::InitializePhysicalDevice() noexcept
			{
				KOTEK_CPU_PROFILE();

				ktk::uint32_t gpu_count = 1;
				const ktk::uint32_t required_count = gpu_count;

				VkResult status = vkEnumeratePhysicalDevices(
					this->m_p_instance, &gpu_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkEnumeratePhysicalDevices");

				this->m_physical_devices.resize(gpu_count);

				status = vkEnumeratePhysicalDevices(this->m_p_instance,
					&gpu_count, this->m_physical_devices.data());

				KOTEK_ASSERT(
					status == VK_SUCCESS && gpu_count >= required_count,
					"failed to fill vector of physical devices or validate "
					"size of "
					"required count");

				bool is_picked_discrete_videocard =
					this->ChooseDiscretePhysicalDevice(
						this->m_physical_devices);

				bool is_picked_videocard = true;

				if (is_picked_discrete_videocard == false)
				{
					bool is_picked_integrate_videocard =
						this->ChooseIntegratePhysicalDevice(
							this->m_physical_devices);

					is_picked_videocard = is_picked_discrete_videocard ||
						is_picked_integrate_videocard;
				}

				KOTEK_ASSERT(is_picked_videocard,
					"engine can't obtain your videocard (GPU only) not "
					"discrete type not integrate type");
			}

			void ktkRenderDevice::InitializeHelper(void) noexcept
			{
				KOTEK_CPU_PROFILE();

				this->m_helper.initialize(this->m_p_device, this->m_p_instance);
			}

			bool ktkRenderDevice::ChooseDiscretePhysicalDevice(
				const ktk::vector<VkPhysicalDevice>& devices) noexcept
			{
				if (devices.empty())
				{
					KOTEK_ASSERT(false,
						"you can't pass an empty vector of VkPhysicalDevice");
					return false;
				}

				VkPhysicalDeviceProperties props = {};
				for (const auto& p_device : devices)
				{
					vkGetPhysicalDeviceProperties(p_device, &props);

					if (props.deviceType ==
						VkPhysicalDeviceType::
							VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
					{
						this->m_p_current_physical_device = p_device;

#ifdef KOTEK_DEBUG
						this->PrintInformationAboutPhysicalDevice(props);
#endif
						break;
					}

					if (props.deviceType ==
						VkPhysicalDeviceType::
							VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
					{
						this->m_p_current_physical_device = p_device;

#ifdef KOTEK_DEBUG
						this->PrintInformationAboutPhysicalDevice(props);
#endif
						break;
					}
				}

				return true;
			}

			bool ktkRenderDevice::ChooseIntegratePhysicalDevice(
				const ktk::vector<VkPhysicalDevice>& devices) noexcept
			{
				if (devices.empty())
				{
					KOTEK_ASSERT(false,
						"you can't pass an empty vector of VkPhysicalDevice");
					return false;
				}

				VkPhysicalDeviceProperties props = {};
				for (const auto& p_device : devices)
				{
					vkGetPhysicalDeviceProperties(p_device, &props);

					if (props.deviceType ==
						VkPhysicalDeviceType::
							VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
					{
						this->m_p_current_physical_device = p_device;

#ifdef KOTEK_DEBUG
						this->PrintInformationAboutPhysicalDevice(props);
#endif

						break;
					}

					if (props.deviceType ==
						VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU)
					{
						KOTEK_MESSAGE_WARNING(
							"YOU DONT HAVE A SUITABLE VIDEOCARD FOR RENDERING "
							"OPERATIONS, THAT MEANS ENGINE PICKED CPU!");

						this->m_p_current_physical_device = p_device;

#ifdef KOTEK_DEBUG
						this->PrintInformationAboutPhysicalDevice(props);
#endif

						break;
					}
				}

				return true;
			}

			void ktkRenderDevice::InitializeQueues() noexcept
			{
				KOTEK_ASSERT(this->m_p_device, "can't be invalid");

				vkGetDeviceQueue(this->m_p_device, this->m_queue_index_graphics,
					0, &this->m_p_queue_graphics);

				if (this->m_queue_index_graphics == this->m_queue_index_present)
				{
					this->m_p_queue_present = this->m_p_queue_graphics;
				}
				else
				{
					vkGetDeviceQueue(this->m_p_device,
						this->m_queue_index_present, 0,
						&this->m_p_queue_present);
				}

				if (this->m_queue_index_compute != ktk::kMax_UINT32)
				{
					vkGetDeviceQueue(this->m_p_device,
						this->m_queue_index_compute, 0,
						&this->m_p_queue_compute);
				}
			}

			kotek_render_instance_properties
			ktkRenderDevice::CreateInstanceProperties() noexcept
			{
				kotek_render_instance_properties result;

				bool status = result.initialize();

				if (status == false)
				{
					KOTEK_MESSAGE(
						"failed to initialize "
						"kotek_render_instance_properties's instance");
				}

				status = result.addLayerName("VK_LAYER_LUNARG_monitor");

				if (status == false)
				{
					KOTEK_MESSAGE(
						"failed to add layer name: VK_LAYER_LUNARG_monitor");
				}

				status = result.addExtensionName("VK_EXT_debug_utils");

				if (status == false)
				{
					KOTEK_MESSAGE(
						"failed to add extension name: VK_EXT_debug_utils");
				}

#ifdef KOTEK_PLATFORM_LINUX
				status =
					result.addExtensionName(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

				if (status == false)
				{
					KOTEK_MESSAGE("failed to add extension name: "
								  "VK_KHR_XCB_SURFACE_EXTENSION_NAME");
				}

#else
				status = result.addExtensionName(
					VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

				if (status == false)
				{
					KOTEK_MESSAGE("failed to add extension name: "
								  "VK_KHR_WIN32_SURFACE_EXTENSION_NAME");
				}
#endif

				status = result.addExtensionName(VK_KHR_SURFACE_EXTENSION_NAME);

				if (status == false)
				{
					KOTEK_MESSAGE("failed to add extension name: "
								  "VK_KHR_SURFACE_EXTENSION_NAME");
				}

#ifdef KOTEK_DEBUG
				bool is_cpu_validation_possible =
					result.addLayerName("VK_LAYER_KHRONOS_validation") &&
					result.addExtensionName(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

				if (is_cpu_validation_possible)
				{
					KOTEK_MESSAGE("enablig cpu and gpu validation");

					ktk::vector<const char*> requested_extensions_gpu = {
						VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME};

					for (const auto& it : requested_extensions_gpu)
					{
						if (result.addExtensionName(it) == false)
						{
							KOTEK_ASSERT(false, "missed extension: {}",
								ktk::cast::to_string(it));
						}
					}

					debug_validation_features_ext.sType =
						VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
					debug_validation_features_ext.pNext = result.getNext();
					debug_validation_features_ext
						.enabledValidationFeatureCount =
						sizeof(debug_validation_features_ext_requested) /
						sizeof(debug_validation_features_ext_requested[0]);
					debug_validation_features_ext.pEnabledValidationFeatures =
						debug_validation_features_ext_requested;

					result.setNext(
						static_cast<void*>(&debug_validation_features_ext));
				}
#endif

				return result;
			}

			ktkRenderDeviceProperties
			ktkRenderDevice::CreateDeviceProperties() noexcept
			{
				ktkRenderDeviceProperties result;

				result.initialize(this->m_p_current_physical_device);

				bool is_fp16_supported = this->CheckExtensionFP16(&result);

				if (is_fp16_supported)
				{
					KOTEK_MESSAGE("Vulkan Extension: FP16 is supported");
				}
				else
				{
					KOTEK_MESSAGE("Vulkan Extension: FP16 is not supported");
				}

				result.addExtensionName(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
				result.addExtensionName(
					VK_EXT_SCALAR_BLOCK_LAYOUT_EXTENSION_NAME);

				return result;
			}

			bool ktkRenderDevice::CheckExtensionFP16(
				ktkRenderDeviceProperties* p_prop) noexcept
			{
				KOTEK_ASSERT(p_prop, "you must pass a valid object");
				KOTEK_ASSERT(this->m_p_current_physical_device,
					"you must initialize physical device before using this "
					"method");

				ktk::vector<const char*> required_extension_names = {
					VK_KHR_SHADER_FLOAT16_INT8_EXTENSION_NAME};

				bool is_enabled_fp16 = true;
				for (auto& it : required_extension_names)
				{
					if (p_prop->addExtensionName(it) == false)
					{
						is_enabled_fp16 = false;
					}
				}

				if (is_enabled_fp16)
				{
					features_storage_16bit.sType =
						VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;

					VkPhysicalDeviceFeatures2 features = {};

					features.sType =
						VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
					features.pNext = &features_storage_16bit;

					vkGetPhysicalDeviceFeatures2(
						this->m_p_current_physical_device, &features);

					is_enabled_fp16 = is_enabled_fp16 &&
						features_storage_16bit.storageBuffer16BitAccess;

					features_fp16.sType =
						VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT16_INT8_FEATURES_KHR;
					features.pNext = &features_fp16;

					vkGetPhysicalDeviceFeatures2(
						this->m_p_current_physical_device, &features);

					is_enabled_fp16 =
						is_enabled_fp16 && features_fp16.shaderFloat16;

					if (is_enabled_fp16)
					{
						features_storage_16bit.pNext = p_prop->getNext();
						features_fp16.pNext = &features_storage_16bit;

						p_prop->setNext(&features_fp16);
					}
				}

				return is_enabled_fp16;
			}

			void ktkRenderDevice::CreateSurface(
				Core::ktkMainManager& main_manager) noexcept
			{
				this->m_p_surface = static_cast<VkSurfaceKHR>(
					main_manager.GetGameManager()->CreateSurface(
						static_cast<Core::ktkMainManager*>(&main_manager),
						this->m_p_instance, nullptr));
			}

			ktk::uint32_t ktkRenderDevice::GetApiVersion() const noexcept
			{
				ktk::uint32_t result = 0;

				VkResult status = vkEnumerateInstanceVersion(&result);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "can't get api version. See status");

				return result;
			}

			void ktkRenderDevice::PrintApiVersion(const ktk::string& pattern,
				ktk::uint32_t api_version) const noexcept
			{
				KOTEK_MESSAGE_STRING(pattern, ((api_version >> 29)),
					((api_version >> 22) & 0x7FU),
					((api_version >> 12) & 0x3FFU), (api_version & 0xFFFU));
			}

			void ktkRenderDevice::PrintSurfaceFormats(
				const ktk::vector<VkSurfaceFormatKHR>& formats) const noexcept
			{
				// TODO: translate enums to strings
#ifdef KOTEK_DEBUG
				for (const auto& format : formats)
				{
					KOTEK_MESSAGE("Surface format: {}",
						helper::TranslateVkFormatToString(format.format)
							.get_as_is());
					KOTEK_MESSAGE("Surface color space: {}",
						helper::TranslateVkColorSpaceToString(format.colorSpace)
							.get_as_is());
				}
#endif
			}

			void ktkRenderDevice::PrintInformationAboutPhysicalDevice(
				const VkPhysicalDeviceProperties& props) const noexcept
			{
				auto p_get_name_of_device_type =
					[](VkPhysicalDeviceType id) -> ktk::string
				{ return string_VkPhysicalDeviceType(id); };

				KOTEK_MESSAGE("VIDEO CARD INFO");

				KOTEK_MESSAGE(
					"name: {}", ktk::string(props.deviceName).get_as_is());

				this->PrintApiVersion(
					"videocard API VERSION DEVICE: {}.{}.{}.{}",
					props.apiVersion);

				KOTEK_MESSAGE("device type: {}",
					p_get_name_of_device_type(props.deviceType).get_as_is());

				KOTEK_MESSAGE("VIDEO CARD INFO");
			}

			namespace helper
			{
				ktk::string TranslateVkColorSpaceToString(
					VkColorSpaceKHR color_space) noexcept
				{
					return string_VkColorSpaceKHR(color_space);
				}

				ktk::string TranslateVkFormatToString(VkFormat format) noexcept
				{
					return string_VkFormat(format);
				}

				ktk::string TranslateVkResultToString(VkResult result) noexcept
				{
					return string_VkResult(result);
				}
			} // namespace helper

		} // namespace vk
	}     // namespace Render
} // namespace Kotek