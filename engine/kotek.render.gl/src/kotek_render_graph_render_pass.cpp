#include "kotek_render_graph_render_pass.h"
#include "../kotek.core/kotek_filesystem.h"
#include "kotek_render_graph_resource_manager.h"
#include "kotek_render_graph_types_input.h"
#include "kotek_render_graph_types_output.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphRenderPass::ktkRenderGraphRenderPass(void) :
				m_p_manager_resource_graph{}, m_p_manager_resource{}
			{
			}

			void ktkRenderGraphRenderPass::OnSetupInput(
				ktkRenderGraphStorageInput& storage, ktkRenderDevice* p_device,
				Core::ktkFileSystem* p_file_system)
			{
			}

			void ktkRenderGraphRenderPass::OnSetupOutput(
				ktkRenderGraphStorageOutput& storage, ktkRenderDevice* p_device)
			{
			}

			void ktkRenderGraphRenderPass::OnCreatedResources(void) {}

			void ktkRenderGraphRenderPass::OnUpdate() {}

			void ktkRenderGraphRenderPass::OnRender(
				const ktkRenderGraphNode& node)
			{
			}

			void ktkRenderGraphRenderPass::SetName(
				const ktk::string& name) noexcept
			{
				KOTEK_ASSERT(name.empty() == false,
					"you can't set an empty name for this structure, you "
					"must "
					"specify your name rationally");

				this->m_name = name;
			}

			const ktk::string& ktkRenderGraphRenderPass::GetName(
				void) const noexcept
			{
				return this->m_name;
			}

			void ktkRenderGraphRenderPass::Initialize(
				ktkRenderResourceManager* p_manager_resource,
				ktkRenderGraphResourceManager*
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