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

static_assert(KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT <
		std::numeric_limits<kun_ktk uint16_t>::max(),
	"are you sure that you really need a such amount of passes?");

class ktkRenderGraphSimplified : public kun_core ktkIRenderGraph
{
public:
	ktkRenderGraphSimplified(void);
	~ktkRenderGraphSimplified(void);

	void Add_Pass(ktkRenderGraphSimplifiedRenderPass* p_allocated_pass);
	void Add_Passes(const ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
		KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>& passes);

	void Initialize(kun_core ktkMainManager* p_main_manager,
		kun_core ktkIRenderResourceManager* p_resource_render_manager) override;
	void Initialize(kun_core ktkMainManager* p_main_manager,
		kun_core ktkIRenderResourceManager* p_resource_render_manager,
		ktkRenderGraphSimplifiedRenderPass** p_passes, kun_ktk uint16_t count);
	void Initialize(kun_core ktkMainManager* p_main_manager,
		kun_core ktkIRenderResourceManager* p_resource_render_manager,
		ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
			KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>&
			passes);

	const ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
		KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>&
	Get_Passes(void) const noexcept;

	ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
		KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>&
	Get_Passes(void) noexcept;

	bool Is_Initialized(void) const noexcept override;
	void Shutdown(void) override;

	void Update_All(void);
	void Render_All(void);

private:
	bool m_is_initialized;
	// TODO: make a constant for pre-allocating passes
	ktk_vector<ktkRenderGraphSimplifiedRenderPass*,
		KOTEK_DEF_RENDER_GL_RENDER_GRAPH_SIMPLIFIED_MAX_PASS_COUNT>
		m_passes;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
