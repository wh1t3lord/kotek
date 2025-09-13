#include "../include/kotek_render_graph_simplified_render_pass.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

ktkRenderGraphSimplifiedRenderPass::ktkRenderGraphSimplifiedRenderPass(
	const kun_ktk u8string_view& name) :
	m_p_manager_main{}, m_p_manager_resource{}
#ifdef KOTEK_DEBUG
	,
	m_name{reinterpret_cast<const char*>(name.data())}
#endif
{
}

ktkRenderGraphSimplifiedRenderPass::ktkRenderGraphSimplifiedRenderPass(void) :
	m_p_manager_main{}, m_p_manager_resource{}
{
}

void ktkRenderGraphSimplifiedRenderPass::OnCreateResources(
	kun_core ktkMainManager* p_manager_main,
	kun_core ktkIRenderResourceManager* p_manager_resource)
{
	KOTEK_ASSERT(false,
		"you forgot to overload! Always provide implementation in child class");
}

void ktkRenderGraphSimplifiedRenderPass::OnDestroyResources() {}

void ktkRenderGraphSimplifiedRenderPass::OnUpdate(
	const ktkRenderGraphSimplifiedRenderPass* p_previous_pass)
{
}

void ktkRenderGraphSimplifiedRenderPass::OnRender(
	const ktkRenderGraphSimplifiedRenderPass* p_previous_pass)
{
}

const char* ktkRenderGraphSimplifiedRenderPass::Get_Name(void) const noexcept
{
#ifdef KOTEK_DEBUG
	return this->m_name.c_str();
#else
	return nullptr;
#endif
}

void ktkRenderGraphSimplifiedRenderPass::Initialize(
	kun_core ktkMainManager* p_manager_main,
	kun_core ktkIRenderResourceManager* p_manager_resource) noexcept
{
	KOTEK_ASSERT(p_manager_resource,
		"you can't pass an invalid resource manager pointer");
	KOTEK_ASSERT(p_manager_main,
		"you must pass ktkMainManager* instance as valid pointer!");

	this->m_p_manager_main = p_manager_main;
	this->m_p_manager_resource = p_manager_resource;
}

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK