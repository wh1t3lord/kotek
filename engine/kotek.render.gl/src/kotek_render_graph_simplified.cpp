#include "../include/kotek_render_graph_simplified.h"
#include "../include/kotek_render_graph_simplified_render_pass.h"
#include "../include/kotek_render_graph_simplified_node.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderGraphSimplified::ktkRenderGraphSimplified(
		const ktk::vector<ktkRenderGraphSimplifiedRenderPass*>& passes,
		const ktk::vector<ktkRenderGraphSimplifiedNode>& nodes) :
		m_passes{passes},
		m_nodes{nodes}
	{
	}
	ktkRenderGraphSimplified::ktkRenderGraphSimplified(void) {}
	ktkRenderGraphSimplified::~ktkRenderGraphSimplified(void) {}

	void ktkRenderGraphSimplified::Initialize(void) {}

	void ktkRenderGraphSimplified::Shutdown(void)
	{
		for (auto* p_pass : this->m_passes)
		{
#ifdef KOTEK_DEBUG
            KOTEK_MESSAGE("Deleting render pass {}",
                reinterpret_cast<const char*>(p_pass->Get_Name().c_str()));
#endif

			delete p_pass;
			p_pass = nullptr;
		}

		this->m_passes.clear();
	}

	void ktkRenderGraphSimplified::Update_All(void)
	{
		for (auto* p_pass : this->m_passes)
		{
			p_pass->OnUpdate();
		}
	}

	void ktkRenderGraphSimplified::Render_All(void)
	{
		ktk::size_t index = 0;

		for (auto*& p_pass : this->m_passes)
		{
			p_pass->OnRender(this->m_nodes.at(index));
			++index;
		}
	}
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
