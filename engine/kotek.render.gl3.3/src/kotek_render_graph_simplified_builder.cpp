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

				return ktkRenderGraphSimplified();
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

			ktk::vector<ktkRenderGraphSimplifiedNode>
			ktkRenderGraphSimplifiedBuilder::Analyze(
				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageInput>& storage_inputs,
				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphSimplifiedStorageOutput>& storage_outputs)
			{
				bool is_current_output_has_inputs_image = false;
				bool is_current_output_has_inputs_buffer = false;
				bool is_current_output_has_inputs = false;

				ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>
					image_to_create;

				ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>
					buffer_to_create;

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
									this->m_render_graph_type),
							render_pass_name.get_as_is());
					}
				}

				return ktk::vector<ktkRenderGraphSimplifiedNode>();
			}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek