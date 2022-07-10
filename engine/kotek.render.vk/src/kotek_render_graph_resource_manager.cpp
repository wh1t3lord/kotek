#include "../include/kotek_render_graph_resource_manager.h"
#include "../include/kotek_render_device.h"
#include "../include/spirv_reflect.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			ktkRenderGraphResourceManager::ktkRenderGraphResourceManager(
				Core::ktkMainManager& main_manager) :
				m_p_render_device(static_cast<ktkRenderDevice*>(
					main_manager.getRenderDevice())),
				m_p_manager_resource(static_cast<ktkRenderResourceManager*>(
					main_manager.GetRenderResourceManager())),
				m_p_profiler(main_manager.GetGameManager()->GetProfiler())
			{
			}

			ktkRenderGraphResourceManager::~ktkRenderGraphResourceManager(void)
			{
			}

			void ktkRenderGraphResourceManager::Initialize(
				eRenderGraphBuilderType type_of_framebuffer,
				eRenderGraphBuilderPipelineRenderingType
					type_videocard_pipeline)
			{
			}

			void ktkRenderGraphResourceManager::Shutdown(void)
			{
				this->DestroyTextures();
				this->DestroyShaders();
				this->DestroyFrameBuffers();
				this->DestroyRenderPasses();
				this->DestroyPipelines();

				// TODO: continue destroying
			}

			void ktkRenderGraphResourceManager::
				CreateShadersAndLayoutsWithDescriptorSets(
					const ktkRenderGraphStorageInput&
						storage_input_of_render_pass) noexcept
			{
				KOTEK_CPU_PROFILE();

				this->CreateShaders_Modules(
					storage_input_of_render_pass.GetShaders());
				this->createDescriptorSetLayouts_And_PipelineLayouts(
					storage_input_of_render_pass);
				this->CreateDescriptorSets(storage_input_of_render_pass);
			}

			void ktkRenderGraphResourceManager::
				CreateSynchronizationPrimitivesAndRenderPass(
					const ktk::string& render_pass_name,
					const ktkRenderGraphStorageInput&
						storage_of_render_pass_input,
					const ktkRenderGraphStorageOutput&
						storage_of_render_pass_output,
					const ktk::unordered_map<ktk::texture_id_t,
						ktkRenderGraphResourceInfo<
							ktkRenderTextureInfo>>& texture_to_create,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<VkBufferCreateInfo>>&
						buffer_to_create) noexcept
			{
				const auto& subpass_dependecies =
					this->CreateSubpassDependencies(
						storage_of_render_pass_output, texture_to_create);
				this->CreateBarriers();
				this->CreateRenderPass(render_pass_name, subpass_dependecies,
					storage_of_render_pass_output);
				this->CreateFrameBuffers(
					render_pass_name, storage_of_render_pass_output);
				this->CreatePipelines(
					render_pass_name, storage_of_render_pass_input);
			}

			void ktkRenderGraphResourceManager::CreateTexture(
				const ktkRenderGraphResourceInfo<
					ktkRenderTextureInfo>& info) noexcept
			{
				KOTEK_CPU_PROFILE();

				const ktk::string& texture_name = info.GetResourceName();
				const ktk::string& render_pass_name = info.GetRenderPassName();

				if (this->m_all_render_graph_textures.find(texture_name) !=
					this->m_all_render_graph_textures.end())
				{
					KOTEK_ASSERT(false, "can't rewrite texture {}",
						texture_name.get_as_is());
					return;
				}

				this->m_all_render_graph_textures[texture_name] =
					this->m_p_manager_resource->GetTextureManager()
						->CreateTexture(info);

				this->m_storage_render_passes_textures[render_pass_name]
													  [texture_name] =
					&this->m_all_render_graph_textures.at(texture_name);
			}

			void ktkRenderGraphResourceManager::CreateBackBuffer(
				const ktk::string& backbuffer_name) noexcept
			{
				KOTEK_CPU_PROFILE();

				KOTEK_ASSERT(backbuffer_name.empty() == false,
					"you must specify your backbuffer (give a name to it)");

				this->m_backbuffer_texture =
					this->m_p_manager_resource->GetTextureManager()
						->CreateTexture(kBackBufferName,
							{helper::InitializeImageForFramebuffer(
								 this->m_p_render_device->GetWidth(),
								 this->m_p_render_device->GetHeight()),
								helper::InitializeSampler()},
							eTextureType::kTextureType_Single);
			}

			const ktkRenderTexture*
			ktkRenderGraphResourceManager::GetTexture(
				const ktk::string& render_pass_name,
				const ktk::string& texture_name) const noexcept
			{
				const ktkRenderTexture* p_result = nullptr;

				if (render_pass_name.empty())
				{
					KOTEK_ASSERT(false, "your render pass name can't be empty");
					return p_result;
				}

				if (texture_name.empty())
				{
					KOTEK_ASSERT(false, "your texture name can't be empty");
					return p_result;
				}

				if (this->m_storage_render_passes_textures.find(
						render_pass_name) ==
					this->m_storage_render_passes_textures.end())
				{
					KOTEK_ASSERT(false, "can't find renderp pass by name {}",
						render_pass_name.get_as_is());
					return p_result;
				}

				if (this->m_storage_render_passes_textures.at(render_pass_name)
						.find(texture_name) ==
					this->m_storage_render_passes_textures.at(render_pass_name)
						.end())
				{
					KOTEK_ASSERT(false,
						"can't find texture {} in render pass {}",
						texture_name.get_as_is(), render_pass_name.get_as_is());
					return p_result;
				}

				p_result =
					this->m_storage_render_passes_textures.at(render_pass_name)
						.at(texture_name);

				return p_result;
			}

			const ktk::unordered_map<ktk::render_pass_id_t,
				ktk::unordered_map<ktk::texture_id_t,
					ktkRenderGraphTexture*>>&
			ktkRenderGraphResourceManager::GetRenderGraph_RenderPasses_Textures(
				void) const noexcept
			{
				return this->m_storage_render_passes_textures;
			}

			void ktkRenderGraphResourceManager::UploadTextureWithData(
				const ktk::string& texture_name, void* p_data) noexcept
			{
				KOTEK_ASSERT(texture_name.empty() == false,
					"can't find texture with empty name");

				ktkRenderTexture* p_texture = nullptr;

				if (this->m_all_render_graph_textures.find(texture_name) ==
					this->m_all_render_graph_textures.end())
				{
					KOTEK_ASSERT(false,
						"can't find texture [{}] in all storages",
						texture_name.get_as_is());
				}
				else
				{
					p_texture =
						&this->m_all_render_graph_textures.at(texture_name);
				}

				this->m_p_manager_resource->GetTextureManager()
					->UploadTextureWithData(p_texture, p_data);
			}

			ktk::vector<VkDescriptorSet>
			ktkRenderGraphResourceManager::GetDescriptorSets(
				const ktk::string& pipeline_name) const noexcept
			{
				if (pipeline_name.empty())
				{
					KOTEK_ASSERT(false,
						"you passed an empty pipeline name string. can't find "
						"VkDescriptorSets");
					return ktk::vector<VkDescriptorSet>();
				}

				if (this->m_storage_descriptor_sets.find(pipeline_name) ==
					this->m_storage_descriptor_sets.end())
				{
					if (this->m_validation_info_for_descriptor_sets_about_whole_user_pipeline
							.find(pipeline_name) !=
						this->m_validation_info_for_descriptor_sets_about_whole_user_pipeline
							.end())
					{
						if (this->m_validation_info_for_descriptor_sets_about_whole_user_pipeline
								.at(pipeline_name)
								.empty() == false)
						{
							KOTEK_ASSERT(false,
								"Can't find descriptor sets by pipeline name: "
								"{}",
								pipeline_name.get_as_is());
						}
					}

					return {};
				}

				return this->m_storage_descriptor_sets.at(pipeline_name);
			}

			VkRenderPass ktkRenderGraphResourceManager::GetRenderPass(
				const ktk::string& render_pass_name) const noexcept
			{
				if (render_pass_name.empty())
				{
					KOTEK_ASSERT(false,
						"you pass an empty string can't find VkRenderPass");
					return nullptr;
				}

				if (this->m_storage_render_passes_render_passes_handles.find(
						render_pass_name) ==
					this->m_storage_render_passes_render_passes_handles.end())
				{
					KOTEK_ASSERT(false, "can't find render pass by name: {}",
						render_pass_name.get_as_is());
					return nullptr;
				}

				return this->m_storage_render_passes_render_passes_handles.at(
					render_pass_name);
			}

			VkFramebuffer ktkRenderGraphResourceManager::GetFrameBuffer(
				const ktk::string& render_pass_name) const noexcept
			{
				if (render_pass_name.empty())
				{
					KOTEK_ASSERT(false,
						"you passed an empty render pass name can't find "
						"VkFramebuffer");
					return nullptr;
				}

				if (this->m_storage_render_passes_framebuffers.find(
						render_pass_name) ==
					this->m_storage_render_passes_framebuffers.end())
				{
					KOTEK_ASSERT(false,
						"can't find VkFramebuffer by render pass name: {}",
						render_pass_name.get_as_is());
					return nullptr;
				}

				return this->m_storage_render_passes_framebuffers.at(
					render_pass_name);
			}

			VkPipeline ktkRenderGraphResourceManager::GetPipeline(
				const ktk::string& pipeline_name) const noexcept
			{
				if (pipeline_name.empty())
				{
					KOTEK_ASSERT(false,
						"you passed an empty pipeline name. Can't find "
						"VkPipeline");
					return nullptr;
				}

				if (this->m_storage_pipelines.find(pipeline_name) ==
					this->m_storage_pipelines.end())
				{
					KOTEK_ASSERT(false,
						"Can't find VkPipeline by pipeline name: {}",
						pipeline_name.get_as_is());
					return nullptr;
				}

				return this->m_storage_pipelines.at(pipeline_name);
			}

			VkPipelineLayout ktkRenderGraphResourceManager::GetPipelineLayout(
				const ktk::string& pipeline_name) const noexcept
			{
				if (pipeline_name.empty())
				{
					KOTEK_ASSERT(false,
						"you can't pass an empty string for getting "
						"VkPipelineLayout by pipeline name");
					return nullptr;
				}

				if (this->m_storage_pipeline_layouts.find(pipeline_name) ==
					this->m_storage_pipeline_layouts.end())
				{
					KOTEK_ASSERT(false, "");
					return nullptr;
				}

				return this->m_storage_pipeline_layouts.at(pipeline_name);
			}

			const ktkRenderTexture*
			ktkRenderGraphResourceManager::GetBackBufferTexture(
				void) const noexcept
			{
				return &this->m_backbuffer_texture;
			}

			void ktkRenderGraphResourceManager::DestroyShaders(void) noexcept
			{
				for (const auto& [pipeline_name, p_descriptor_layout] :
					this->m_storage_descriptor_set_layouts)
				{
#ifdef KOTEK_DEBUG
					KOTEK_MESSAGE(
						"Destroying VkDescriptorSetLayout for pipeline: {}",
						pipeline_name.get_as_is());
#endif
					vkDestroyDescriptorSetLayout(
						this->m_p_render_device->GetDevice(),
						p_descriptor_layout, nullptr);
				}

				this->m_storage_descriptor_set_layouts.clear();

				for (const auto& [pipeline_name, p_pipeline_layout] :
					this->m_storage_pipeline_layouts)
				{
#ifdef KOTEK_DEBUG
					KOTEK_MESSAGE(
						"Destroying VkPipelineLayout for pipeline: {}",
						pipeline_name.get_as_is());
#endif
					vkDestroyPipelineLayout(
						this->m_p_render_device->GetDevice(), p_pipeline_layout,
						nullptr);
				}

				this->m_storage_pipeline_layouts.clear();

				for (const auto& [pipeline_name,
						 map_shader_type_and_shader_module] :
					this->m_storage_shaders)
				{
#ifdef KOTEK_DEBUG
					KOTEK_MESSAGE("Destroying VkShaderModules in pipeline: {}",
						pipeline_name.get_as_is());
#endif
					for (const auto& [shader_type, shader_module] :
						map_shader_type_and_shader_module)
					{
						this->m_p_manager_resource->getShaderManager()
							->destroyShader(shader_module);
					}
				}

				this->m_storage_shaders.clear();
			}

			void ktkRenderGraphResourceManager::DestroyTextures(void) noexcept
			{
				for (auto& [texture_name, texture] :
					this->m_all_render_graph_textures)
				{
					this->m_p_manager_resource->GetTextureManager()
						->DestroyTexture(
							this->m_p_render_device->GetAllocator(), &texture);
				}

				this->m_p_manager_resource->GetTextureManager()->DestroyTexture(
					this->m_p_render_device->GetAllocator(),
					&this->m_backbuffer_texture);

				this->m_all_render_graph_textures.clear();
				this->m_storage_render_passes_textures.clear();
			}

			void ktkRenderGraphResourceManager::DestroyRenderPasses(
				void) noexcept
			{
				auto* p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "your device is invalid");

				for (const auto& [render_pass_name, p_pass] :
					this->m_storage_render_passes_render_passes_handles)
				{
					vkDestroyRenderPass(p_device, p_pass, nullptr);
				}

				this->m_storage_render_passes_render_passes_handles.clear();
			}

			void ktkRenderGraphResourceManager::DestroyFrameBuffers(
				void) noexcept
			{
				auto* p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(
					p_device, "you can't have an invalid device (VkDevice)");

				for (const auto& [render_pass_name, p_frame_buffer] :
					this->m_storage_render_passes_framebuffers)
				{
					vkDestroyFramebuffer(p_device, p_frame_buffer, nullptr);
				}

				this->m_storage_render_passes_framebuffers.clear();
			}

			void ktkRenderGraphResourceManager::DestroyPipelines(void) noexcept
			{
				VkDevice p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(
					p_device, "you can't have an invalid device (VkDevice)");

				for (const auto& [pipeline_name, p_pipeline] :
					this->m_storage_pipelines)
				{
					vkDestroyPipeline(p_device, p_pipeline, nullptr);
				}

				this->m_storage_pipelines.clear();
			}

			bool ktkRenderGraphResourceManager::IsFileOrSourceCodeString(
				const ktk::string& string_to_analyze) noexcept
			{
				KOTEK_CPU_PROFILE();

				if (string_to_analyze.empty())
				{
					KOTEK_ASSERT(false, "can't analyze empty string");
					return false;
				}

				bool is_file = true;

				if (string_to_analyze.get_as_is().find(KOTEK_TEXT("main")) !=
					ktk::string::npos)
				{
					// it's source code, because it's direct text of shader
					return false;
				}

				return true;
			}

			bool ktkRenderGraphResourceManager::IsFileWithFormat(
				const ktk::string& path_name) noexcept
			{
				KOTEK_CPU_PROFILE();

				if (path_name.empty())
				{
					KOTEK_ASSERT(false, "you can't pass an empty string");
					return false;
				}

				if (path_name.get_as_is().find(KOTEK_TEXT(".")) ==
					ktk::string::npos)
				{
					return false;
				}

				return true;
			}

			void ktkRenderGraphResourceManager::CreateShaders_Modules(
				const ktk::unordered_map<ktk::pipeline_id_t,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
					render_graph_builder_data) noexcept
			{
				KOTEK_CPU_PROFILE();

				auto* p_shader_manager =
					this->m_p_manager_resource->getShaderManager();

				// TODO: caching system
				for (const auto& [pipeline_name,
						 map_shader_type_and_shader_data] :
					render_graph_builder_data)
				{
					for (const auto& [shader_type, shader_data] :
						map_shader_type_and_shader_data)
					{
						KOTEK_ASSERT(shader_data.getType() !=
								shader_loading_data_type_t::
									kShaderLoadingDataType_NotInitialized,
							"you must initialize your shader data before "
							"adding");

						switch (shader_data.getType())
						{
						case shader_loading_data_type_t::
							kShaderLoadingDataType_FilePathString:
						{
							if (this->m_storage_shaders.find(pipeline_name) !=
								this->m_storage_shaders.end())
							{
								if (this->m_storage_shaders.at(pipeline_name)
										.find(shader_type) !=
									this->m_storage_shaders.at(pipeline_name)
										.end())
								{
									KOTEK_ASSERT(false,
										"you can't add new shader type {} that "
										"is existed in "
										"pipeline [{}] that is existed in "
										"manager, because "
										"manager collects every pipeline for "
										"sharing them "
										"between passes",
										helper::translateShaderTypeToString(
											shader_type)
											.get_as_is(),
										pipeline_name.get_as_is());
								}
							}

							ktk::string shader_string_copy =
								std::get<ktk::string>(shader_data.getData());

							if (this->IsFileWithFormat(shader_string_copy) ==
								false)
							{
								// means without format
								shader_string_copy +=
									helper::translateShaderTypeToStringFormat(
										shader_type);
							}

							this->m_storage_shaders[pipeline_name]
												   [shader_type] =
								p_shader_manager->loadShader(
									shader_string_copy, shader_type);

							break;
						}
						case shader_loading_data_type_t::
							kShaderLoadingDataType_SourceCodeTextString:
						{
							this->m_storage_shaders[pipeline_name]
												   [shader_type] =
								p_shader_manager->loadShaderAsString(
									std::get<ktk::string>(
										shader_data.getData()),
									shader_type);
						}
						case shader_loading_data_type_t::
							kShaderLoadingDataType_ByteArrayFile:
						{
							// TODO: implement
							KOTEK_ASSERT(false, "not implement");
							break;
						}
						case shader_loading_data_type_t::
							kShaderLoadingDataType_ByteArrayCompiledSPIRV:
						{
							// TODO: implement
							KOTEK_ASSERT(false, "not implement");
							break;
						}
						}
					}
				}
			}

			ktk::vector<VkSubpassDependency>
			ktkRenderGraphResourceManager::CreateSubpassDependencies(
				const ktkRenderGraphStorageOutput& storage_output,
				const ktk::unordered_map<ktk::texture_id_t,
					ktkRenderGraphResourceInfo<
						ktkRenderTextureInfo>>&
					texture_to_create) noexcept
			{
				ktk::vector<VkSubpassDependency> result;

				if (storage_output.GetImages().empty())
				{
					VkSubpassDependency dependency = {};

					dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
					dependency.dstSubpass = 0;
					dependency.srcStageMask = VkPipelineStageFlagBits::
						VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
					dependency.srcAccessMask =
						VkAccessFlagBits::VK_ACCESS_NONE_KHR;
					dependency.dstStageMask = VkPipelineStageFlagBits::
						VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
					dependency.dstAccessMask =
						VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
						VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

					result.push_back(dependency);
				}
				else
				{
					KOTEK_ASSERT(false, "not implemented yet");
				}

				return result;
			}

			void ktkRenderGraphResourceManager::
				createDescriptorSetLayouts_And_PipelineLayouts(
					const ktkRenderGraphStorageInput& storage) noexcept
			{
				ktk::vector<VkDescriptorSetLayoutBinding>
					all_bindings_for_whole_pipeline;
				ktk::unordered_map<ktk::string,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<descriptor_set_info_t>>>
					validate_info_from_spirv_reflect;

				for (const auto& [pipeline_name,
						 map_shader_type_and_shader_module] :
					this->m_storage_shaders)
				{
					if (this->m_storage_descriptor_set_layouts.find(
							pipeline_name) !=
						this->m_storage_descriptor_set_layouts.end())
					{
						KOTEK_ASSERT(false,
							"can't add existed pipeline to descriptor set "
							"layouts: {}",
							pipeline_name.get_as_is());
						continue;
					}

					if (this->m_storage_pipeline_layouts.find(pipeline_name) !=
						this->m_storage_pipeline_layouts.end())
					{
						KOTEK_ASSERT(false,
							"can't add existed pipeline to pipeline layout: {}",
							pipeline_name.get_as_is());
						continue;
					}

					for (const auto& [shader_type, shader_module] :
						map_shader_type_and_shader_module)
					{
						const auto& bindings_for_current_shader =
							this->CollectDescriptorSetLayoutBingings(
								shader_module);
						const auto& validation_data =
							this->CollectValidationData(shader_module);

						for (const auto& [descriptor_set_index, datas] :
							validation_data)
						{
							validate_info_from_spirv_reflect
								[pipeline_name][descriptor_set_index]
									.insert(validate_info_from_spirv_reflect
												.at(pipeline_name)
												.at(descriptor_set_index)
												.end(),
										datas.begin(), datas.end());
						}

						all_bindings_for_whole_pipeline.insert(
							all_bindings_for_whole_pipeline.end(),
							bindings_for_current_shader.begin(),
							bindings_for_current_shader.end());
					}

					VkDescriptorSetLayoutCreateInfo info = {};

					info.sType =
						VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
					info.pBindings = all_bindings_for_whole_pipeline.data();
					info.bindingCount = all_bindings_for_whole_pipeline.size();

					// TODO: use CreatorHeap for reducing repeated code for
					// creating VkDescriptorSetLayour and VkPipelineLayout
					// respectively

					VkDescriptorSetLayout p_layout = nullptr;

					auto status = vkCreateDescriptorSetLayout(
						this->m_p_render_device->GetDevice(), &info, nullptr,
						&p_layout);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"failed to vkCreateDescriptorSetLayout. See status: {}",
						status);

					VkPipelineLayoutCreateInfo info_pipeline = {};

					// TODO: push constants???
					info_pipeline.sType =
						VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
					info_pipeline.pSetLayouts = &p_layout;
					info_pipeline.setLayoutCount = 1;

					VkPipelineLayout p_pipeline = nullptr;

					status = vkCreatePipelineLayout(
						this->m_p_render_device->GetDevice(), &info_pipeline,
						nullptr, &p_pipeline);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"failed to vkCreatePipelineLayout. See status: {}",
						status);

					this->m_storage_descriptor_set_layouts[pipeline_name] =
						p_layout;
					this->m_storage_pipeline_layouts[pipeline_name] =
						p_pipeline;

					all_bindings_for_whole_pipeline.clear();
				}

				this->ValidateInputDataForShaders(storage.GetShadersInputData(),
					validate_info_from_spirv_reflect);

				this->m_validation_info_for_descriptor_sets_about_whole_user_pipeline =
					validate_info_from_spirv_reflect;
			}

			void ktkRenderGraphResourceManager::CreateDescriptorSets(
				const ktkRenderGraphStorageInput& storage) noexcept
			{
				for (const auto& [pipeline_name,
						 map_descriptor_index_descriptor_data] :
					storage.GetShadersInputData())
				{
					for (const auto& [descriptor_index, descriptor_data] :
						map_descriptor_index_descriptor_data)
					{
						VkDescriptorSet p_descriptor = nullptr;

						this->m_p_manager_resource->GetCreatorHeap()
							->AllocDescriptor(this->m_p_render_device,
								this->m_storage_descriptor_set_layouts.at(
									pipeline_name),
								&p_descriptor);

						KOTEK_ASSERT(p_descriptor,
							"can't allocate the descriptor see code in creator "
							"heap");

						for (const auto& data : descriptor_data)
						{
							if (data.IsDataFor() == true)
							{
								this->m_p_manager_resource
									->GetDynamicBufferRing()
									->SetDescriptorSet(this->m_p_render_device,
										data.getBindingIndex(),
										data.GetData_BufferSize(),
										data.getDescriptorType(), p_descriptor);
							}
							else
							{
								const ktk::string& texture_name =
									data.GetData_RenderGraphTextureName();

								const auto* p_texture = this->GetTexture(
									data.GetRenderPassName(), texture_name);

								KOTEK_ASSERT(p_texture,
									"can't find texture {} in pass {}",
									data.GetRenderPassName().get_as_is(),
									texture_name.get_as_is());

								// TODO: think about it do we need to hardcode
								// here and is it fine? I mean about image
								// layout
								this->m_p_manager_resource
									->GetDynamicBufferRing()
									->SetDescriptorSet(this->m_p_render_device,
										data.getBindingIndex(),
										p_texture->GetImageSamplerHandle(),
										VkImageLayout::
											VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
										p_texture->GetImageViewHandle(),
										data.getDescriptorType(), p_descriptor);
							}
						}

						this->m_storage_descriptor_sets[pipeline_name]
							.push_back(p_descriptor);
					}
				}
			}

			void ktkRenderGraphResourceManager::CreateFrameBuffers(
				const ktk::string& render_pass_name,
				const ktkRenderGraphStorageOutput& storage) noexcept
			{
				if (this->m_storage_render_passes_framebuffers.find(
						render_pass_name) !=
					this->m_storage_render_passes_framebuffers.end())
				{
					KOTEK_ASSERT(false,
						"you can't overwrite your existed frame buffer for "
						"pass: {}",
						render_pass_name.get_as_is());
				}

				ktk::vector<VkImageView> attachments;

				// TODO: think about validation (???) because user can pass in
				// not right order
				if (storage.GetImages().empty())
				{
					KOTEK_ASSERT(
						this->m_backbuffer_texture.GetImageViewHandle(),
						"VkImageView handle is invalid for back buffer");

					if (storage.IsUseBackBuffer() == false)
					{
						KOTEK_MESSAGE_WARNING(
							"you don't want to "
							"create framebuffer with backbuffer, because you "
							"don't have any output images and you "
							"SetUseBackBuffer to false for render pass: {}",
							render_pass_name.get_as_is());

						return;
					}

					attachments.push_back(
						this->m_backbuffer_texture.GetImageViewHandle());
				}
				else
				{
					for (const auto& [texture_name, info] : storage.GetImages())
					{
						const auto* p_texture =
							this->GetTexture(render_pass_name, texture_name);

						KOTEK_ASSERT(p_texture, "your texture is invalid {}",
							p_texture->GetTextureName().get_as_is());
						KOTEK_ASSERT(p_texture->GetImageViewHandle(),
							"VkImageView handle is invalid {}",
							p_texture->GetTextureName().get_as_is());

						attachments.push_back(p_texture->GetImageViewHandle());
					}
				}

				auto p_pass =
					this->m_storage_render_passes_render_passes_handles.at(
						render_pass_name);

				KOTEK_ASSERT(
					p_pass, "you must create a valid VkRenderPass handle!");

				auto* p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "your device is invalid");

				VkFramebufferCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				info.pNext = nullptr;
				info.renderPass = p_pass;
				info.pAttachments = attachments.data();
				info.attachmentCount = attachments.size();
				info.width = this->m_p_render_device->GetWidth();
				info.height = this->m_p_render_device->GetHeight();
				info.layers = 1; // TODO: think about it ???

				VkFramebuffer p_frame_buffer = nullptr;

				auto status = vkCreateFramebuffer(
					p_device, &info, nullptr, &p_frame_buffer);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "failed to vkCreateFramebuffer");

				this->m_storage_render_passes_framebuffers[render_pass_name] =
					p_frame_buffer;
			}

			void ktkRenderGraphResourceManager::CreateRenderPass(
				const ktk::string& render_pass_name,
				const ktk::vector<VkSubpassDependency>& dependencies,
				const ktkRenderGraphStorageOutput&
					storage_output) noexcept
			{
				if (this->m_storage_render_passes_render_passes_handles.find(
						render_pass_name) !=
					this->m_storage_render_passes_render_passes_handles.end())
				{
					KOTEK_ASSERT(false,
						"you can't overwrite the existed VkRenderPass for "
						"pass: {}",
						render_pass_name.get_as_is());
				}

				KOTEK_ASSERT(render_pass_name.empty() == false,
					"you can't pass an empty render pass name here");

				KOTEK_ASSERT(dependencies.empty() == false,
					"you can't pass an empty VkSubpassDependency vector");

				const auto& color_references =
					this->CreateRenderPassAttachmentReferences(storage_output);

				const auto& subpass_descriptions =
					this->CreateRenderPassSubpassDescriptions(
						storage_output, color_references);

				const auto& descriptions_attachments =
					this->CreateRenderPassAttachmentDescription(storage_output);

				VkRenderPassCreateInfo info = {};

				info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
				info.pAttachments = descriptions_attachments.data();
				info.attachmentCount = descriptions_attachments.size();
				info.subpassCount = subpass_descriptions.size();
				info.pSubpasses = subpass_descriptions.data();
				info.dependencyCount = dependencies.size();
				info.pDependencies = dependencies.data();

				auto* p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(p_device, "your device is invalid");

				VkRenderPass p_pass = nullptr;

				auto status =
					vkCreateRenderPass(p_device, &info, nullptr, &p_pass);

				KOTEK_ASSERT(
					status == VK_SUCCESS, "failed to vkCreateRenderPass");

				this->m_storage_render_passes_render_passes_handles
					[render_pass_name] = p_pass;
			}

			ktk::vector<VkAttachmentReference>
			ktkRenderGraphResourceManager::CreateRenderPassAttachmentReferences(
				const ktkRenderGraphStorageOutput& storage) noexcept
			{
				ktk::vector<VkAttachmentReference> result;

				if (storage.GetImages().empty())
				{
					// TODO: add depth buffer for back buffer (?);
					VkAttachmentReference ref = {};

					ref.attachment = 0;
					ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

					result.push_back(ref);
				}
				else
				{
					KOTEK_ASSERT(false, "not implemented yet");
				}

				return result;
			}

			ktk::vector<VkSubpassDescription>
			ktkRenderGraphResourceManager::CreateRenderPassSubpassDescriptions(
				const ktkRenderGraphStorageOutput& storage,
				const ktk::vector<VkAttachmentReference>&
					color_references) noexcept
			{
				ktk::vector<VkSubpassDescription> result;

				if (storage.GetImages().empty())
				{
					// TODO: add depth buffer for back buffer (?);
					VkSubpassDescription desc = {};

					desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
					desc.colorAttachmentCount = color_references.size();
					desc.pColorAttachments = color_references.data();
					desc.pDepthStencilAttachment = nullptr;

					result.push_back(desc);
				}
				else
				{
					KOTEK_ASSERT(false, "not implemented yet!");
				}

				return result;
			}

			ktk::vector<VkAttachmentDescription> ktkRenderGraphResourceManager::
				CreateRenderPassAttachmentDescription(
					const ktkRenderGraphStorageOutput& storage) noexcept
			{
				ktk::vector<VkAttachmentDescription> result;

				// TODO: think about samples

				if (storage.GetImages().empty())
				{
					VkAttachmentDescription desc = {};

					desc.format = kImageFormat;
					desc.samples = VK_SAMPLE_COUNT_1_BIT;
					desc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					desc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
					desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					desc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

					result.push_back(desc);
				}
				else
				{
					KOTEK_ASSERT(false, "not implemented yet!");
				}

				return result;
			}

			void ktkRenderGraphResourceManager::CreateBarriers(void) noexcept {}

			// TODO: make all validations by physical device limits of current
			// physical device, so you need create a wrapper for physical device
			void ktkRenderGraphResourceManager::CreatePipelines(
				const ktk::string& render_pass_name,
				const ktkRenderGraphStorageInput& storage) noexcept
			{
				if (storage.GetPipelinesInfo().empty() &&
					storage.GetShaders().empty())
				{
					KOTEK_MESSAGE_WARNING("you don't create "
										  "VkPipeline for render pass: {}",
						render_pass_name.get_as_is());

					return;
				}

				KOTEK_ASSERT(storage.GetPipelinesInfo().empty() == false,
					"you must add one info at least for creating VkPipeline "
					"handle");

				KOTEK_ASSERT(storage.GetPipelinesInfo().size() ==
						storage.GetShaders().size(),
					"each pipeline must contain shaders, but you don't have "
					"equality! Some pipeline is missed");

				VkDevice p_device = this->m_p_render_device->GetDevice();

				KOTEK_ASSERT(p_device,
					"you must have initialized VkDevice. It's invalid.");

				ktk::vector<VkPipelineShaderStageCreateInfo>
					current_pipeline_shader_stages;

				// TODO: improve that system
				for (const auto& [pipeline_name, info] :
					storage.GetPipelinesInfo())
				{
					if (this->m_storage_pipelines.find(pipeline_name) !=
						this->m_storage_pipelines.end())
					{
						KOTEK_ASSERT(false,
							"each pipeline must have unique name and you can't "
							"overwrite existed VkPipeline {}",
							pipeline_name.get_as_is());
					}

					for (const auto& [shader_type, shader_module] :
						this->m_storage_shaders.at(pipeline_name))
					{
						current_pipeline_shader_stages.push_back(
							helper::InitializePipelineShaderStage(
								shader_type, shader_module.getModule()));
					}

					bool is_use_tesselation =
						this->IsUseTesselationInPipeline(pipeline_name);

					VkPipelineDynamicStateCreateInfo info_state_dynamic =
						helper::InitializePipelineDynamicState(
							info.GetDynamicStates());

					VkPipelineVertexInputStateCreateInfo info_state_vertex =
						helper::InitializePipelineVertexInputState(
							info.GetVertexBindingDescriptions(),
							info.GetVertexAttributes());

					VkPipelineColorBlendStateCreateInfo info_state_color_blend =
						helper::InitializePipelineColorBlendState(
							info.GetColorBlendAttachments());

					VkGraphicsPipelineCreateInfo info_create =
						helper::InitializeGraphicsPipeline(is_use_tesselation,
							info, &info_state_vertex, &info_state_color_blend,
							&info_state_dynamic,
							this->m_storage_pipeline_layouts.at(pipeline_name),
							this->m_storage_render_passes_render_passes_handles
								.at(render_pass_name));

					info_create.pStages = current_pipeline_shader_stages.data();
					info_create.stageCount =
						current_pipeline_shader_stages.size();

					VkPipeline p_pipeline = nullptr;

					auto status = vkCreateGraphicsPipelines(p_device, nullptr,
						1, &info_create, nullptr, &p_pipeline);

					KOTEK_ASSERT(status == VK_SUCCESS,
						"failed to vkCreateGraphicsPipelines");

					this->m_storage_pipelines[pipeline_name] = p_pipeline;

					current_pipeline_shader_stages.clear();
				}
			}

			ktk::vector<VkDescriptorSetLayoutBinding>
			ktkRenderGraphResourceManager::CollectDescriptorSetLayoutBingings(
				const kotek_render_shader_manager::shader_module_t&
					your_module) noexcept
			{
				ktk::vector<VkDescriptorSetLayoutBinding> result;

				KOTEK_ASSERT(your_module.getModule(),
					"your class must contain valid VkShaderModule");

				KOTEK_ASSERT(your_module.getSPIRVByteCode().empty() == false,
					"your class must contain valid SPIRV vector data field "
					"from "
					"VkShaderModuleCreateInfo");

				SpvReflectShaderModule spv_module = {};
				SpvReflectResult status = spvReflectCreateShaderModule(
					your_module.getSPIRVByteCode().size() *
						sizeof(ktk::uint32_t),
					your_module.getSPIRVByteCode().data(), &spv_module);

				KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
					"SPIRV-Reflect failed to spvReflectCreateShaderModule");

				ktk::uint32_t count = 0;
				status = spvReflectEnumerateDescriptorSets(
					&spv_module, &count, nullptr);

				KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
					"SPIRV-Reflect failed to spvReflectEnumerateDescriptorSets")

				ktk::vector<SpvReflectDescriptorSet*> sets(count);
				status = spvReflectEnumerateDescriptorSets(
					&spv_module, &count, sets.data());

				KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
					"SPIRV-Reflect failed to spvReflectEnumerateDescriptorSets "
					"(fill SpvReflectDescriptorSet* to vector)");

				ktk::vector<VkDescriptorSetLayoutBinding> temp;
				for (const auto* p_descriptor_set : sets)
				{
					temp.resize(p_descriptor_set->binding_count);

					for (ktk::uint32_t binding_index = 0;
						 binding_index < p_descriptor_set->binding_count;
						 ++binding_index)
					{
						const SpvReflectDescriptorBinding* p_binding =
							p_descriptor_set->bindings[binding_index];

						VkDescriptorSetLayoutBinding& info =
							temp[binding_index];

						info.binding = p_binding->binding;
						info.descriptorCount = 1;
						info.descriptorType = static_cast<VkDescriptorType>(
							p_binding->descriptor_type);
						info.stageFlags = static_cast<VkShaderStageFlagBits>(
							spv_module.shader_stage);

						// TODO: understand what array means here
						for (ktk::uint32_t index = 0;
							 index < p_binding->array.dims_count; ++index)
						{
							info.descriptorCount *=
								p_binding->array.dims[index];
						}
					}

					result.insert(result.end(), temp.begin(), temp.end());
					temp.clear();
				}

				spvReflectDestroyShaderModule(&spv_module);

				return result;
			}

			ktk::unordered_map<ktk::uint32_t,
				ktk::vector<descriptor_set_info_t>>
			ktkRenderGraphResourceManager::CollectValidationData(
				const kotek_render_shader_manager::shader_module_t&
					your_module) noexcept
			{
				ktk::unordered_map<ktk::uint32_t,
					ktk::vector<descriptor_set_info_t>>
					result;

				KOTEK_ASSERT(your_module.getSPIRVByteCode().empty() == false,
					"your class must contain valid SPIRV vector data field "
					"from "
					"VkShaderModuleCreateInfo");

				SpvReflectShaderModule spv_module = {};
				SpvReflectResult status = spvReflectCreateShaderModule(
					your_module.getSPIRVByteCode().size() *
						sizeof(ktk::uint32_t),
					your_module.getSPIRVByteCode().data(), &spv_module);

				KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
					"SPIRV-Reflect failed to spvReflectCreateShaderModule");

				ktk::uint32_t count = 0;
				status = spvReflectEnumerateDescriptorSets(
					&spv_module, &count, nullptr);

				KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
					"SPIRV-Reflect failed to spvReflectEnumerateDescriptorSets")

				ktk::vector<SpvReflectDescriptorSet*> sets(count);
				status = spvReflectEnumerateDescriptorSets(
					&spv_module, &count, sets.data());

				KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
					"SPIRV-Reflect failed to spvReflectEnumerateDescriptorSets "
					"(fill SpvReflectDescriptorSet* to vector)");

				for (auto* p_set : sets)
				{
					auto is_equal_pointer = spvReflectGetDescriptorSet(
						&spv_module, p_set->set, &status);
					KOTEK_ASSERT(status == SPV_REFLECT_RESULT_SUCCESS,
						"SPIRV-Reflect failed to spvReflectGetDescriptorSet");
					KOTEK_ASSERT(is_equal_pointer == p_set,
						"SPIRV-Reflect obtained not valid pointer or that "
						"pointer "
						"doesn't equal to current");

					for (ktk::uint32_t i = 0; i < p_set->binding_count; ++i)
					{
						const auto* p_binding = p_set->bindings[i];

						// TODO: support dims_arr
						result[p_binding->set].push_back(
							{p_binding->set, p_binding->binding,
								static_cast<VkDescriptorType>(
									p_binding->descriptor_type),
								helper::GetShaderTypeByShaderStageFlagBits(
									static_cast<VkShaderStageFlagBits>(
										spv_module.shader_stage)),
								p_binding->name});
					}
				}

				spvReflectDestroyShaderModule(&spv_module);

				return result;
			}

			void ktkRenderGraphResourceManager::ValidateInputDataForShaders(
				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<shader_input_data_t>>>& storage,
				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<ktk::uint32_t,
						ktk::vector<descriptor_set_info_t>>>&
					validation_data) noexcept
			{
#ifdef KOTEK_DEBUG
				if (validation_data.empty())
					return;

				KOTEK_ASSERT(storage.size() == validation_data.size(),
					"size must be equal, you missed some pipeline");

				for (const auto& [pipeline_name, descriptor_sets_map] :
					validation_data)
				{
					for (const auto& [descriptor_set_index, bindings] :
						descriptor_sets_map)
					{
						const auto& bindings_from_storage =
							storage.at(pipeline_name).at(descriptor_set_index);
						for (const auto& binding : bindings)
						{
							auto result = std::find_if(
								bindings_from_storage.begin(),
								bindings_from_storage.end(),
								[binding](const shader_input_data_t&
										binding_from_storage) -> bool
								{
									KOTEK_ASSERT(binding_from_storage
													 .getDescriptorSetIndex() ==
											binding.getDescriptorSetIndex(),
										"something is wrong, your index in "
										"storage is not "
										"valid! See how you fill data to "
										"storage");

									KOTEK_ASSERT(
										binding_from_storage.GetRenderPassName()
												.empty() == false,
										"you can't have an amepty render pass "
										"name for shader input data!");

									return (binding_from_storage
												   .getBindingIndex() ==
											   binding.getBindingIndex()) &&
										(binding_from_storage
												.getDescriptorType() ==
											binding.getDescriptorType());
								});

							if (result == bindings_from_storage.end())
								helper::printBindingInfo(binding);

							KOTEK_ASSERT(result != bindings_from_storage.end(),
								"your storage doesn't have binding for "
								"variable {} in shader {}",
								binding.getVariableName().get_as_is(),
								helper::translateShaderTypeToString(
									binding.GetShaderType())
									.get_as_is());
						}
					}
				}
#endif
			}

			bool ktkRenderGraphResourceManager::IsUseTesselationInPipeline(
				const ktk::string& pipeline_name) const noexcept
			{
				bool result = false;

				if (pipeline_name.empty())
					return result;

				if (this->m_storage_shaders.empty())
					return result;

				const auto& map_shaders =
					this->m_storage_shaders.at(pipeline_name);

				if ((map_shaders.find(
						 shader_type_t::kShaderType_TessellationControl) !=
						map_shaders.end()) &&
					(map_shaders.find(
						 shader_type_t::kShaderType_TessellationEvaluation) !=
						map_shaders.end()))
					result = true;

				return result;
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek