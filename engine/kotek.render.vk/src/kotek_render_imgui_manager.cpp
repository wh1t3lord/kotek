#include "../include/kotek_render_imgui_manager.h"
#include "../include/kotek_render_device.h"
#include "../include/kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			struct VERTEX_CONSTANT_BUFFER
			{
				float mvp[4][4];
			};

			static void check_vk_result(VkResult status) noexcept
			{
				KOTEK_ASSERT(status == VK_SUCCESS,
					"A trouble in imgui library. See status");
			}

			kotek_render_imgui_manager::kotek_render_imgui_manager() :
				m_p_image(nullptr), m_p_image_view(nullptr),
				m_p_device_memory(nullptr), m_p_sampler(nullptr),
				m_p_pipeline(nullptr), m_current_descriptor_index(0)
			{
			}

			kotek_render_imgui_manager::~kotek_render_imgui_manager() {}

			void kotek_render_imgui_manager::initialize(
				Core::ktkMainManager& main_manager) noexcept
			{
				IMGUI_CHECKVERSION();
				sui::CreateContext();

				auto& io = sui::GetIO();

				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

				ImGui::StyleColorsDark();

				if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				{
					ImGuiStyle& style = sui::GetStyle();

					style.WindowRounding = 0.0f;
					style.Colors[ImGuiCol_WindowBg].w = 1.0f;
				}

				//	ImGui_ImplGlfw_InitForVulkan(g_manager_render_device->getGLFWwindow(),
				// true);

// 				ImGui_ImplGlfw_InitForVulkan(
// 					main_manager.GetWindow()->GetHandle(), true);

				//   this->createFontTexture(
				//       static_cast<ktkRenderDevice*>(main_manager.getRenderDevice()),
				//       static_cast<ktkRenderResourceManager*>(
				//           main_manager.getRenderResourceManager()));

				io.Fonts->TexID = this->m_p_image_view;

				KOTEK_MESSAGE("ImGui is created");
			}

			void kotek_render_imgui_manager::shutdown(
				Core::ktkIRenderDevice* p_raw_device) noexcept
			{
				ImGui_ImplVulkan_Shutdown();

				ImGui_ImplGlfw_Shutdown();

				ImGui::DestroyContext();

				ktkRenderDevice* p_render_device =
					static_cast<ktkRenderDevice*>(p_raw_device);

				// this->destroyFontTexture(p_render_device);
			}

			void kotek_render_imgui_manager::draw(VkCommandBuffer p_cmd,
				ktkRenderDevice* p_render_device,
				ktkRenderResourceManager*
					p_render_resource_manager) noexcept
			{
				return;

				KOTEK_ASSERT(p_cmd,
					"invaid VkCommandBuffer, you can't pass this in that "
					"way...");
				KOTEK_ASSERT(this->m_p_pipeline,
					"you must create pipeline before call the draw method!");

				sui::Render();

				auto* p_draw_data = sui::GetDrawData();

				char* p_verts = nullptr;
				char* p_indecies = nullptr;

				VkDescriptorBufferInfo info_vert;
				VkDescriptorBufferInfo info_index;

				bool status_alloc =
					p_render_resource_manager->GetDynamicBufferRing()
						->allocVertexBuffer(p_draw_data->TotalVtxCount,
							sizeof(ImDrawVert),
							reinterpret_cast<void**>(&p_verts), &info_vert);

				KOTEK_ASSERT(status_alloc, "can't allocate vertex buffer");

				status_alloc =
					p_render_resource_manager->GetDynamicBufferRing()
						->allocIndexBuffer(p_draw_data->TotalIdxCount,
							sizeof(ImDrawVert),
							reinterpret_cast<void**>(&p_indecies), &info_index);

				KOTEK_ASSERT(status_alloc, "can't allocate vertex buffer");

				ImDrawVert* p_dst_vrtx = reinterpret_cast<ImDrawVert*>(p_verts);
				ImDrawIdx* p_dst_index =
					reinterpret_cast<ImDrawIdx*>(p_indecies);

				for (int i = 0; i < p_draw_data->CmdListsCount; ++i)
				{
					const ImDrawList* p_list = p_draw_data->CmdLists[i];
					ktk::memory::memcpy(p_dst_vrtx, p_list->VtxBuffer.Data,
						p_list->VtxBuffer.Size * sizeof(ImDrawVert));
					ktk::memory::memcpy(p_dst_index, p_list->IdxBuffer.Data,
						p_list->IdxBuffer.Size * sizeof(ImDrawIdx));

					p_dst_vrtx += p_list->VtxBuffer.Size;
					p_dst_index += p_list->IdxBuffer.Size;
				}

				VkDescriptorBufferInfo info_buffer;
				VERTEX_CONSTANT_BUFFER* p_constant_buffer;

				status_alloc =
					p_render_resource_manager->GetDynamicBufferRing()
						->allocConstantBuffer(sizeof(VERTEX_CONSTANT_BUFFER),
							reinterpret_cast<void**>(&p_constant_buffer),
							&info_buffer);

				KOTEK_ASSERT(status_alloc, "can't allocate constant buffer");

				{
					float L = 0.0f;
					float R = ImGui::GetIO().DisplaySize.x;
					float B = ImGui::GetIO().DisplaySize.y;
					float T = 0.0f;
					float mvp[4][4] = {
						{2.0f / (R - L), 0.0f, 0.0f, 0.0f},
						{0.0f, 2.0f / (T - B), 0.0f, 0.0f},
						{0.0f, 0.0f, 0.5f, 0.0f},
						{(R + L) / (L - R), (T + B) / (B - T), 0.5f, 1.0f},
					};

					ktk::memory::memcpy(
						p_constant_buffer->mvp, mvp, sizeof(mvp));
				}

				VkViewport viewport;

				viewport.x = 0;
				viewport.y = ImGui::GetIO().DisplaySize.y;
				viewport.width = ImGui::GetIO().DisplaySize.x;
				viewport.height = -(ImGui::GetIO().DisplaySize.y);
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;

				vkCmdSetViewport(p_cmd, 0, 1, &viewport);

				vkCmdBindVertexBuffers(
					p_cmd, 0, 1, &info_vert.buffer, &info_vert.offset);
				vkCmdBindIndexBuffer(p_cmd, info_index.buffer,
					info_index.offset, VK_INDEX_TYPE_UINT16);
				vkCmdBindPipeline(
					p_cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, this->m_p_pipeline);

				ImTextureID p_tex_id = nullptr;

				int vtx_offset = 0;
				int idx_offset = 0;

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "invalid device (VkDevice)");

				ktk::uint32_t p_offset[1] = {info_buffer.offset};

				for (int i = 0; i < p_draw_data->CmdListsCount; ++i)
				{
					const ImDrawList* p_cmd_list = p_draw_data->CmdLists[i];

					for (int j = 0; j < p_cmd_list->CmdBuffer.Size; ++j)
					{
						const ImDrawCmd* p_im_cmd = &p_cmd_list->CmdBuffer[j];

						if (p_im_cmd->UserCallback)
						{
							p_im_cmd->UserCallback(p_cmd_list, p_im_cmd);
						}
						else
						{
							VkRect2D scissor;

							scissor.offset.x = (uint32_t)p_im_cmd->ClipRect.x;
							scissor.offset.y = (uint32_t)p_im_cmd->ClipRect.y;
							scissor.extent.width =
								(uint32_t)(p_im_cmd->ClipRect.z -
									p_im_cmd->ClipRect.x);
							scissor.extent.height =
								(uint32_t)(p_im_cmd->ClipRect.w -
									p_im_cmd->ClipRect.y);

							vkCmdSetScissor(p_cmd, 0, 1, &scissor);

							if (p_tex_id != p_im_cmd->TextureId)
							{
								p_tex_id = p_im_cmd->TextureId;

								VkDescriptorImageInfo info_image[1] = {};

								info_image[0].sampler = this->m_p_sampler;
								info_image[0].imageView =
									reinterpret_cast<VkImageView>(
										p_im_cmd->TextureId);
								info_image[0].imageLayout =
									VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

								VkWriteDescriptorSet writes[2];

								writes[0] = {};
								writes[0].sType =
									VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
								writes[0].pNext = NULL;
								writes[0].dstSet =
									this->m_descriptor_sets
										[this->m_current_descriptor_index];
								writes[0].descriptorCount = 1;
								writes[0].descriptorType =
									VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
								writes[0].pImageInfo = info_image;
								writes[0].dstArrayElement = 0;
								writes[0].dstBinding = 1;

								writes[1] = {};
								writes[1].sType =
									VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
								writes[1].pNext = NULL;
								writes[1].dstSet =
									this->m_descriptor_sets
										[this->m_current_descriptor_index];
								writes[1].descriptorCount = 1;
								writes[1].descriptorType =
									VK_DESCRIPTOR_TYPE_SAMPLER;
								writes[1].pImageInfo = info_image;
								writes[1].dstArrayElement = 0;
								writes[1].dstBinding = 2;

								vkUpdateDescriptorSets(
									p_device, 2, writes, 0, nullptr);
								vkCmdBindDescriptorSets(p_cmd,
									VK_PIPELINE_BIND_POINT_GRAPHICS,
									this->m_pipeline_layout, 0, 1,
									&this->m_descriptor_sets
										 [this->m_current_descriptor_index],
									1, p_offset);

								++this->m_current_descriptor_index;
								this->m_current_descriptor_index &= 127;
							}

							vkCmdDrawIndexed(p_cmd, p_im_cmd->ElemCount, 1,
								idx_offset, vtx_offset, 0);
						}

						idx_offset += p_im_cmd->ElemCount;
					}

					vtx_offset += p_cmd_list->VtxBuffer.Size;
				}
			}

			void kotek_render_imgui_manager::createFontTexture(
				ktkRenderDevice* p_render_device,
				ktkRenderResourceManager*
					p_render_resource_manager) noexcept
			{
				this->createImage(p_render_device);
				this->createImageMemoryAndBind(p_render_device);
				this->createImageView(p_render_device);
				this->writeDataToSuballocatedPartOfHeap(
					p_render_resource_manager);
				this->copyBufferToImage(p_render_resource_manager);
				this->flushHeap(p_render_resource_manager, p_render_device);
				this->createSampler(p_render_device);
				this->compileShaders(
					p_render_device, p_render_resource_manager);
				this->updatePipeline(
					p_render_resource_manager->getSwapchainRenderPass(),
					p_render_device);
			}

			void kotek_render_imgui_manager::destroyFontTexture(
				ktkRenderDevice* p_render_device) noexcept
			{
				KOTEK_ASSERT(this->m_shader_stages.empty() == false,
					"it is empty vector can't be!");

				this->m_shader_stages.clear();
				this->destroyImageView(p_render_device);
				this->destroyImage(p_render_device);
				this->destroyImageMemory(p_render_device);
				this->destroySampler(p_render_device);
				this->destroyDescriptorSetLayout(p_render_device);
				this->destroyPipelineLayout(p_render_device);
				this->destroyPipeline(p_render_device);
			}

			void kotek_render_imgui_manager::createImageView(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				KOTEK_ASSERT(this->m_p_image != nullptr,
					"must be a valid object (you didn't initialize VkImage)");

				VkImageViewCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				info.image = this->m_p_image;
				info.viewType = VK_IMAGE_VIEW_TYPE_2D;
				info.format = VK_FORMAT_R8G8B8A8_UNORM;
				info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				info.subresourceRange.levelCount = 1;
				info.subresourceRange.layerCount = 1;

				VkResult status = vkCreateImageView(
					p_device, &info, nullptr, &this->m_p_image_view);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed tovkCreateImageView. See status");

				/* TODO: DELETE THIS BECAUSE WE CAN ADD TO RENDER GRAPH
				  p_render_device->setDebugNameToResource(VK_OBJECT_TYPE_IMAGE_VIEW,
				                                          this->m_p_image_view,
				                                          "ImGui font texture
				  view");*/
			}

			void kotek_render_imgui_manager::destroyImageView(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkDestroyImageView(p_device, this->m_p_image_view, nullptr);
			}

			void kotek_render_imgui_manager::createImage(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				ktk::uint8_t* p_data = nullptr;
				int width, height;

				sui::GetIO().Fonts->GetTexDataAsRGBA32(
					&p_data, &width, &height);

				VkImageCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				info.imageType = VK_IMAGE_TYPE_2D;
				info.format = VK_FORMAT_R8G8B8A8_UNORM;
				info.extent.width = width;
				info.extent.height = height;
				info.extent.depth = 1;
				info.mipLevels = 1;
				info.arrayLayers = 1;
				info.samples = VK_SAMPLE_COUNT_1_BIT;
				info.tiling = VK_IMAGE_TILING_LINEAR;
				info.usage = VK_IMAGE_USAGE_SAMPLED_BIT |
					VK_IMAGE_USAGE_TRANSFER_DST_BIT;
				info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

				VkResult status =
					vkCreateImage(p_device, &info, nullptr, &this->m_p_image);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "faild to vkCreateImage. See status");

				/* TODO: DELETE THIS BECAUSE WE CAN ADD TO RENDER GRAPH
				#ifdef KOTEK_DEBUG
				  p_render_device->setDebugNameToResource(VK_OBJECT_TYPE_IMAGE,
				this->m_p_image, "ImGui font texture"); #endif*/
			}

			void kotek_render_imgui_manager::destroyImage(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkDestroyImage(p_device, this->m_p_image, nullptr);
			}

			void kotek_render_imgui_manager::createImageMemoryAndBind(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				KOTEK_ASSERT(this->m_p_image != nullptr,
					"must be a valid object (you didn't initialize VkImage)");

				VkMemoryRequirements memory_requirements;

				vkGetImageMemoryRequirements(
					p_device, this->m_p_image, &memory_requirements);

				VkMemoryAllocateInfo info_alloc = {};

				info_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				info_alloc.pNext = nullptr;
				info_alloc.allocationSize = memory_requirements.size;
				info_alloc.memoryTypeIndex = 0;

				bool is_valid = p_render_device->IsMemoryTypeFromProperties(
					p_render_device->GetCurrentPhysicalDeviceMemoryProperties(),
					memory_requirements.memoryTypeBits,
					VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
					&info_alloc.memoryTypeIndex);

				KOTEK_ASSERT(is_valid, "no mappable, coherent memory");

				VkResult status = vkAllocateMemory(
					p_device, &info_alloc, nullptr, &this->m_p_device_memory);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkAllocateMemory. See status");

				/* TODO: DELETE THIS BECAUSE WE CAN ADD TO RENDER GRAPH
				#ifdef KOTEK_DEBUG
				  p_render_device->setDebugNameToResource(VK_OBJECT_TYPE_DEVICE_MEMORY,
				                                          this->m_p_device_memory,
				                                          "ImGui font texture's
				device memory"); #endif*/

				status = vkBindImageMemory(
					p_device, this->m_p_image, this->m_p_device_memory, 0);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkBindImageMemory. See status");
			}

			void kotek_render_imgui_manager::destroyImageMemory(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkFreeMemory(p_device, this->m_p_device_memory, nullptr);
			}

			void kotek_render_imgui_manager::copyBufferToImage(
				ktkRenderResourceManager*
					p_render_resource_manager) noexcept
			{
				kotek_render_upload_heap* p_heap =
					p_render_resource_manager->getUploadHeap();

				VkImageMemoryBarrier copy_barrier[1] = {};

				copy_barrier[0].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
				copy_barrier[0].dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				copy_barrier[0].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				copy_barrier[0].newLayout =
					VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
				copy_barrier[0].srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				copy_barrier[0].dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				copy_barrier[0].image = this->m_p_image;
				copy_barrier[0].subresourceRange.aspectMask =
					VK_IMAGE_ASPECT_COLOR_BIT;
				copy_barrier[0].subresourceRange.layerCount = 1;
				copy_barrier[0].subresourceRange.levelCount = 1;

				vkCmdPipelineBarrier(p_heap->getCommandBuffer(),
					VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
					0, 0, nullptr, 0, nullptr, 1, copy_barrier);

				VkBufferImageCopy region = {};

				int width, height;
				ktk::uint8_t* p_data;

				sui::GetIO().Fonts->GetTexDataAsRGBA32(
					&p_data, &width, &height);

				region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				region.imageSubresource.layerCount = 1;
				region.imageExtent.width = width;
				region.imageExtent.height = height;
				region.imageExtent.depth = 1;

				vkCmdCopyBufferToImage(p_heap->getCommandBuffer(),
					p_heap->getBuffer(), this->m_p_image,
					VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

				VkImageMemoryBarrier use_barrier[1] = {};

				use_barrier[0].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
				use_barrier[0].srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				use_barrier[0].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
				use_barrier[0].oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
				use_barrier[0].newLayout =
					VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				use_barrier[0].srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				use_barrier[0].dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				use_barrier[0].image = this->m_p_image;
				use_barrier[0].subresourceRange.aspectMask =
					VK_IMAGE_ASPECT_COLOR_BIT;
				use_barrier[0].subresourceRange.levelCount = 1;
				use_barrier[0].subresourceRange.layerCount = 1;

				vkCmdPipelineBarrier(p_heap->getCommandBuffer(),
					VK_PIPELINE_STAGE_TRANSFER_BIT,
					VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0,
					nullptr, 1, use_barrier);
			}

			void kotek_render_imgui_manager::writeDataToSuballocatedPartOfHeap(
				ktkRenderResourceManager*
					p_render_resource_manager) noexcept
			{
				sui::GetIO().Fonts->SetTexID(
					static_cast<ImTextureID>(this->m_p_image));

				ktk::uint8_t* p_data;
				int width, height;

				sui::GetIO().Fonts->GetTexDataAsRGBA32(
					&p_data, &width, &height);

				kotek_render_upload_heap* p_heap =
					p_render_resource_manager->getUploadHeap();

				KOTEK_ASSERT(p_heap,
					"you must initialize render resource manager "
					"(kotek_render_upload_heap)");

				ktk::size_t upload_size = width * height * 4 * sizeof(char);

				ktk::uint8_t* pointer_write_in =
					p_heap->subAllocate(upload_size);

				ktk::memory::memcpy(pointer_write_in, p_data,
					width * height * 4 * sizeof(char));
			}

			void kotek_render_imgui_manager::flushHeap(
				ktkRenderResourceManager* p_render_resource_manager,
				ktkRenderDevice* p_render_device) noexcept
			{
				kotek_render_upload_heap* p_heap =
					p_render_resource_manager->getUploadHeap();

				p_heap->flushAndFinish(p_render_device);
			}

			void kotek_render_imgui_manager::createSampler(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must intialize device (VkDevice)");

				VkSamplerCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				info.magFilter = VK_FILTER_NEAREST;
				info.minFilter = VK_FILTER_NEAREST;
				info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
				info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				info.minLod = -1000;
				info.maxLod = 1000;
				info.maxAnisotropy = 1.0f;

				VkResult status = vkCreateSampler(
					p_device, &info, nullptr, &this->m_p_sampler);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreateSampler. See status");
			}

			void kotek_render_imgui_manager::destroySampler(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "you must initialize device (VkDevice)");

				vkDestroySampler(p_device, this->m_p_sampler, nullptr);
			}

			void kotek_render_imgui_manager::compileShaders(
				ktkRenderDevice* p_render_device,
				ktkRenderResourceManager*
					p_render_resource_manager) noexcept
			{
				const char* vertShaderTextGLSL =
					"#version 400\n"
					"#extension GL_ARB_separate_shader_objects : enable\n"
					"#extension GL_ARB_shading_language_420pack : enable\n"
					"layout (std140, binding = 0) uniform vertexBuffer {\n"
					"    mat4 ProjectionMatrix;\n"
					"} myVertexBuffer;\n"
					"layout (location = 0) in vec4 pos;\n"
					"layout (location = 1) in vec2 inTexCoord;\n"
					"layout (location = 2) in vec4 inColor;\n"
					"layout (location = 0) out vec2 outTexCoord;\n"
					"layout (location = 1) out vec4 outColor;\n"
					"void main() {\n"
					"   outColor = inColor;\n"
					"   outTexCoord = inTexCoord;\n"
					"   gl_Position = myVertexBuffer.ProjectionMatrix * pos;\n"
					"}\n";

				const char* fragShaderTextGLSL =
					"#version 400\n"
					"#extension GL_ARB_separate_shader_objects : enable\n"
					"#extension GL_ARB_shading_language_420pack : enable\n"
					"layout (location = 0) in vec2 inTexCoord;\n"
					"layout (location = 1) in vec4 inColor;\n"
					"\n"
					"layout (location = 0) out vec4 outColor;\n"
					"\n"
					"layout(set=0, binding=1) uniform texture2D sTexture;\n"
					"layout(set=0, binding=2) uniform sampler sSampler;\n"
					"\n"
					"void main() {\n"
					"#if 1\n"
					"   outColor = inColor * texture(sampler2D(sTexture, "
					"sSampler), "
					"inTexCoord.st);\n"
					"   const float gamma = 2.2f;\n"
					"   outColor.xyz = pow(outColor.xyz, vec3(gamma, gamma, "
					"gamma));\n"
					"#else\n"
					"   outColor = inColor;\n"
					"#endif\n"
					"}\n";

				VkPipelineShaderStageCreateInfo shader_vertex, shader_fragment;

				auto* p_shader_manager =
					p_render_resource_manager->getShaderManager();

				KOTEK_ASSERT(
					p_shader_manager, "shader manager can't be nullptr");

				auto module_vertex = p_shader_manager->loadShaderAsString(
					vertShaderTextGLSL, shader_type_t::kShaderType_Vertex);
				auto module_fragment = p_shader_manager->loadShaderAsString(
					fragShaderTextGLSL, shader_type_t::kShaderType_Pixel);

				/* TODO: DELETE THIS BECAUSE WE CAN ADD TO RENDER GRAPH
				  p_render_device->setDebugNameToResource(
				      VK_OBJECT_TYPE_SHADER_MODULE, p_module_vertex,
				      "ResourceDebugName_ShaderModule_ImGui_Vertex");

				  p_render_device->setDebugNameToResource(
				      VK_OBJECT_TYPE_SHADER_MODULE, p_module_fragment,
				      "ResourceDebugName_ShaderModule_ImGui_Fragment");*/

				shader_vertex = p_render_resource_manager->buildShader(
					shader_type_t::kShaderType_Vertex,
					module_vertex.getModule());
				shader_fragment = p_render_resource_manager->buildShader(
					shader_type_t::kShaderType_Pixel,
					module_fragment.getModule());

				KOTEK_ASSERT(this->m_shader_stages.empty() == true,
					"you must have here an empty vectory otherwise you didn't "
					"call destroy!");

				this->m_shader_stages.push_back(shader_vertex);
				this->m_shader_stages.push_back(shader_fragment);

				VkDescriptorSetLayoutBinding bindings[3];

				bindings[0].binding = 0;
				bindings[0].descriptorType =
					VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
				bindings[0].descriptorCount = 1;
				bindings[0].stageFlags =
					VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
				bindings[0].pImmutableSamplers = nullptr;

				bindings[1].binding = 1;
				bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
				bindings[1].descriptorCount = 1;
				bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
				bindings[1].pImmutableSamplers = nullptr;

				bindings[2].binding = 2;
				bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
				bindings[2].descriptorCount = 1;
				bindings[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
				bindings[2].pImmutableSamplers = nullptr;

				VkDescriptorSetLayoutCreateInfo info_descriptor_layout = {};

				info_descriptor_layout.sType =
					VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				info_descriptor_layout.pNext = nullptr;
				info_descriptor_layout.flags = 0;
				info_descriptor_layout.bindingCount = 3;
				info_descriptor_layout.pBindings = bindings;

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "your device is invalid (VkDevice)");

				auto status = vkCreateDescriptorSetLayout(p_device,
					&info_descriptor_layout, nullptr,
					&this->m_descriptor_layout);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreateDescriptorSetLayout. See status");

				VkPipelineLayoutCreateInfo info_pipeline_layout = {};

				info_pipeline_layout.sType =
					VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				info_pipeline_layout.pNext = nullptr;
				info_pipeline_layout.pushConstantRangeCount = 0;
				info_pipeline_layout.pPushConstantRanges = nullptr;
				info_pipeline_layout.setLayoutCount = 1;
				info_pipeline_layout.pSetLayouts = &this->m_descriptor_layout;

				status = vkCreatePipelineLayout(p_device, &info_pipeline_layout,
					nullptr, &this->m_pipeline_layout);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreatePipelineLayout, See status");

				for (int i = 0; i < 128; ++i)
				{
					bool status_allocation =
						p_render_resource_manager->GetCreatorHeap()
							->AllocDescriptor(p_render_device,
								this->m_descriptor_layout,
								&this->m_descriptor_sets[i]);

					KOTEK_ASSERT(
						status_allocation, "can't allocate descriptor set");

/*
					p_render_resource_manager->GetDynamicBufferRing()
						->SetDescriptorSet(p_render_device, 0,
							sizeof(VERTEX_CONSTANT_BUFFER),
							this->m_descriptor_sets[i]);*/

					VkDescriptorImageInfo info_descriptor_image[1] = {};

					info_descriptor_image[0].sampler = this->m_p_sampler;
					info_descriptor_image[0].imageLayout =
						VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					info_descriptor_image[0].imageView = this->m_p_image_view;

					VkWriteDescriptorSet writes[2];

					writes[0] = {};

					writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writes[0].pNext = nullptr;
					writes[0].dstSet = this->m_descriptor_sets[i];
					writes[0].descriptorCount = 1;
					writes[0].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
					writes[0].pImageInfo = info_descriptor_image;
					writes[0].dstArrayElement = 0;
					writes[0].dstBinding = 1;

					writes[1] = {};

					writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writes[1].pNext = nullptr;
					writes[1].dstSet = this->m_descriptor_sets[i];
					writes[1].descriptorCount = 1;
					writes[1].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
					writes[1].pImageInfo = info_descriptor_image;
					writes[1].dstArrayElement = 0;
					writes[1].dstBinding = 2;

					vkUpdateDescriptorSets(p_device, 2, writes, 0, nullptr);
				}
			}

			void kotek_render_imgui_manager::destroyPipelineLayout(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "invalid device (VkDevice)");

				vkDestroyPipelineLayout(
					p_device, this->m_pipeline_layout, nullptr);
			}

			void kotek_render_imgui_manager::destroyPipeline(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "invalid device (VkDevice)");

				vkDestroyPipeline(p_device, this->m_p_pipeline, nullptr);
			}

			void kotek_render_imgui_manager::destroyDescriptorSetLayout(
				ktkRenderDevice* p_render_device) noexcept
			{
				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "invalid device (VkDevice)");

				vkDestroyDescriptorSetLayout(
					p_device, this->m_descriptor_layout, nullptr);
			}

			void kotek_render_imgui_manager::updatePipeline(
				VkRenderPass p_render_pass,
				ktkRenderDevice* p_render_device) noexcept
			{
				if (p_render_pass == nullptr)
				{
					KOTEK_MESSAGE_WARNING(
						"you can't pass here an invaid VkRenderPass");
					return;
				}

				VkDevice p_device = p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "invalid device (VkDevice)");

				if (this->m_p_pipeline)
				{
					vkDestroyPipeline(p_device, this->m_p_pipeline, nullptr);
				}

				VkVertexInputBindingDescription binding_vi = {};

				binding_vi.binding = 0;
				binding_vi.stride = sizeof(ImDrawVert);
				binding_vi.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

				VkVertexInputAttributeDescription attrs_vi[3] = {
					{0, 0, VK_FORMAT_R32G32_SFLOAT, 0},
					{1, 0, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 2},
					{2, 0, VK_FORMAT_R8G8B8A8_UNORM, sizeof(float) * 4}};

				VkPipelineVertexInputStateCreateInfo info_vi = {};

				info_vi.sType =
					VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				info_vi.pNext = nullptr;
				info_vi.flags = 0;
				info_vi.vertexBindingDescriptionCount = 1;
				info_vi.pVertexBindingDescriptions = &binding_vi;
				info_vi.vertexAttributeDescriptionCount =
					sizeof(attrs_vi) / sizeof(attrs_vi[0]);
				info_vi.pVertexAttributeDescriptions = attrs_vi;

				VkPipelineInputAssemblyStateCreateInfo info_ia = {};

				info_ia.sType =
					VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				info_ia.pNext = nullptr;
				info_ia.flags = 0;
				info_ia.primitiveRestartEnable = VK_FALSE;
				info_ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

				VkPipelineRasterizationStateCreateInfo info_rs = {};

				info_rs.sType =
					VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				info_rs.pNext = nullptr;
				info_rs.flags = 0;
				info_rs.polygonMode = VK_POLYGON_MODE_FILL;
				info_rs.cullMode = VK_CULL_MODE_NONE;
				info_rs.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
				info_rs.depthClampEnable = VK_FALSE;
				info_rs.rasterizerDiscardEnable = VK_FALSE;
				info_rs.depthBiasEnable = VK_FALSE;
				info_rs.depthBiasSlopeFactor = 0;
				info_rs.depthBiasConstantFactor = 0;
				info_rs.depthBiasClamp = 0;
				info_rs.lineWidth = 1.0f;

				VkPipelineColorBlendAttachmentState attachment_state[1] = {};

				attachment_state[0].blendEnable = VK_TRUE;
				attachment_state[0].srcColorBlendFactor =
					VK_BLEND_FACTOR_SRC_ALPHA;
				attachment_state[0].dstColorBlendFactor =
					VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
				attachment_state[0].colorBlendOp = VK_BLEND_OP_ADD;
				attachment_state[0].srcAlphaBlendFactor =
					VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
				attachment_state[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
				attachment_state[0].alphaBlendOp = VK_BLEND_OP_ADD;
				attachment_state[0].colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
					VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
					VK_COLOR_COMPONENT_A_BIT;

				VkPipelineColorBlendStateCreateInfo info_pipeline_color_blend =
					{};

				info_pipeline_color_blend.sType =
					VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				info_pipeline_color_blend.flags = 0;
				info_pipeline_color_blend.pNext = nullptr;
				info_pipeline_color_blend.attachmentCount = 1;
				info_pipeline_color_blend.pAttachments = attachment_state;
				info_pipeline_color_blend.logicOp = VK_LOGIC_OP_NO_OP;
				info_pipeline_color_blend.logicOpEnable = VK_FALSE;
				info_pipeline_color_blend.blendConstants[0] = 1.0f;
				info_pipeline_color_blend.blendConstants[1] = 1.0f;
				info_pipeline_color_blend.blendConstants[2] = 1.0f;
				info_pipeline_color_blend.blendConstants[3] = 1.0f;

				ktk::vector<VkDynamicState> dynamic_states = {
					VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

				VkPipelineDynamicStateCreateInfo info_pipeline_dynamic_state =
					{};

				info_pipeline_dynamic_state.sType =
					VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				info_pipeline_dynamic_state.pNext = nullptr;
				info_pipeline_dynamic_state.flags = 0;
				info_pipeline_dynamic_state.pDynamicStates =
					dynamic_states.data();
				info_pipeline_dynamic_state.dynamicStateCount =
					dynamic_states.size();

				VkPipelineViewportStateCreateInfo info_pipeline_viewport_state =
					{};

				info_pipeline_viewport_state.sType =
					VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				info_pipeline_viewport_state.pNext = nullptr;
				info_pipeline_viewport_state.flags = 0;
				info_pipeline_viewport_state.viewportCount = 1;
				info_pipeline_viewport_state.scissorCount = 1;
				info_pipeline_viewport_state.pScissors = nullptr;
				info_pipeline_viewport_state.pViewports = nullptr;

				VkPipelineDepthStencilStateCreateInfo
					info_pipeline_depth_stencil_state = {};

				info_pipeline_depth_stencil_state.sType =
					VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				info_pipeline_depth_stencil_state.pNext = nullptr;
				info_pipeline_depth_stencil_state.flags = 0;
				info_pipeline_depth_stencil_state.depthTestEnable = VK_FALSE;
				info_pipeline_depth_stencil_state.depthWriteEnable = VK_FALSE;
				info_pipeline_depth_stencil_state.depthCompareOp =
					VK_COMPARE_OP_LESS_OR_EQUAL;
				info_pipeline_depth_stencil_state.depthBoundsTestEnable =
					VK_FALSE;
				info_pipeline_depth_stencil_state.stencilTestEnable = VK_FALSE;
				info_pipeline_depth_stencil_state.back.failOp =
					VK_STENCIL_OP_KEEP;
				info_pipeline_depth_stencil_state.back.passOp =
					VK_STENCIL_OP_KEEP;
				info_pipeline_depth_stencil_state.back.compareOp =
					VK_COMPARE_OP_ALWAYS;
				info_pipeline_depth_stencil_state.back.compareMask = 0;
				info_pipeline_depth_stencil_state.back.reference = 0;
				info_pipeline_depth_stencil_state.back.depthFailOp =
					VK_STENCIL_OP_KEEP;
				info_pipeline_depth_stencil_state.back.writeMask = 0;
				info_pipeline_depth_stencil_state.minDepthBounds = 0;
				info_pipeline_depth_stencil_state.maxDepthBounds = 0;
				info_pipeline_depth_stencil_state.stencilTestEnable = VK_FALSE;
				info_pipeline_depth_stencil_state.front =
					info_pipeline_depth_stencil_state.back;

				VkPipelineMultisampleStateCreateInfo
					info_pipeline_multisample_state = {};

				info_pipeline_multisample_state.sType =
					VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				info_pipeline_multisample_state.pNext = nullptr;
				info_pipeline_multisample_state.flags = 0;
				info_pipeline_multisample_state.pSampleMask = nullptr;
				info_pipeline_multisample_state.rasterizationSamples =
					VK_SAMPLE_COUNT_1_BIT;
				info_pipeline_multisample_state.sampleShadingEnable = VK_FALSE;
				info_pipeline_multisample_state.alphaToCoverageEnable =
					VK_FALSE;
				info_pipeline_multisample_state.alphaToOneEnable = VK_FALSE;
				info_pipeline_multisample_state.minSampleShading = 0.0f;

				VkGraphicsPipelineCreateInfo info_pipeline_graphics = {};

				info_pipeline_graphics.sType =
					VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				info_pipeline_graphics.pNext = nullptr;
				info_pipeline_graphics.flags = 0;
				info_pipeline_graphics.layout = this->m_pipeline_layout;
				info_pipeline_graphics.basePipelineHandle = nullptr;
				info_pipeline_graphics.basePipelineIndex = 0;
				info_pipeline_graphics.pVertexInputState = &info_vi;
				info_pipeline_graphics.pInputAssemblyState = &info_ia;
				info_pipeline_graphics.pRasterizationState = &info_rs;
				info_pipeline_graphics.pColorBlendState =
					&info_pipeline_color_blend;
				info_pipeline_graphics.pTessellationState = nullptr;
				info_pipeline_graphics.pMultisampleState =
					&info_pipeline_multisample_state;
				info_pipeline_graphics.pDynamicState =
					&info_pipeline_dynamic_state;
				info_pipeline_graphics.pViewportState =
					&info_pipeline_viewport_state;
				info_pipeline_graphics.pDepthStencilState =
					&info_pipeline_depth_stencil_state;
				info_pipeline_graphics.pStages = this->m_shader_stages.data();
				info_pipeline_graphics.stageCount =
					this->m_shader_stages.size();
				info_pipeline_graphics.renderPass = p_render_pass;
				info_pipeline_graphics.subpass = 0;

				auto status = vkCreateGraphicsPipelines(p_device, nullptr, 1,
					&info_pipeline_graphics, nullptr, &this->m_p_pipeline);

				KOTEK_ASSERT(status == VK_SUCCESS,
					"failed to vkCreateGraphicsPipelines, See status");
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek
