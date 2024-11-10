#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_CORE
class ktkIRenderGraph;
class ktkIRenderResourceManager;
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL
class ktkRenderGraphSimplifiedRenderPass;
KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

class ktkRenderGraphSimplified : public kun_core ktkIRenderGraph
{
public:
	ktkRenderGraphSimplified(void);
	~ktkRenderGraphSimplified(void);

	void Add_Pass(ktkRenderGraphSimplifiedRenderPass* p_allocated_pass);

	void Initialize(kun_core ktkMainManager* p_main_manager,
		kun_core ktkIRenderResourceManager* p_resource_render_manager) override;
	void Shutdown(void) override;

	void Update_All(void);
	void Render_All(void);

private:
	// TODO: make a constant for pre-allocating passes
	kun_ktk static_vector<ktkRenderGraphSimplifiedRenderPass*, 32> m_passes;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
