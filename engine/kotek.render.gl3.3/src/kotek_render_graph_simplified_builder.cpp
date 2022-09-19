#include "../include/kotek_render_graph_simplified_builder.h"
#include "../include/kotek_render_graph_simplified.h"
#include "../include/kotek_render_graph_simplified_render_pass.h"
#include "../include/kotek_render_graph_simplified_node.h"

#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_graph_simplified_resource_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderGraphSimplifiedBuilder::ktkRenderGraphSimplifiedBuilder(
				Core::ktkMainManager* p_main_manager) :
				m_render_graph_type{},
				m_rendering_pipeline_type{}, m_p_main_manager{p_main_manager},
				m_p_render_resource_manager{
					static_cast<ktkRenderResourceManager*>(
						m_p_main_manager->GetRenderResourceManager())},
				m_p_render_graph_simplified_resource_manager{}
			{
				KOTEK_ASSERT(this->m_p_main_manager,
					"you must pass a valid pointer of ktkMainManager instance");
			}

			ktkRenderGraphSimplifiedBuilder::~ktkRenderGraphSimplifiedBuilder(
				void)
			{
			}

			void ktkRenderGraphSimplifiedBuilder::Initialize(
				Core::ktkIRenderGraphResourceManager* p_resource_manager,
				const ktk::string& backbuffer_name,
				const gl::eRenderGraphBuilderType& render_graph_type_id,
				const gl::eRenderGraphBuilderPipelineRenderingType&
					rendering_pipeline_type)
			{
				KOTEK_ASSERT(p_resource_manager,
					"you can't pass an invalid pointer of resource manager");

				KOTEK_ASSERT(backbuffer_name.empty() == false,
					"you can't pass an empty string for backbuffer name");

				this->m_backbuffer_name = backbuffer_name;
				this->m_render_graph_type = render_graph_type_id;
				this->m_rendering_pipeline_type = rendering_pipeline_type;

				p_resource_manager->Initialize(
					render_graph_type_id, rendering_pipeline_type);

				this->m_p_render_graph_simplified_resource_manager =
					static_cast<ktkRenderGraphSimplifiedResourceManager*>(
						p_resource_manager);
			}

			ktkRenderGraphSimplified ktkRenderGraphSimplifiedBuilder::Compile(
				void)
			{
				auto storage_inputs = this->Compile_Inputs();
				auto storage_outputs = this->Compile_Outputs();

				const ktk::vector<ktkRenderGraphSimplifiedNode>& nodes =
					this->Analyze(storage_inputs, storage_outputs);

				return ktkRenderGraphSimplified(this->m_passes, nodes);
			}

			bool ktkRenderGraphSimplifiedBuilder::Register_RenderPass(
				const ktk::string& render_pass_name,
				ktkRenderGraphSimplifiedRenderPass* p_pass) noexcept
			{
				KOTEK_ASSERT(render_pass_name.empty() == false,
					"you can't pass an empty name");

				KOTEK_ASSERT(p_pass,
					"you can't pass an empty pointer of "
					"ktkRenderGraphSimplifiedRenderPass instance");

				KOTEK_ASSERT(this->m_p_render_graph_simplified_resource_manager,
					"you must initialize it before registering render pass");

				if (p_pass)
				{
					p_pass->Set_Name(render_pass_name);
				}

				if (std::find_if(this->m_passes.begin(), this->m_passes.end(),
						[p_pass](
							ktkRenderGraphSimplifiedRenderPass* p_current_pass)
							-> bool {
							return p_current_pass->Get_Name() ==
								p_pass->Get_Name();
						}) != std::end(this->m_passes))
				{
					KOTEK_ASSERT(false,
						"render pass is already existed in storage! {}",
						render_pass_name.get_as_is());

					this->m_failed_passes_for_adding.push_back(p_pass);

					return false;
				}

				this->m_passes.push_back(p_pass);

				p_pass->Initialize(this->m_p_render_resource_manager,
					this->m_p_render_graph_simplified_resource_manager);

				return true;
			}

			const ktk::string&
			ktkRenderGraphSimplifiedBuilder::Get_BackBufferName(
				void) const noexcept
			{
				return this->m_backbuffer_name;
			}

			gl::eRenderGraphBuilderType
			ktkRenderGraphSimplifiedBuilder::Get_RenderGraphBuilderType(
				void) const noexcept
			{
				return this->m_render_graph_type;
			}

			gl::eRenderGraphBuilderPipelineRenderingType
			ktkRenderGraphSimplifiedBuilder::
				Get_RenderGraphPipelineRenderingType(void) const noexcept
			{
				return this->m_rendering_pipeline_type;
			}

			ktk::unordered_map<ktk::string,
				gl::ktkRenderGraphSimplifiedStorageInput>
			ktkRenderGraphSimplifiedBuilder::Compile_Inputs(void) noexcept
			{
				ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageInput>
					result;

				for (const auto& pass : this->m_passes)
				{
					gl::ktkRenderGraphSimplifiedStorageInput& storage =
						result[pass->Get_Name()];

					pass->OnSetupInput(storage,
						this->m_p_main_manager->getRenderDevice(),
						static_cast<Core::ktkFileSystem*>(
							this->m_p_main_manager->GetFileSystem()));
				}

				return result;
			}

			ktk::unordered_map<ktk::string,
				gl::ktkRenderGraphSimplifiedStorageOutput>
			ktkRenderGraphSimplifiedBuilder::Compile_Outputs(void) noexcept
			{
				ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageOutput>
					result;

				for (const auto& pass : this->m_passes)
				{
					gl::ktkRenderGraphSimplifiedStorageOutput& storage =
						result[pass->Get_Name()];

					pass->OnSetupOutput(
						storage, this->m_p_main_manager->getRenderDevice());
				}

				return result;
			}

			void ktkRenderGraphSimplifiedBuilder::
				Compile_BuffersAndImagesForCreation(
					const ktk::unordered_map<ktk::string,
						gl::ktkRenderGraphSimplifiedStorageInput>&
						storage_inputs,
					const ktk::unordered_map<ktk::string,
						gl::ktkRenderGraphSimplifiedStorageOutput>&
						storage_outputs,
					ktk::unordered_map<ktk::string,
						gl::ktkRenderGraphResourceInfo<
							gl::ktkRenderGraphTextureInfo>>& images_to_create,
					ktk::unordered_map<ktk::string,
						gl::ktkRenderGraphResourceInfo<
							gl::ktkRenderGraphBufferInfo>>&
						buffers_to_create) noexcept
			{
				KOTEK_ASSERT(images_to_create.empty(),
					"you can't pass a not empty storage here!");
				KOTEK_ASSERT(buffers_to_create.empty(),
					"you can't pass a not empty storage here!");

				bool is_current_output_has_inputs_image = false;
				bool is_current_output_has_inputs_buffer = false;
				bool is_current_output_has_inputs = false;

				for (const auto& p_pass : this->m_passes)
				{
					const ktk::string& render_pass_name = p_pass->Get_Name();

					const gl::ktkRenderGraphSimplifiedStorageOutput&
						storage_output = storage_outputs.at(render_pass_name);

					is_current_output_has_inputs_image =
						!(storage_inputs.at(render_pass_name)
								.Get_Images()
								.empty());

					is_current_output_has_inputs_buffer =
						!(storage_inputs.at(render_pass_name)
								.Get_Buffers()
								.empty());

					if (this->m_render_graph_type ==
						gl::eRenderGraphBuilderType::
							kRenderBuilderFor_Forward_Only)
					{
						KOTEK_ASSERT(storage_output.Empty(),
							"you can't create any outputs from render pass "
							"(e.g. render targets or attachments in frame "
							"buffer) because you have: {} and render pass[{}]",
							gl::helper::
								Translate_RenderGraphBuilderTypeToString(
									this->m_render_graph_type)
									.get_as_is(),
							render_pass_name.get_as_is());
					}

					for (const auto& [texture_name, info_create] :
						storage_output.Get_Images())
					{
						KOTEK_ASSERT(images_to_create.find(texture_name) ==
								images_to_create.end(),
							"you want ot create a texture which is already "
							"added: {}",
							texture_name.get_as_is());

						images_to_create[texture_name] = {
							render_pass_name, texture_name, info_create};
					}

					for (const auto& [buffer_name, info_create] :
						storage_output.Get_Buffers())
					{
						KOTEK_ASSERT(buffers_to_create.find(buffer_name) ==
								buffers_to_create.end(),
							"you want to create a buffer which is already "
							"added");

						buffers_to_create[buffer_name] = {
							render_pass_name, buffer_name, info_create};
					}

					if (is_current_output_has_inputs)
					{
						if (is_current_output_has_inputs_image)
						{
							for (const auto& [texture_name, info_create] :
								storage_inputs.at(render_pass_name)
									.Get_Images())
							{
								if (images_to_create.find(texture_name) ==
									images_to_create.end())
								{
									images_to_create[texture_name] = {
										render_pass_name, texture_name,
										info_create};

									// TODO: I guess we don't need
									// synchronization status here but anyway...
								}
								else
								{
									if (render_pass_name !=
										images_to_create.at(texture_name)
											.Get_RenderPassName())
									{
										// TODO: I guess we don't need
										// synchronization status here but
										// anyway...
									}
									else
									{
										KOTEK_ASSERT(false,
											"you can't use the same resource "
											"in both variant as input and "
											"output");
									}
								}
							}
						}

						if (is_current_output_has_inputs_buffer)
						{
							for (const auto& [buffer_name, info_create] :
								storage_inputs.at(render_pass_name)
									.Get_Buffers())
							{
								if (buffers_to_create.find(buffer_name) ==
									buffers_to_create.end())
								{
									buffers_to_create[buffer_name] = {
										render_pass_name, buffer_name,
										info_create};

									// TODO: I guess we don't need
									// synchronization status here but anyway...
								}
								else
								{
									if (render_pass_name !=
										buffers_to_create.at(buffer_name)
											.Get_RenderPassName())
									{
										// TODO: I guess we don't need
										// synchronization status here but
										// anyway...
									}
									else
									{
										KOTEK_ASSERT(false,
											"you can't use the same resource "
											"in both variant as input and "
											"output");
									}
								}
							}
						}
					}
				}
			}

			ktk::vector<ktkRenderGraphSimplifiedNode>
			ktkRenderGraphSimplifiedBuilder::Analyze(
				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageInput>& storage_inputs,
				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageOutput>& storage_outputs)
			{
				ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphResourceInfo<
						gl::ktkRenderGraphTextureInfo>>
					images_to_create;

				ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphResourceInfo<
						gl::ktkRenderGraphBufferInfo>>
					buffers_to_create;

				this->Compile_BuffersAndImagesForCreation(storage_inputs,
					storage_outputs, images_to_create, buffers_to_create);

				this->Create_Resources(storage_inputs);

				for (const auto& p_render_pass : this->m_passes)
				{
					p_render_pass->OnCreatedResources();
				}

				ktk::vector<ktkRenderGraphSimplifiedNode> result;

				for (const auto* p_render_pass : this->m_passes)
				{
					const ktk::string& render_pass_name =
						p_render_pass->Get_Name();

					result.push_back({render_pass_name,
						this->m_p_render_graph_simplified_resource_manager
							->Get_Storage_Programs()});
				}

				return result;
			}

			void ktkRenderGraphSimplifiedBuilder::Create_Resources(
				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageInput>&
					all_inputs) noexcept
			{
				this->Create_BackBuffer();
				this->Create_Shaders(all_inputs);
			}

			void ktkRenderGraphSimplifiedBuilder::Create_BackBuffer(
				void) noexcept
			{
				KOTEK_ASSERT(this->m_p_render_graph_simplified_resource_manager,
					"you must initialize simplified resource manager for "
					"render graph");
			}

			void ktkRenderGraphSimplifiedBuilder::Create_Shaders(
				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageInput>&
					all_inputs) noexcept
			{
				KOTEK_ASSERT(this->m_p_render_graph_simplified_resource_manager,
					"you must initialize simplified resource manager for "
					"render graph");

				for (const auto& [render_pass_name, storage_input] : all_inputs)
				{
					this->m_p_render_graph_simplified_resource_manager
						->Create_Shaders(storage_input);
				}
			}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek