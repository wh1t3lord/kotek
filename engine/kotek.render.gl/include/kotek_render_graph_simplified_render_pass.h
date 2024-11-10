#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkIRenderDevice;
class ktkIRenderResourceManager;
class ktkFileSystem;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

class ktkRenderGraphSimplifiedRenderPass
{
public:
	ktkRenderGraphSimplifiedRenderPass(const kun_ktk u8string_view& name);
	ktkRenderGraphSimplifiedRenderPass(void);
	virtual ~ktkRenderGraphSimplifiedRenderPass(void) = default;

	void Initialize(kun_core ktkMainManager* p_manager_main,
		kun_core ktkIRenderResourceManager* p_manager_resource) noexcept;

	virtual void OnCreateResources(kun_core ktkMainManager* p_manager_main,
		kun_core ktkIRenderResourceManager* p_manager_resource);
	virtual void OnUpdate(
		const ktkRenderGraphSimplifiedRenderPass* p_previous_pass);
	virtual void OnRender(
		const ktkRenderGraphSimplifiedRenderPass* p_previous_pass);

	const char* Get_Name(void) const noexcept;

protected:
	kun_core ktkMainManager* m_p_manager_main;
	kun_core ktkIRenderResourceManager* m_p_manager_resource;

private:
#ifdef KOTEK_DEBUG
	kun_ktk static_cstring<32> m_name;
#endif
};
KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK