#include "../include/kotek_render_graph_simplified_render_pass.h"
#include "../include/kotek_render_graph_simplified_types_input.h"
#include "../include/kotek_render_graph_simplified_types_output.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphSimplifiedRenderPass::
				ktkRenderGraphSimplifiedRenderPass(void) :
				m_p_manager_resource_graph{},
				m_p_manager_resource{}
			{
			}

			void ktkRenderGraphSimplifiedRenderPass::OnSetupInput(
				gl::ktkRenderGraphSimplifiedStorageInput& storage,
				Core::ktkIRenderDevice* p_device,
				Core::ktkFileSystem* p_file_system)
			{
			}

			void ktkRenderGraphSimplifiedRenderPass::OnSetupOutput(
				gl::ktkRenderGraphSimplifiedStorageOutput& storage,
				Core::ktkIRenderDevice* p_device)
			{
			}

			void ktkRenderGraphSimplifiedRenderPass::OnCreatedResources(void) {}

			void ktkRenderGraphSimplifiedRenderPass::OnUpdate() {}

			void ktkRenderGraphSimplifiedRenderPass::OnRender(
				const gl::ktkRenderGraphSimplifiedNode& node)
			{
			}

			void ktkRenderGraphSimplifiedRenderPass::SetName(
				const ktk::string& name) noexcept
			{
				KOTEK_ASSERT(name.empty() == false,
					"you can't set an empty name for this structure, you "
					"must "
					"specify your name rationally");

				this->m_name = name;
			}

			const ktk::string& ktkRenderGraphSimplifiedRenderPass::GetName(
				void) const noexcept
			{
				return this->m_name;
			}

			void ktkRenderGraphSimplifiedRenderPass::Initialize(
				Core::ktkIRenderResourceManager* p_manager_resource,
				Core::ktkIRenderGraphResourceManager*
					p_manager_resource_graph) noexcept
			{
				KOTEK_ASSERT(p_manager_resource,
					"you can't pass an invalid resource manager pointer");
				KOTEK_ASSERT(p_manager_resource_graph,
					"you can't pass an invalid resource graph manager "
					"pointer");

				this->m_p_manager_resource = p_manager_resource;
				this->m_p_manager_resource_graph = p_manager_resource_graph;
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek