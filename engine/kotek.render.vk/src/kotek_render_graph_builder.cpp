#include "../include/kotek_render_graph_builder.h"
#include <kotek.core/include/kotek_main_manager.h>
#include "../include/kotek_render_device.h"
#include "../include/kotek_render_graph.h"
#include "../include/kotek_render_graph_data_types.h"
#include "../include/kotek_render_graph_resource_manager.h"
#include "../include/kotek_render_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			ktkRenderGraphBuilder::ktkRenderGraphBuilder(
				Core::ktkMainManager& main_manager) :
				m_render_graph_type(eRenderGraphBuilderType::
						kRenderBuilderFor_Undefined),
				m_p_manager_render_resource(
					static_cast<ktkRenderResourceManager*>(
						main_manager.GetRenderResourceManager())),
				m_p_device(static_cast<ktkRenderDevice*>(
					main_manager.getRenderDevice())),
				m_p_profiler(main_manager.GetGameManager()->GetProfiler()),
				m_p_main_manager(&main_manager)
			{
			}

			ktkRenderGraphBuilder::~ktkRenderGraphBuilder(void)
			{
				// TODO: move this code to shutdown method and call it here
#ifdef KOTEK_DEBUG
				if (this->m_failed_add_passes.empty())
				{
					KOTEK_MESSAGE("There's no wrong passes which duplicates to "
								  "temporary. Good "
								  "to you user!");
				}
#endif

				for (auto& p_pass : this->m_failed_add_passes)
				{
#ifdef KOTEK_DEBUG
					KOTEK_MESSAGE("deleted failed passes {}",
						p_pass->GetName().get_as_is());
#endif

					KOTEK_ASSERT(
						p_pass, "can't be nullptr, impossible here!!!!");

					delete p_pass;
				}

				KOTEK_ASSERT(this->m_render_graph_type !=
						eRenderGraphBuilderType::
							kRenderBuilderFor_Undefined,
					"you didn't call initialize for this object");
			}

			void ktkRenderGraphBuilder::Initialize(
				ktkRenderGraphResourceManager* p_resource_manager,
				const ktk::string& backbuffer_name,
				const eRenderGraphBuilderType& render_graph_type_id,
				const eRenderGraphBuilderPipelineRenderingType&
					rendering_pipeline_type)
			{
				this->m_render_graph_type = render_graph_type_id;
				this->m_rendering_pipeline_type = rendering_pipeline_type;
				this->m_p_manager_render_graph_resource = p_resource_manager;
				this->m_backbuffer_name = backbuffer_name;

				KOTEK_ASSERT(backbuffer_name.empty() == false,
					"you must have valid (not empty) string for back buffer!");
				KOTEK_ASSERT(this->m_p_manager_render_graph_resource,
					"you must pass a valid resource manager of render graph");
				KOTEK_ASSERT(this->m_p_manager_render_resource,
					"you must pass a valid resource manager pointer");
				KOTEK_ASSERT(this->m_p_device,
					"you must pass a valid device manager pointer");

				this->m_p_manager_render_graph_resource->Initialize(
					this->m_render_graph_type, this->m_rendering_pipeline_type);
			}

			void ktkRenderGraphBuilder::Shutdown(void) {}

			ktk::unordered_map<ktk::string, ktkRenderGraphStorageInput>
			ktkRenderGraphBuilder::CompileInputs(void) noexcept
			{
				ktk::unordered_map<ktk::string,
					ktkRenderGraphStorageInput>
					result;

				for (const auto& pass : this->m_temporary_storage_render_passes)
				{
					ktkRenderGraphStorageInput& storage =
						result[pass->GetName()];

					pass->OnSetupInput(storage, this->m_p_device,
						this->m_p_main_manager->GetFileSystem());
				}

				return result;
			}

			ktk::unordered_map<ktk::string, ktkRenderGraphStorageOutput>
			ktkRenderGraphBuilder::CompileOutputs(void) noexcept
			{
				ktk::unordered_map<ktk::string,
					ktkRenderGraphStorageOutput>
					result;

				for (const auto& pass : this->m_temporary_storage_render_passes)
				{
					ktkRenderGraphStorageOutput& storage =
						result[pass->GetName()];

					pass->OnSetupOutput(storage, this->m_p_device);
				}

				return result;
			}

			void ktkRenderGraphBuilder::CompileInput(
				const ktkRenderGraphStorageInput& storage) noexcept
			{
			}

			ktk::vector<ktkRenderGraphNode> ktkRenderGraphBuilder::Analyze(
				const ktk::unordered_map<ktk::string,
					ktkRenderGraphStorageInput>& input_storage,
				const ktk::unordered_map<ktk::string,
					ktkRenderGraphStorageOutput>& output_storage) noexcept
			{
				KOTEK_CPU_PROFILE();

				bool is_current_output_has_inputs_image = false;
				bool is_current_output_has_inputs_buffer = false;
				bool is_current_output_has_inputs =
					(is_current_output_has_inputs_buffer ||
						is_current_output_has_inputs_image);

				ktk::unordered_map<ktk::string,
					ktkRenderGraphResourceInfo<
						ktkRenderTextureInfo>>
					image_to_create;

				ktk::unordered_map<ktk::string,
					ktkRenderGraphResourceInfo<VkBufferCreateInfo>>
					buffer_to_create;

				for (const auto& p_pass :
					this->m_temporary_storage_render_passes)
				{
					const auto& render_pass_name = p_pass->GetName();
					const auto& output_data =
						output_storage.at(render_pass_name);

					is_current_output_has_inputs_image = !(
						input_storage.at(render_pass_name).GetImages().empty());
					is_current_output_has_inputs_buffer =
						!(input_storage.at(render_pass_name)
								.GetBuffers()
								.empty());

					is_current_output_has_inputs =
						(is_current_output_has_inputs_buffer ||
							is_current_output_has_inputs_image);

					if (this->m_render_graph_type ==
						eRenderGraphBuilderType::
							kRenderBuilderFor_Forward_Only)
					{
						KOTEK_ASSERT(output_data.Empty(),
							"you can't create any outputs from render pass "
							"(e.g. render targets "
							"or attachments in frame buffer) because you have: "
							"{} and render "
							"pass[{}]",
							helper::TranslateRenderGraphBuilderTypeToString(
								this->m_render_graph_type)
								.get_as_is(),
							render_pass_name.get_as_is());
					}

					for (const auto& [texture_name, info_create] :
						output_data.GetImages())
					{
						if (image_to_create.find(texture_name) !=
							image_to_create.end())
						{
							KOTEK_ASSERT(false,
								"you want to create a texture which is already "
								"added");
						}

						image_to_create[texture_name] = {
							render_pass_name, texture_name, info_create};
					}

					for (const auto& [buffer_name, info_create] :
						output_data.GetBuffers())
					{
						KOTEK_ASSERT(buffer_to_create.find(buffer_name) ==
								buffer_to_create.end(),
							"you want to create a buffer which is alread "
							"added");

						buffer_to_create[buffer_name] = {
							render_pass_name, buffer_name, info_create};
					}

					if (is_current_output_has_inputs)
					{
						if (is_current_output_has_inputs_image)
						{
							for (const auto& [texture_name, info_create] :
								input_storage.at(render_pass_name).GetImages())
							{
								if (image_to_create.find(texture_name) ==
									image_to_create.end())
								{
									image_to_create[texture_name] = {
										render_pass_name, texture_name,
										info_create};

									image_to_create.at(texture_name)
										.SetStatus(
											eResourceSynchronizationStatus::
												kToInputOnly);
								}
								else
								{
									if (render_pass_name !=
										image_to_create.at(texture_name)
											.GetRenderPassName())
									{
										KOTEK_ASSERT(
											image_to_create.at(texture_name)
													.GetStatus() ==
												eResourceSynchronizationStatus::
													kEmpty,
											"you can't specify status "
											"synchronization when you "
											"just create texture in output, "
											"because input might "
											"contain cetrain information about "
											"sync process");

										image_to_create.at(texture_name)
											.SetStatus(
												eResourceSynchronizationStatus::
													kFromOutputToInput);
									}
									else
									{
										KOTEK_ASSERT(false,
											"you can't use the same resource "
											"in both "
											"variant as input and output");
									}
								}
							}
						}

						if (is_current_output_has_inputs_buffer)
						{
							for (const auto& [buffer_name, info_create] :
								input_storage.at(render_pass_name).GetBuffers())
							{
								if (buffer_to_create.find(buffer_name) ==
									buffer_to_create.end())
								{
									buffer_to_create[buffer_name] = {
										render_pass_name, buffer_name,
										info_create};

									// TODO: I really need this or there's
									// something else option needs to be ???
									buffer_to_create.at(buffer_name)
										.SetStatus(
											eResourceSynchronizationStatus::
												kToInputOnly);
								}
								else
								{
									if (render_pass_name !=
										buffer_to_create.at(buffer_name)
											.GetRenderPassName())
									{
										KOTEK_ASSERT(
											buffer_to_create.at(buffer_name)
													.GetStatus() ==
												eResourceSynchronizationStatus::
													kEmpty,
											"you can't specify status "
											"synchronization when you "
											"just create texture in output, "
											"because input might "
											"contain cetrain information about "
											"sync process");

										buffer_to_create.at(buffer_name)
											.SetStatus(
												eResourceSynchronizationStatus::
													kFromOutputToInput);
									}
									else
									{
										KOTEK_ASSERT(false,
											"you can't use the same resource "
											"in both "
											"variant as input and output");
									}
								}
							}
						}
					}
				}

				this->CreateBackBuffer();
				this->CreateTexturesAndBuffers(
					image_to_create, buffer_to_create);
				this->CreateShadersAndLayouts(input_storage);
				this->CreateSynchronizationPrimitivesAndRenderPass(
					input_storage, output_storage, image_to_create,
					buffer_to_create);

				for (const auto& p_render_pass :
					this->m_temporary_storage_render_passes)
				{
					p_render_pass->OnCreatedResources();
				}

				ktk::vector<ktkRenderGraphNode> nodes;

				for (const auto* p_render_pass :
					this->m_temporary_storage_render_passes)
				{
					const ktk::string& render_pass_name =
						p_render_pass->GetName();

					const auto& storage_input =
						input_storage.at(render_pass_name);
					const auto& storage_output =
						output_storage.at(render_pass_name);

					VkRenderPass p_pass =
						this->m_p_manager_render_graph_resource->GetRenderPass(
							render_pass_name);
					
					bool is_use_backbuffer = storage_output.IsUseBackBuffer();
					
					VkFramebuffer p_framebuffer = is_use_backbuffer ?
						this->m_p_manager_render_graph_resource->GetFrameBuffer(
							render_pass_name) : nullptr;

					KOTEK_ASSERT(p_pass,
						"you contain an invalid pointer of VkRenderPass. Can't "
						"be");

					if (is_use_backbuffer) {
						KOTEK_ASSERT(p_framebuffer,
							"you contain an invalid pointer of VkFramebuffer. "
							"Can't be");
					}


					ktk::unordered_map<ktk::string, VkPipeline> pipelines;
					ktk::unordered_map<ktk::string,
						ktk::vector<VkDescriptorSet>>
						descriptor_sets;
					ktk::unordered_map<ktk::string, VkPipelineLayout>
						pipelines_layout;

					for (const auto& [pipeline_name, info] :
						storage_input.GetPipelinesInfo())
					{
						VkPipeline p_pipeline =
							this->m_p_manager_render_graph_resource
								->GetPipeline(pipeline_name);

						KOTEK_ASSERT(p_pipeline,
							"you have an invalid pointer of VkPipeline in your "
							"Resource manager of render graph");

						pipelines[pipeline_name] = p_pipeline;

						const auto& sets =
							this->m_p_manager_render_graph_resource
								->GetDescriptorSets(pipeline_name);

						if (sets.empty() == false)
							descriptor_sets[pipeline_name] = sets;

						VkPipelineLayout p_pipeline_layout =
							this->m_p_manager_render_graph_resource
								->GetPipelineLayout(pipeline_name);

						KOTEK_ASSERT(p_pipeline_layout,
							"you have an invalid pointer of VkPipelineLayout "
							"in your render graph resource manager, it can't "
							"be check your initialized data and debug it!");

						pipelines_layout[pipeline_name] = p_pipeline_layout;
					}

					nodes.push_back({render_pass_name, p_pass, p_framebuffer,
						pipelines, descriptor_sets, pipelines_layout});
				}

				return nodes;
			}

			void ktkRenderGraphBuilder::CreateBackBuffer(void) noexcept
			{
				this->m_p_manager_render_graph_resource->CreateBackBuffer(
					this->m_backbuffer_name);
			}

			void ktkRenderGraphBuilder::CreateTexturesAndBuffers(
				const ktk::unordered_map<ktk::string,
					ktkRenderGraphResourceInfo<
						ktkRenderTextureInfo>>& images,
				const ktk::unordered_map<ktk::string,
					ktkRenderGraphResourceInfo<VkBufferCreateInfo>>&
					buffers) noexcept
			{
				KOTEK_CPU_PROFILE();

				if (images.empty()) 
				{
					KOTEK_MESSAGE_WARNING(
						"you have empty images for creation for render");
					return;
				}


				for (const auto& [render_pass_name, image_info] : images)
				{
					this->m_p_manager_render_graph_resource->CreateTexture(
						image_info);
				}

				// TODO: create buffers here too
			}

			void ktkRenderGraphBuilder::CreateShadersAndLayouts(
				const ktk::unordered_map<ktk::string,
					ktkRenderGraphStorageInput>& storages) noexcept
			{
				KOTEK_ASSERT(storages.empty() == false,
					"you must add one render pass at least");

				for (const auto& [render_pass_name, storage_input] : storages)
				{
					if (storage_input.GetShaders().empty())
					{
						KOTEK_MESSAGE_WARNING(
							"you use render pass without shaders means you "
						    "must not have pipeline for render pass: {}", render_pass_name.get_as_is());
						return;
					}

					this->ValidateShaders(storage_input.GetShaders());

					this->m_p_manager_render_graph_resource
						->CreateShadersAndLayoutsWithDescriptorSets(
							storage_input);
				}
			}

			void ktkRenderGraphBuilder::
				CreateSynchronizationPrimitivesAndRenderPass(
					const ktk::unordered_map<ktk::render_pass_id_t,
						ktkRenderGraphStorageInput>& input_storage,
					const ktk::unordered_map<ktk::render_pass_id_t,
						ktkRenderGraphStorageOutput>& output_storage,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<
							ktkRenderTextureInfo>>& images,
					const ktk::unordered_map<ktk::string,
						ktkRenderGraphResourceInfo<VkBufferCreateInfo>>&
						buffers) noexcept
			{
				for (const auto& [render_pass_name, storage_input] :
					input_storage)
				{
					this->m_p_manager_render_graph_resource
						->CreateSynchronizationPrimitivesAndRenderPass(
							render_pass_name, storage_input,
							output_storage.at(render_pass_name), images,
							buffers);
				}
			}

			void ktkRenderGraphBuilder::ValidateShaders(
				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<shader_type_t, shader_loading_data_t>>&
					input_shaders) noexcept
			{
				switch (this->m_rendering_pipeline_type)
				{
				case eRenderGraphBuilderPipelineRenderingType::
					kRenderBuilderBasedOnPipeline_Orthodox:
				{
					for (const auto& [pipeline_name, map_type_and_data] :
						input_shaders)
					{
						KOTEK_ASSERT(map_type_and_data.empty() == false,
							"you must pass valid shaders to general map. So "
							"you don't "
							"have shaders for pipeline: [{}]",
							pipeline_name.get_as_is());

						KOTEK_ASSERT(map_type_and_data.size() >= 2,
							"it doesn't make a sense you must have vertex and "
							"pixel "
							"(fragment) shaders at least.");

						for (const auto& [shader_type, shader_data] :
							map_type_and_data)
						{
							KOTEK_ASSERT(
								helper::isRTXShaderByType(shader_type) == false,
								"you can't have RTX shaders map based on "
								"shader file paths "
								"in Orthodox pipeline (pipeline which is not "
								"RTX)");
						}
					}
					break;
				}
				case eRenderGraphBuilderPipelineRenderingType::
					kRenderBuilderBasedOnPipeline_RTX:
				{
					KOTEK_ASSERT(false,
						"this engine version doesn't support RTX at all!");

					break;
				}
				}
			}

			void ktkRenderGraphBuilder::CreateBarriers(void) noexcept
			{
				KOTEK_CPU_PROFILE();

				for (const auto& [render_pass_name, map_textures] :
					this->m_p_manager_render_graph_resource
						->GetRenderGraph_RenderPasses_Textures())
				{
					for (const auto& [texture_name, texture] : map_textures) {}
				}
			}

			ktkRenderGraph ktkRenderGraphBuilder::Compile(void)
			{
				KOTEK_ASSERT(this->m_render_graph_type !=
						eRenderGraphBuilderType::
							kRenderBuilderFor_Undefined,
					"you didn't call initialize for this object");

				auto storage_inputs = this->CompileInputs();
				auto storage_outputs = this->CompileOutputs();

				const auto& nodes =
					this->Analyze(storage_inputs, storage_outputs);

				this->m_p_manager_render_resource->uploadAllResourcesToGPU();

				auto* p_command_list_ring =
					new Kotek::Render::vk::kotek_render_command_list_ring();

				p_command_list_ring->initialize(this->m_p_device,
					Kotek::Render::vk::_kSwapchainBackBuffers, nodes.size());

				return ktkRenderGraph(
					this->m_temporary_storage_render_passes, nodes,
					p_command_list_ring,
					this->m_p_device,
					this->m_p_profiler);
			}

			bool ktkRenderGraphBuilder::RegisterRenderPass(
				const ktk::string& render_pass_name,
				ktkRenderGraphRenderPass* p_pass) noexcept
			{
				KOTEK_ASSERT(p_pass != nullptr, "you must pass a valid object");
				KOTEK_ASSERT(render_pass_name.empty() == false,
					"you can't register render pass with empty name");

				p_pass->SetName(render_pass_name);

				if (std::find_if(
						this->m_temporary_storage_render_passes.begin(),
						this->m_temporary_storage_render_passes.end(),
						[p_pass](
							ktkRenderGraphRenderPass* p_object) -> bool {
							return p_object->GetName() == p_pass->GetName();
						}) != std::end(this->m_temporary_storage_render_passes))
				{
					KOTEK_ASSERT(false,
						"render pass is already existed in map! {}",
						render_pass_name.get_as_is());

					this->m_failed_add_passes.push_back(p_pass);

					return false;
				}

				this->m_temporary_storage_render_passes.push_back(p_pass);

				p_pass->Initialize(this->m_p_manager_render_resource,
					this->m_p_manager_render_graph_resource);

				return true;
			}

			const ktk::string& ktkRenderGraphBuilder::GetBackBufferName(
				void) const noexcept
			{
				return this->m_backbuffer_name;
			}

			eRenderGraphBuilderType
			ktkRenderGraphBuilder::GetRenderGraphBuilderType(
				void) const noexcept
			{
				return this->m_render_graph_type;
			}

			eRenderGraphBuilderPipelineRenderingType
			ktkRenderGraphBuilder::GetRenderGraphPipelineRenderingType(
				void) const noexcept
			{
				return this->m_rendering_pipeline_type;
			}

		} // namespace vk
	}     // namespace Render
} // namespace Kotek