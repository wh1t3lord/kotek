#include "kotek_render_resource_manager.h"
#include "../kotek.core/kotek_main_manager.h"
#include "kotek_render_device.h"
#include "kotek_render_swapchain.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			// TODO: make it dynamic, load from sys_info.json
			constexpr ktk::uint32_t _kDescriptorCount_CBV = 2000;
			constexpr ktk::uint32_t _kDescriptorCount_SRV = 8000;
			constexpr ktk::uint32_t _kDescriptorCount_UAV = 10;
			constexpr ktk::uint32_t _kDescriptorCount_Sampler = 20;

			/// Memory allocating sizes
			// Engine must execute scenes with only 64Mb video RAM
			// TODO: make it dynamic, load from sys_info.json

#pragma region Video Memory
			constexpr ktk::uint32_t _kVidMemoryFor_StaticGeometry =
				24 * ktk::kMemoryConvertValue_Megabytes;
			constexpr ktk::uint32_t _kVidMemoryFor_ConstantBuffers =
				8 * ktk::kMemoryConvertValue_Megabytes;
			constexpr ktk::uint32_t _kMemoryFor_UploadHeap =
				32 * ktk::kMemoryConvertValue_Megabytes;
#pragma endregion

#pragma region Computer RAM
			constexpr ktk::uint32_t _kCPUMemoryFor_StaticGeometry =
				32 * ktk::kMemoryConvertValue_Megabytes;
#pragma endregion

			ktkRenderResourceManager::ktkRenderResourceManager(
				ktkRenderDevice* p_device,
				Core::ktkMainManager* p_manager) :
				m_swapchain_image_count(0),
				m_p_render_pass_swapchain(nullptr), m_p_device(p_device),
				m_manager_texture(p_device, &this->m_upload_heap),
				m_manager_shader(p_manager)
			{
				KOTEK_ASSERT(this->m_p_device, "you passed an invalid device");

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("ctor");
#endif
			}

			ktkRenderResourceManager::~ktkRenderResourceManager()
			{
#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("~dtor");
#endif
			}

			void ktkRenderResourceManager::initialize(
				Core::ktkIRenderDevice* p_raw_device,
				Core::ktkIRenderSwapchain* p_raw_swapchain)
			{
				ktkRenderDevice* p_render_device =
					static_cast<ktkRenderDevice*>(p_raw_device);

				ktkRenderSwapchain* p_render_swapchain =
					static_cast<ktkRenderSwapchain*>(p_raw_swapchain);

				this->createSwapchainRTVs(p_render_device, p_render_swapchain);
				this->createStaticAllocators(p_render_device);

				this->m_manager_shader.initialize();
				this->m_manager_texture.initialize();

				KOTEK_MESSAGE("resource manager is initialized");
			}

			void ktkRenderResourceManager::shutdown(
				Core::ktkIRenderDevice* p_raw_device)
			{
				ktkRenderDevice* p_render_device =
					static_cast<ktkRenderDevice*>(p_raw_device);

				this->destroyStaticAllocators(p_render_device);
				this->destroySwapchainRTVs(p_render_device);

				this->m_manager_shader.shutdown();
				this->m_manager_texture.shutdown();

				KOTEK_MESSAGE("resource manager is shutdown");
			}

			void ktkRenderResourceManager::resize(
				ktkRenderDevice* p_render_device,
				ktkRenderSwapchain* p_render_swapchain)
			{
				this->destroySwapchainRTVs(p_render_device);
				this->createSwapchainRTVs(p_render_device, p_render_swapchain);
			}

			kotek_render_dynamic_buffer_ring*
			ktkRenderResourceManager::GetDynamicBufferRing(void) noexcept
			{
				return &this->m_dynamic_buffer_ring;
			}

			kotek_render_upload_heap* ktkRenderResourceManager::getUploadHeap(
				void) noexcept
			{
				return &this->m_upload_heap;
			}

			kotek_render_texture_manager*
			ktkRenderResourceManager::getTextureManager(void) noexcept
			{
				return &this->m_manager_texture;
			}

			kotek_render_resource_view_heap*
			ktkRenderResourceManager::GetCreatorHeap(void) noexcept
			{
				return &this->m_resource_view_heap;
			}

			kotek_render_shader_manager*
			ktkRenderResourceManager::getShaderManager(void) noexcept
			{
				return &this->m_manager_shader;
			}

			VkRenderPass ktkRenderResourceManager::getSwapchainRenderPass(
				void) const noexcept
			{
				return this->m_p_render_pass_swapchain;
			}

			const VkFramebuffer
			ktkRenderResourceManager::getSwapchainFrameBuffer(
				ktk::uint32_t acquired_swapchain_index) const noexcept
			{
				return this->m_swapchain_framebuffers.at(
					acquired_swapchain_index);
			}

			const VkDescriptorPool ktkRenderResourceManager::getDescriptorPool(
				void) const noexcept
			{
				return this->m_resource_view_heap.getDescriptorPool();
			}

			VkPipelineShaderStageCreateInfo
			ktkRenderResourceManager::buildShader(
				shader_type_t type, VkShaderModule p_module) noexcept
			{
				VkPipelineShaderStageCreateInfo result = {};

				if (p_module == nullptr)
				{
					KOTEK_ASSERT(false, "can't pass an invalid module pointer");
					return result;
				}

				result.sType =
					VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				result.pNext = nullptr;
				result.flags = 0;
				result.pSpecializationInfo = nullptr;
				result.pName = "main";
				result.module = p_module;

				switch (type)
				{
				case shader_type_t::kShaderType_Vertex:
				{
					result.stage = VK_SHADER_STAGE_VERTEX_BIT;
					break;
				}
				case shader_type_t::kShaderType_Pixel:
				{
					result.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
					break;
				}
				case shader_type_t::kShaderType_Mesh:
				{
					result.stage = VK_SHADER_STAGE_MESH_BIT_NV;
					break;
				}
				case shader_type_t::kShaderType_Geometry:
				{
					result.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
					break;
				}
				case shader_type_t::kShaderType_Compute:
				{
					result.stage = VK_SHADER_STAGE_COMPUTE_BIT;
					break;
				}
				case shader_type_t::kShaderType_Task:
				{
					result.stage = VK_SHADER_STAGE_TASK_BIT_NV;
					break;
				}
				case shader_type_t::kShaderType_TessellationControl:
				{
					result.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
					break;
				}
				case shader_type_t::kShaderType_TessellationEvaluation:
				{
					result.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
					break;
				}
				default:
				{
					KOTEK_ASSERT(false, "you must specify your stage");
					break;
				}
				}

				return result;
			}

			void ktkRenderResourceManager::uploadAllResourcesToGPU(
				void) noexcept
			{
				this->m_manager_texture.uploadAll();
			}

			VkImage ktkRenderResourceManager::GetSwapchainImage(
				ktk::uint32_t acquired_index) const noexcept
			{
				return this->m_swapchain_images.at(acquired_index);
			}

			void ktkRenderResourceManager::createStaticAllocators(
				ktkRenderDevice* p_render_device) noexcept
			{
				this->m_resource_view_heap.initialize(p_render_device,
					_kDescriptorCount_CBV, _kDescriptorCount_SRV,
					_kDescriptorCount_UAV, _kDescriptorCount_Sampler);

				this->m_dynamic_buffer_ring.initialize(p_render_device,
					_kSwapchainBackBuffers, _kVidMemoryFor_ConstantBuffers,
					KOTEK_TEXT("Uniforms"));

				// TODO: write more informative description string
				this->m_static_buffer_cpu_access.initialize(p_render_device,
					_kCPUMemoryFor_StaticGeometry, false,
					KOTEK_TEXT("Post processing geometry"));

				this->m_static_buffer_gpu_access_only.initialize(
					p_render_device, _kVidMemoryFor_StaticGeometry, true,
					KOTEK_TEXT("Static Geometry"));

				this->m_upload_heap.initialize(
					p_render_device, _kMemoryFor_UploadHeap);
			}

			void ktkRenderResourceManager::destroyStaticAllocators(
				ktkRenderDevice* p_render_device) noexcept
			{
				this->m_dynamic_buffer_ring.shutdown(p_render_device);
				this->m_resource_view_heap.shutdown(p_render_device);
				this->m_static_buffer_cpu_access.shutdown(p_render_device);
				this->m_static_buffer_gpu_access_only.shutdown(p_render_device);
				this->m_upload_heap.shutdown(p_render_device);
			}

			void ktkRenderResourceManager::createSwapchainRTVs(
				ktkRenderDevice* p_render_device,
				ktkRenderSwapchain* p_render_swapchain)
			{
				this->createSwapchainImages(
					p_render_device, p_render_swapchain);
				this->createSwapchainImagesView(
					p_render_device, p_render_swapchain);
				this->createSwapchainRenderPass(
					p_render_device, p_render_swapchain);
				this->createSwapchainFrameBuffers(p_render_device);
			}

			void ktkRenderResourceManager::destroySwapchainRTVs(
				ktkRenderDevice* p_render_device)
			{
				this->destroySwapchainFrameBuffers(p_render_device);
				this->destroySwapchainRenderPass(p_render_device);
				this->destroySwapchainImagesView(p_render_device);
			}

			void ktkRenderResourceManager::createDSV() {}

			void ktkRenderResourceManager::createSwapchainRenderPass(
				ktkRenderDevice* p_render_device,
				ktkRenderSwapchain* p_render_swapchain)
			{
				VkAttachmentDescription attachments[1];

				attachments[0].format =
					p_render_swapchain->getSwapchainFormat();
				attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
				attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
				attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
				attachments[0].stencilStoreOp =
					VK_ATTACHMENT_STORE_OP_DONT_CARE;
				attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
				attachments[0].flags = 0;

				VkAttachmentReference swapchain_color_reference;

				swapchain_color_reference.attachment = 0;
				swapchain_color_reference.layout =
					VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

				VkSubpassDescription subpass = {};

				subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				subpass.flags = 0;
				subpass.inputAttachmentCount = 0;
				subpass.pInputAttachments = nullptr;
				subpass.colorAttachmentCount = 1;
				subpass.pColorAttachments = &swapchain_color_reference;
				subpass.pResolveAttachments = nullptr;
				subpass.pDepthStencilAttachment = nullptr;
				subpass.preserveAttachmentCount = 0;
				subpass.pPreserveAttachments = nullptr;

				VkSubpassDependency dep = {};

				dep.dependencyFlags = 0;
				dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
					VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				dep.srcAccessMask = 0;
				dep.dstStageMask =
					VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				dep.srcStageMask =
					VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				dep.dstSubpass = 0;
				dep.srcSubpass = VK_SUBPASS_EXTERNAL;

				VkRenderPassCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
				info.pNext = nullptr;
				info.attachmentCount = 1;
				info.pAttachments = attachments;
				info.subpassCount = 1;
				info.pSubpasses = &subpass;
				info.dependencyCount = 1;
				info.pDependencies = &dep;

				VkResult status =
					vkCreateRenderPass(p_render_device->getDevice(), &info,
						nullptr, &this->m_p_render_pass_swapchain);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't create render pass. See status");
			}

			void ktkRenderResourceManager::createSwapchainImages(
				ktkRenderDevice* p_render_device,
				ktkRenderSwapchain* p_render_swapchain)
			{
				VkDevice p_device = p_render_device->getDevice();
				VkSwapchainKHR p_swapchain = p_render_swapchain->getSwapchain();

				KOTEK_ASSERT(p_device,
					"you must initialize device before using resource manager "
					"(VkDevice)");

				KOTEK_ASSERT(p_swapchain,
					"you must initialize swapchain before using "
					"resource manager (VkSwapchainKHR)");

				VkResult status = vkGetSwapchainImagesKHR(p_device, p_swapchain,
					&this->m_swapchain_image_count, nullptr);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't get count of swapchain images from "
					"vkGetSwapchainImagesKHR");

				KOTEK_ASSERT(
					this->m_swapchain_image_count == _kSwapchainBackBuffers,
					"must be equal, otherwise you need different model (by "
					"default "
					"it is triple buffering)");

				this->m_swapchain_images.resize(this->m_swapchain_image_count);

				status = vkGetSwapchainImagesKHR(p_device, p_swapchain,
					&this->m_swapchain_image_count,
					this->m_swapchain_images.data());

				KOTEK_ASSERT(status == VK_SUCCESS,
					"can't fill vector of VkImages from "
					"vkGetSwapchainImagesKHR");

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("swapchain images count: {}",
					this->m_swapchain_image_count);

				ktk::uint32_t index = 1;
				for (auto p_image : this->m_swapchain_images) 
				{
					ktk::string formatted = ktk::format("Swapchain Image #{}", index);

					this->m_p_device->getHelper()
						.getDebug()
						.setDebugNameToResource(this->m_p_device->getDevice(),
							VkObjectType::VK_OBJECT_TYPE_IMAGE, p_image, formatted.get_as_legacy().c_str());

					++index;
				}
#endif
			}

			void ktkRenderResourceManager::createSwapchainImagesView(
				ktkRenderDevice* p_render_device,
				ktkRenderSwapchain* p_render_swapchain)
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize device before use resource manager "
					"(VkDevice)");

				KOTEK_ASSERT(this->m_swapchain_images.empty() == false,
					"you must fill vector of VkImages");

				KOTEK_ASSERT(this->m_swapchain_image_count,
					"you didn't get a valid count of swapchain images");

				this->m_swapchain_images_view.resize(
					this->m_swapchain_image_count);

				VkResult status = VK_ERROR_UNKNOWN;

				for (ktk::uint32_t i = 0; i < this->m_swapchain_images.size();
					 ++i)
				{
					VkImageViewCreateInfo info = {};

					info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					info.pNext = nullptr;
					info.format = p_render_swapchain->getSwapchainFormat();
					info.components.r = VK_COMPONENT_SWIZZLE_R;
					info.components.g = VK_COMPONENT_SWIZZLE_G;
					info.components.b = VK_COMPONENT_SWIZZLE_B;
					info.components.a = VK_COMPONENT_SWIZZLE_A;
					info.subresourceRange.aspectMask =
						VK_IMAGE_ASPECT_COLOR_BIT;
					info.subresourceRange.baseMipLevel = 0;
					info.subresourceRange.levelCount = 1;
					info.subresourceRange.baseArrayLayer = 0;
					info.subresourceRange.layerCount = 1;
					info.viewType = VK_IMAGE_VIEW_TYPE_2D;
					info.flags = 0;
					info.image = this->m_swapchain_images.at(i);

					status = vkCreateImageView(p_device, &info, nullptr,
						&this->m_swapchain_images_view[i]);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't create image view. See status");
				}
			}

			void ktkRenderResourceManager::createSwapchainFrameBuffers(
				ktkRenderDevice* p_render_device)
			{
				this->m_swapchain_framebuffers.resize(
					this->m_swapchain_images_view.size());

				ktk::uint32_t width = p_render_device->getWidth();
				ktk::uint32_t height = p_render_device->getHeight();

				VkResult status = VK_ERROR_UNKNOWN;

				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize device before use resource manager");

				for (ktk::uint32_t i = 0;
					 i < this->m_swapchain_images_view.size(); ++i)
				{
					VkImageView attach[] = {this->m_swapchain_images_view[i]};

					VkFramebufferCreateInfo info = {};

					info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
					info.pNext = nullptr;
					info.renderPass = this->m_p_render_pass_swapchain;
					info.attachmentCount = 1;
					info.pAttachments = attach;
					info.width = width;
					info.height = height;
					info.layers = 1;

					status = vkCreateFramebuffer(p_device, &info, nullptr,
						&this->m_swapchain_framebuffers[i]);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"can't create frame buffer. See status");
				}
			}

			void ktkRenderResourceManager::destroySwapchainRenderPass(
				ktkRenderDevice* p_render_device)
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize device before use resource manager "
					"(VkDevice)");

				if (this->m_p_render_pass_swapchain)
				{
					vkDestroyRenderPass(
						p_device, this->m_p_render_pass_swapchain, nullptr);
					this->m_p_render_pass_swapchain = nullptr;
				}
			}

			void ktkRenderResourceManager::destroySwapchainImagesView(
				ktkRenderDevice* p_render_device)
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize device before using resource manager "
					"(VkDevice)");

				for (auto& p_image_view : this->m_swapchain_images_view)
				{
					vkDestroyImageView(p_device, p_image_view, nullptr);
				}

				this->m_swapchain_images_view.clear();
			}

			void ktkRenderResourceManager::destroySwapchainFrameBuffers(
				ktkRenderDevice* p_render_device)
			{
				VkDevice p_device = p_render_device->getDevice();

				KOTEK_ASSERT(p_device,
					"you must initialize device before using resource manager "
					"(VkDevice)");

				for (auto& p_frame_buffer : this->m_swapchain_framebuffers)
				{
					vkDestroyFramebuffer(p_device, p_frame_buffer, nullptr);
				}

				this->m_swapchain_framebuffers.clear();
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
