#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX
class ktkRenderDevice;
class ktkRenderTextureManager;
class ktkRenderShaderManager;
class ktkRenderGeometryManager;
KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

class ktkRenderResourceManager : public kun_core ktkIRenderResourceManager
{
public:
	ktkRenderResourceManager(kun_core ktkIRenderDevice* p_device,
		kun_core ktkMainManager* p_manager);
	ktkRenderResourceManager(void) = delete;

	~ktkRenderResourceManager(void);

	ktkRenderResourceManager(const ktkRenderResourceManager&) = delete;
	ktkRenderResourceManager& operator=(
		const ktkRenderResourceManager&) = delete;
	ktkRenderResourceManager(ktkRenderResourceManager&&) = delete;
	ktkRenderResourceManager& operator=(ktkRenderResourceManager&&) = delete;

	void initialize(kun_core ktkIRenderDevice* p_raw_device,
		kun_core ktkIRenderSwapchain* p_raw_swapchain,
		ktk::size_t memory_size =
			ktk::kMemoryConvertValueDenominator_Megabytes * 32) override;

	void shutdown(kun_core ktkIRenderDevice* p_raw_device) override;

	void Resize(kun_core ktkIRenderDevice* p_raw_device,
		kun_core ktkIRenderSwapchain* p_raw_swapchain) override;

	// called from a thread! Not render thread!!!!
	// not cached , without cache
	ktk::shared_ptr<kun_core ktkResourceHandle> LoadGeometry(
		ktk::enum_base_t resource_loading_type, ktk::uint32_t id) override;
	ktk::shared_ptr<kun_core ktkResourceHandle> LoadGeometry(
		ktk::enum_base_t resource_loading_type,
		const ktk_filesystem_path& path_to_file, ktk::uint32_t id) override;

	// call only in render thread
	void Update(void) noexcept;

	ktkRenderTextureManager* Get_ManagerTexture(void) const noexcept;
	ktkRenderShaderManager* Get_ManagerShader(void) const noexcept;
	ktkRenderGeometryManager* Get_ManagerGeometry(void) const noexcept;

	ktkRenderStats* Get_Statistic(
		kun_core eRenderStatistics type) noexcept override;

private:
	kun_core ktkIRenderDevice* m_p_render_device;
	ktkRenderTextureManager* m_p_render_manager_texture;
	ktkRenderShaderManager* m_p_render_manager_shader;
	ktkRenderGeometryManager* m_p_render_manager_geometry;
	kun_core ktkMainManager* m_p_main_manager;
};

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK