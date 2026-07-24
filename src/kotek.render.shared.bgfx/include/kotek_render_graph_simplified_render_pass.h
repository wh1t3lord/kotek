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
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

class ktkRenderGraphSimplifiedRenderPass
{
public:
	ktkRenderGraphSimplifiedRenderPass(void);
	virtual ~ktkRenderGraphSimplifiedRenderPass(void) = default;

	void Initialize(kun_core ktkMainManager* p_manager_main,
		kun_core ktkIRenderResourceManager* p_manager_resource) noexcept;

	virtual void OnCreateResources(kun_core ktkMainManager* p_manager_main,
		kun_core ktkIRenderResourceManager* p_manager_resource);
	virtual void OnDestroyResources();
	virtual void OnUpdate(
		const ktkRenderGraphSimplifiedRenderPass* p_previous_pass, kun_ktk uint32_t my_id_in_queue);
	virtual void OnRender(
		const ktkRenderGraphSimplifiedRenderPass* p_previous_pass, kun_ktk uint32_t my_id_in_queue);

	void Set_Name(static_cstring_t<32>& debug_name);
	const char* Get_Name(void) const noexcept;

protected:
	kun_core ktkMainManager* m_p_manager_main;
	kun_core ktkIRenderResourceManager* m_p_manager_resource;

private:
#ifdef KOTEK_DEBUG
	kun_ktk static_cstring<32> m_name;
#endif
};
KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK