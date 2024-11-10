#include "../include/kotek_render_graph_simplified.h"
#include "../include/kotek_render_graph_simplified_render_pass.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkRenderGraphSimplified::ktkRenderGraphSimplified(void) {}
ktkRenderGraphSimplified::~ktkRenderGraphSimplified(void) {}

void ktkRenderGraphSimplified::Add_Pass(
	ktkRenderGraphSimplifiedRenderPass* p_allocated_pass)
{
	KOTEK_ASSERT(p_allocated_pass, "you can't pass an invalid pointer!");

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("registered pass: [{}]", p_allocated_pass->Get_Name());
#endif

	this->m_passes.push_back(p_allocated_pass);
}

void ktkRenderGraphSimplified::Initialize(
	kun_core ktkMainManager* p_main_manager,
	kun_core ktkIRenderResourceManager* p_resource_render_manager)
{
	KOTEK_ASSERT(this->m_passes.empty() == false,
		"did you add your passes through Add_Pass method?");
	KOTEK_ASSERT(p_main_manager, "must be a valid pointer!");
	KOTEK_ASSERT(p_resource_render_manager, "must be a valid pointer!");

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("max passes for simplified render graph: {}",
		this->m_passes.max_size());
	KOTEK_MESSAGE("total registered passes: {}", this->m_passes.size());
#endif

	for (ktkRenderGraphSimplifiedRenderPass* p_pass : this->m_passes)
	{
		if (p_pass)
		{
			p_pass->Initialize(p_main_manager, p_resource_render_manager);
			p_pass->OnCreateResources(
				p_main_manager, p_resource_render_manager);
		}
	}
}

void ktkRenderGraphSimplified::Shutdown(void)
{
	for (auto* p_pass : this->m_passes)
	{
#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("Deleting render pass {}",
			reinterpret_cast<const char*>(p_pass->Get_Name()));
#endif

		delete p_pass;
		p_pass = nullptr;
	}

	this->m_passes.clear();
}

void ktkRenderGraphSimplified::Update_All(void)
{
	ktkRenderGraphSimplifiedRenderPass* p_previous_pass{};
	for (ktkRenderGraphSimplifiedRenderPass* p_pass : this->m_passes)
	{
		if (p_pass)
		{
			p_pass->OnUpdate(p_previous_pass);
		}

		p_previous_pass = p_pass;
	}
}

void ktkRenderGraphSimplified::Render_All(void)
{
	ktkRenderGraphSimplifiedRenderPass* p_previous_pass{};

	for (ktkRenderGraphSimplifiedRenderPass* p_pass : this->m_passes)
	{
		if (p_pass)
		{
			p_pass->OnRender(p_previous_pass);
		}

		p_previous_pass = p_pass;
	}
}

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
