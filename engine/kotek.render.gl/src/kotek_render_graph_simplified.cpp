#include "../include/kotek_render_graph_simplified.h"
#include "../include/kotek_render_graph_simplified_render_pass.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkRenderGraphSimplified::ktkRenderGraphSimplified(void) : m_is_initialized{} {}
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

void ktkRenderGraphSimplified::Add_Passes(
	const ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
		KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>& passes)
{
	KOTEK_ASSERT(passes.empty(),
		"passing empty vector it is not supposed to be, at least just add "
	    "present pass!");

	this->m_passes = passes;
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

	this->m_is_initialized = true;
}

void ktkRenderGraphSimplified::Initialize(
	kun_core ktkMainManager* p_main_manager,
	kun_core ktkIRenderResourceManager* p_resource_render_manager,
	ktkRenderGraphSimplifiedRenderPass** p_passes, kun_ktk uint16_t count)
{
	KOTEK_ASSERT(p_passes, "must be valid array of passes!");
	KOTEK_ASSERT(
		count < KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT,
		"too much passes!");

	if (this->m_passes.empty() == false)
	{
#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE_WARNING(
			"previous storage wasn't empty, so deleting it...");
#endif

		this->Shutdown();
	}

	for (kun_ktk uint16_t i = 0; i < count; ++i)
	{
		ktkRenderGraphSimplifiedRenderPass* p_pass = p_passes[i];
		KOTEK_ASSERT(p_pass, "must be valid pointer!");
		if (p_pass)
		{
			p_pass->Initialize(p_main_manager, p_resource_render_manager);
			p_pass->OnCreateResources(
				p_main_manager, p_resource_render_manager);

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("added render pass: {}", p_pass->Get_Name());
#endif

			this->m_passes.push_back(p_pass);
		}
	}

	this->m_is_initialized = true;
}

void ktkRenderGraphSimplified::Initialize(
	kun_core ktkMainManager* p_main_manager,
	kun_core ktkIRenderResourceManager* p_resource_render_manager,
	ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
		KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>& passes)
{
	KOTEK_ASSERT(
		passes.empty() == false, "you need to pass not empty array of passes!");

	this->Initialize(p_main_manager, p_resource_render_manager, passes.data(),
		passes.size());
}

const ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
	KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>&
ktkRenderGraphSimplified::Get_Passes(void) const noexcept
{
	return this->m_passes;
}

ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
	KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>&
ktkRenderGraphSimplified::Get_Passes(void) noexcept
{
	return this->m_passes;
}


bool ktkRenderGraphSimplified::Is_Initialized(void) const noexcept
{
	return this->m_is_initialized;
}

void ktkRenderGraphSimplified::Shutdown(void)
{
	for (auto* p_pass : this->m_passes)
	{
		if (p_pass)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("Deleting render pass {}",
				reinterpret_cast<const char*>(p_pass->Get_Name()));
#endif
			p_pass->OnDestroyResources();
			delete p_pass;
			p_pass = nullptr;
		}
	}

	this->m_passes.clear();

	this->m_is_initialized = false;
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
