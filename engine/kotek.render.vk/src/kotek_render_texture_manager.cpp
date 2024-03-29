#include "../include/kotek_render_texture_manager.h"
#include "../include/kotek_render_device.h"
#include "../include/kotek_render_upload_heap.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			ktkRenderTextureManager::ktkRenderTextureManager(
                ktkRenderDevice* p_device, kotek_render_upload_heap* p_heap) :
				m_p_device(p_device),
				m_p_heap(p_heap)
			{
				KOTEK_ASSERT(
					this->m_p_device, "you can't pass an invalid device");
				KOTEK_ASSERT(this->m_p_heap, "you can't pass an invalid heap");
			}

			ktkRenderTextureManager::~ktkRenderTextureManager() {}

			void ktkRenderTextureManager::Initialize() {}

			void ktkRenderTextureManager::Shutdown() {}

			void ktkRenderTextureManager::UploadAll(void) noexcept
			{
				this->m_p_heap->flushAndFinish(this->m_p_device);
			}

			ktkRenderTexture ktkRenderTextureManager::CreateTexture(
                const ktk::cstring& texture_name,
				const ktkRenderTextureCreateInfoBase& info,
				eTextureType type) noexcept
			{
				ktkRenderTexture result;

				if (type == eTextureType::kTextureType_Unknown)
				{
					KOTEK_ASSERT(
						false, "it can't be unknown use enum correctly!");
					return result;
				}

				if (texture_name.empty())
				{
					KOTEK_ASSERT(false, "you can't pass an empty texture name");
					return result;
				}

                result.SetTextureName(
                    ktk::ustring(texture_name.begin(), texture_name.end()));
				result.SetCreateInfoImage(info.getImageCreateInfo());
				result.SetCreateInfoSampler(info.getSamplerCreateInfo());
				result.SetTextureType(type);

				this->AllocateTexture(this->m_p_device->GetAllocator(), result);
				this->ValidateTexture(result);

				return result;
			}

            ktkRenderGraphTexture ktkRenderTextureManager::CreateTexture(
                const ktkRenderGraphResourceInfo<ktkRenderTextureInfo>&
                    info) noexcept
			{
                ktkRenderGraphTexture result(
                    this->CreateTexture(reinterpret_cast<const char*>(
                                            info.GetResourceName().c_str()),
                        info.GetInfo().GetCreateInfo(),
                        info.GetInfo().GetTypeTexture()));

				result.SetInfo(info);
				result.SetRenderPassName(info.GetRenderPassName());

				return result;
			}

			// TODO: refactor this
			void ktkRenderTextureManager::AllocateTexture(
                VmaAllocator p_allocator, ktkRenderTexture& texture) noexcept
			{
				KOTEK_ASSERT(p_allocator,
					"you can't pass an invalid vmaAllocator instance");

				VmaAllocation p_alloc = nullptr;
				VkImage p_image = nullptr;
				VkImageView p_image_view = nullptr;
				VkSampler p_sampler = nullptr;

                const auto& texture_name = texture.GetTextureName();

				VmaAllocationCreateInfo info = {};
				info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
				info.flags = VMA_ALLOCATION_CREATE_USER_DATA_COPY_STRING_BIT;
                info.pUserData = const_cast<char*>(
                    reinterpret_cast<const char*>(texture_name.c_str()));

				VmaAllocationInfo info_gpu = {};

				VkResult status =
					vmaCreateImage(p_allocator, &texture.GetCreateInfoImage(),
						&info, &p_image, &p_alloc, &info_gpu);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vmaCreateImage, see status");

				VkImageViewCreateInfo info_view = {};

				VkImageViewType view_type =
					VkImageViewType::VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				VkImageType image_type = texture.GetCreateInfoImage().imageType;

				switch (texture.GetTextureType())
				{
				case eTextureType::kTextureType_Single:
				{
					view_type = this->DetectTypeByTextureFormat(image_type);
					break;
				}
				case eTextureType::kTextureType_Array:
				{
					view_type =
						this->DetectTypeArrayByTextureFormat(image_type);
					break;
				}
				case eTextureType::kTextureType_Cubemap_Single:
				{
					view_type =
						this->DetectTypeCubemapByTextureFormat(image_type);
					break;
				}
				case eTextureType::kTextureType_Cubemap_Array:
				{
					view_type =
						this->DetectTypeCubemapArrayByTextureFormat(image_type);
					break;
				}
				default:
				{
					KOTEK_ASSERT(false,
						"can't understand your texture what do you want from "
						"system. See commentary about e_texture_type_t enum");
				}
				}

				info_view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				info_view.image = p_image;
				info_view.format = texture.GetCreateInfoImage().format;
				info_view.viewType = view_type;
				info_view.subresourceRange.aspectMask =
					VK_IMAGE_ASPECT_COLOR_BIT;
				info_view.subresourceRange.levelCount = 1;
				info_view.subresourceRange.layerCount = 1;

				status = vkCreateImageView(this->m_p_device->GetDevice(),
					&info_view, nullptr, &p_image_view);

				KOTEK_ASSERT(
					status == false, "failed to vkCreateImageView, see status");

				status = vkCreateSampler(this->m_p_device->GetDevice(),
					&texture.GetCreateInfoSampler(), nullptr, &p_sampler);

				KOTEK_ASSERT(
					status == false, "failed to vkCreateImageView, see status");

				texture.SetAllocation(p_alloc);
				texture.SetImageHandle(p_image);
				texture.SetImageViewHandle(p_image_view);
				texture.SetImageSamplerHandle(p_sampler);

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("allocated texture [{}] for {:.3f} Mbs",
                    reinterpret_cast<const char*>(
                        texture.GetTextureName().c_str()),
					static_cast<float>(static_cast<float>(info_gpu.size) /
						static_cast<float>(
							ktk::kMemoryConvertValueDenominator_Megabytes)));

				this->m_p_device->GetHelper().getDebug().setDebugNameToResource(
					this->m_p_device->GetDevice(),
                    VkObjectType::VK_OBJECT_TYPE_IMAGE, p_image,
                    reinterpret_cast<const char*>(
                        texture.GetTextureName().c_str()));

				this->m_p_device->GetHelper().getDebug().setDebugNameToResource(
					this->m_p_device->GetDevice(),
					VkObjectType::VK_OBJECT_TYPE_IMAGE_VIEW, p_image_view,
                    reinterpret_cast<const char*>(
                        texture.GetTextureName().c_str()));
#endif
			}

			bool ktkRenderTextureManager::ValidateTexture(
				const ktkRenderTexture& texture) noexcept
			{
				if (texture.GetAllocation() == nullptr)
				{
					KOTEK_ASSERT(false,
						"your vmaAllocation in texture class can't be nullptr");
					return false;
				}

				if (texture.GetImageHandle() == nullptr)
				{
					KOTEK_ASSERT(false,
						"your VkImage in texture class can't be nullptr");
					return false;
				}

				if (texture.GetImageViewHandle() == nullptr)
				{
					KOTEK_ASSERT(false,
						"your VkImageView in texture class can't be nullptr");
					return false;
				}

				if (texture.GetTextureName().empty())
				{
					KOTEK_ASSERT(false, "you must name your texture!");
					return false;
				}

				return true;
			}

			void ktkRenderTextureManager::DestroyTexture(
                VmaAllocator p_allocator, ktkRenderTexture& texture) noexcept
			{
				KOTEK_ASSERT(
					p_allocator, "you can't pass an invalid VmaAllocator");

#ifdef KOTEK_DEBUG
				// TODO: add allocation size what texture has
				KOTEK_MESSAGE("deallocating texture {}",
                    reinterpret_cast<const char*>(
                        texture.GetTextureName().c_str()));
#endif

				vkDestroyImageView(this->m_p_device->GetDevice(),
					texture.GetImageViewHandle(), nullptr);

				vkDestroySampler(this->m_p_device->GetDevice(),
					texture.GetImageSamplerHandle(), nullptr);

				vmaDestroyImage(p_allocator, texture.GetImageHandle(),
					texture.GetAllocation());
			}

			void ktkRenderTextureManager::DestroyTexture(
                VmaAllocator p_allocator, ktkRenderTexture* p_texture) noexcept
			{
				this->DestroyTexture(p_allocator, *p_texture);
			}

			void ktkRenderTextureManager::UploadTextureWithData(
				ktkRenderTexture* p_texture, void* p_data) noexcept
			{
				KOTEK_ASSERT(p_texture,
					"you can't pass an invalid kotek_render_texture "
					"pointer for coping to upload heap");

				this->m_p_heap->addPreBarrier(
					{.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
						.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
						.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
						.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
						.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
						.image = p_texture->GetImageHandle(),
						.subresourceRange = {
							.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.layerCount = 1}});

				this->m_p_heap->addPostBarrier(
					{.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
						.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
						.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
						.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
						.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
						.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
						.image = p_texture->GetImageHandle(),
						.subresourceRange = {
							.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel = 0,
							.levelCount = 1,
							.layerCount = 1}});

				ktk::size_t pixels_per_block =
					this->m_p_device->GetHelper().getPixelsPerBlockByFormat(
						p_texture->GetCreateInfoImage().format);

				// TODO: we must to ensure that upload_size contains valid size
				// for using in memcpy function
				ktk::size_t upload_size =
					((static_cast<ktk::size_t>(
						  p_texture->GetCreateInfoImage().extent.width) *
						 static_cast<ktk::size_t>(
							 p_texture->GetCreateInfoImage().extent.height)) *
						static_cast<ktk::size_t>(
							this->m_p_device->GetHelper()
								.getSizeInBytesByFormat(
									p_texture->GetCreateInfoImage().format))) /
					static_cast<ktk::size_t>(pixels_per_block);

				ktk::uint8_t* p_allocated =
					this->m_p_heap->subAllocate(upload_size);

				ktk::size_t offset = this->m_p_heap->getOffset(p_allocated);

				VkBufferImageCopy info_copy = {};

				info_copy.bufferOffset = offset;
				info_copy.imageSubresource.aspectMask =
					VK_IMAGE_ASPECT_COLOR_BIT;
				info_copy.imageSubresource.mipLevel =
					0; // TODO: create mipmap generation
				info_copy.imageSubresource.layerCount = 1;
				info_copy.imageSubresource.baseArrayLayer = 0;
				info_copy.imageExtent.width =
					p_texture->GetCreateInfoImage().extent.width;
				info_copy.imageExtent.height =
					p_texture->GetCreateInfoImage().extent.height;
				info_copy.imageExtent.depth =
					p_texture->GetCreateInfoImage().extent.depth;
                info_copy.imageOffset = VkOffset3D{0, 0, 0};

				ktk::memory::memcpy(p_allocated, p_data, upload_size);

				this->m_p_heap->addCopy(p_texture->GetImageHandle(), info_copy);
			}

            VkImageViewType ktkRenderTextureManager::DetectTypeByTextureFormat(
				VkImageType type_image) noexcept
			{
				switch (type_image)
				{
				case VkImageType::VK_IMAGE_TYPE_1D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D;
					break;
				}
				case VkImageType::VK_IMAGE_TYPE_2D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
					break;
				}
				case VkImageType::VK_IMAGE_TYPE_3D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_3D;
					break;
				}
				default:
				{
					KOTEK_ASSERT(false,
						"can't detect VkImageType from your "
						"VkImageCreationInfo "
						"recreate and specify correctly.");

					return VkImageViewType::VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				}
				}
			}

			VkImageViewType
			ktkRenderTextureManager::DetectTypeArrayByTextureFormat(
				VkImageType type_image) noexcept
			{
				switch (type_image)
				{
				case VkImageType::VK_IMAGE_TYPE_1D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D_ARRAY;
					break;
				}
				case VkImageType::VK_IMAGE_TYPE_2D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D_ARRAY;
					break;
				}
				default:
				{
					KOTEK_ASSERT(false,
						"can't detect VkImageType from your "
						"VkImageCreationInfo "
						"recreate and specify correctly.");

					return VkImageViewType::VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				}
				}
			}

			VkImageViewType
			ktkRenderTextureManager::DetectTypeCubemapByTextureFormat(
				VkImageType type_image) noexcept
			{
				switch (type_image)
				{
				case VkImageType::VK_IMAGE_TYPE_2D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_CUBE;
					break;
				}
				default:
				{
					KOTEK_ASSERT(false,
						"can't detect VkImageType from your "
						"VkImageCreationInfo "
						"recreate and specify correctly.");

					return VkImageViewType::VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				}
				}
			}

			VkImageViewType
			ktkRenderTextureManager::DetectTypeCubemapArrayByTextureFormat(
				VkImageType type_image) noexcept
			{
				switch (type_image)
				{
				case VkImageType::VK_IMAGE_TYPE_2D:
				{
					return VkImageViewType::VK_IMAGE_VIEW_TYPE_CUBE_ARRAY;
					break;
				}
				default:
				{
					KOTEK_ASSERT(false,
						"can't detect VkImageType from your "
						"VkImageCreationInfo "
						"recreate and specify correctly.");

					return VkImageViewType::VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				}
				}
			}

			bool ktkRenderGraphStorageOutput::Empty(void) const noexcept
			{
				return this->m_output_buffers.empty() &&
					this->m_output_images.empty();
			}

			namespace helper
			{
                ktk::cstring TranslateRenderGraphBuilderTypeToString(
					eRenderGraphBuilderType type) noexcept
				{
					switch (type)
					{
					case eRenderGraphBuilderType::
						kRenderBuilderFor_Forward_Only:
					{
						return "render_graph_builder_type_forward_only";
					}
					case eRenderGraphBuilderType::
						kRenderBuilderFor_Forward_With_Outputs:
					{
						return "render_graph_builder_type_forward_with_outputs";
					}
                    case eRenderGraphBuilderType::kRenderBuilderFor_Deferred:
					{
						return "render_graph_builder_type_deferred";
					}
                    case eRenderGraphBuilderType::kRenderBuilderFor_Undefined:
					{
						return "render_graph_builder_type_undefined (not "
							   "initialized)";
					}
					default:
					{
                        KOTEK_ASSERT(false, "can't translate this type: {}",
                            static_cast<ktk::enum_base_t>(type));

						return "render_graph_builder_type_INVALID";
					}
					}
				}

				VkGraphicsPipelineCreateInfo InitializeGraphicsPipeline(
					bool is_use_tesselation,
					const ktkRenderGraphPipelineInfo& info,
					const VkPipelineVertexInputStateCreateInfo* p_state_vertex,
					const VkPipelineColorBlendStateCreateInfo*
						p_state_color_blend,
					const VkPipelineDynamicStateCreateInfo* p_state_dynamic,
					VkPipelineLayout p_layout, VkRenderPass p_pass) noexcept
				{
					const VkPipelineTessellationStateCreateInfo*
						p_info_tesselation = nullptr;

					if (is_use_tesselation)
						p_info_tesselation =
							&info.GetPipelineTessellationState();

                    return InitializeGraphicsPipeline(p_state_vertex,
						&info.GetPipelineInputAssemblyState(),
						&info.GetPipelineViewportState(),
						&info.GetPipelineRasterizationState(),
						&info.GetPipelineMultisampleState(),
						&info.GetPipelineDepthStencilState(),
                        p_state_color_blend, p_state_dynamic, p_layout, p_pass,
						p_info_tesselation, info.GetSubpassIndex());
				}
			} // namespace helper

			ktkRenderGraphTexture::ktkRenderGraphTexture(
				const ktkRenderTexture& data) :
				ktkRenderTexture(data)
			{
			}

			ktkRenderGraphPipelineInfo::ktkRenderGraphPipelineInfo(
				const VkPipelineInputAssemblyStateCreateInfo& state_assembly,
				const VkPipelineRasterizationStateCreateInfo&
					state_rasterization,
				const VkPipelineViewportStateCreateInfo& state_viewport,
				const ktk::vector<VkPipelineColorBlendAttachmentState>&
					color_blend_attachments,
				const VkPipelineDepthStencilStateCreateInfo&
					state_depth_stencil,
				const ktk::vector<VkDynamicState>& dynamic_states,
				const VkPipelineMultisampleStateCreateInfo& state_multisample,
				const ktk::vector<VkVertexInputAttributeDescription>&
					vertex_attributes,
				const ktk::vector<VkVertexInputBindingDescription>&
					vertex_bindings,
				const VkPipelineTessellationStateCreateInfo& state_tessellation,
				ktk::uint32_t subpass_index) :
				m_subpass_index(subpass_index),
				m_vertex_attributes(vertex_attributes),
				m_vertex_descriptions(vertex_bindings),
				m_state_assembly(state_assembly),
				m_state_rasterization(state_rasterization),
				m_attachments_blend(color_blend_attachments),
				m_dynamic_states(dynamic_states),
				m_state_depth_stencil(state_depth_stencil),
				m_state_multisample(state_multisample),
				m_state_tessellation(state_tessellation),
				m_state_viewport(state_viewport)
			{
                /*
                                VkPipelineColorBlendStateCreateInfo info = {};

                                this->m_state_dynamic =
                   helper::InitializePipelineDynamicState(
                                    this->m_dynamic_states);

                                this->m_state_color_blend =
                                    helper::InitializePipelineColorBlendState(
                                        this->m_attachments_blend);

                                this->m_state_vertex =
                                    helper::InitializePipelineVertexInputState(
                                        this->m_vertex_descriptions,
                   this->m_vertex_attributes);
                */
			}

			ktkRenderGraphPipelineInfo::ktkRenderGraphPipelineInfo(void) {}

			ktkRenderGraphPipelineInfo::~ktkRenderGraphPipelineInfo(void) {}

			const VkPipelineInputAssemblyStateCreateInfo&
			ktkRenderGraphPipelineInfo::GetPipelineInputAssemblyState(
				void) const noexcept
			{
				return this->m_state_assembly;
			}

			const VkPipelineRasterizationStateCreateInfo&
			ktkRenderGraphPipelineInfo::GetPipelineRasterizationState(
				void) const noexcept
			{
				return this->m_state_rasterization;
			}

			const VkPipelineDepthStencilStateCreateInfo&
			ktkRenderGraphPipelineInfo::GetPipelineDepthStencilState(
				void) const noexcept
			{
				return this->m_state_depth_stencil;
			}

			const VkPipelineViewportStateCreateInfo&
			ktkRenderGraphPipelineInfo::GetPipelineViewportState(
				void) const noexcept
			{
				return this->m_state_viewport;
			}

			const VkPipelineMultisampleStateCreateInfo&
			ktkRenderGraphPipelineInfo::GetPipelineMultisampleState(
				void) const noexcept
			{
				return this->m_state_multisample;
			}

			const VkPipelineTessellationStateCreateInfo&
			ktkRenderGraphPipelineInfo::GetPipelineTessellationState(
				void) const noexcept
			{
				return this->m_state_tessellation;
			}

			ktk::uint32_t ktkRenderGraphPipelineInfo::GetSubpassIndex(
				void) const noexcept
			{
				return this->m_subpass_index;
			}

			const ktk::vector<VkVertexInputBindingDescription>&
			ktkRenderGraphPipelineInfo::GetVertexBindingDescriptions(
				void) const noexcept
			{
				return this->m_vertex_descriptions;
			}

			const ktk::vector<VkVertexInputAttributeDescription>&
			ktkRenderGraphPipelineInfo::GetVertexAttributes(void) const noexcept
			{
				return this->m_vertex_attributes;
			}

			const ktk::vector<VkDynamicState>&
			ktkRenderGraphPipelineInfo::GetDynamicStates(void) const noexcept
			{
				return this->m_dynamic_states;
			}

			const ktk::vector<VkPipelineColorBlendAttachmentState>&
			ktkRenderGraphPipelineInfo::GetColorBlendAttachments(
				void) const noexcept
			{
				return this->m_attachments_blend;
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
