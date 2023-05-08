#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderDevice;
	class ktkRenderTextureManager;
	class ktkRenderShaderManager;
	class ktkRenderGeometryManager;
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderResourceManager : public Core::ktkIRenderResourceManager
	{
	public:
		// this is because GL shares some implementations with GLES
		ktkRenderResourceManager(
			Core::ktkIRenderDevice* p_device, Core::ktkMainManager* p_manager);
		ktkRenderResourceManager(void) = delete;

		~ktkRenderResourceManager(void);

		ktkRenderResourceManager(const ktkRenderResourceManager&) = delete;
		ktkRenderResourceManager& operator=(
			const ktkRenderResourceManager&) = delete;
		ktkRenderResourceManager(ktkRenderResourceManager&&) = delete;
		ktkRenderResourceManager& operator=(
			ktkRenderResourceManager&&) = delete;

		void initialize(Core::ktkIRenderDevice* p_raw_device,
			Core::ktkIRenderSwapchain* p_raw_swapchain,
			ktk::size_t memory_size = ktk::kMemoryConvertValueDenominator_Megabytes *
				32) override;

		void shutdown(Core::ktkIRenderDevice* p_raw_device) override;

		void Resize(Core::ktkIRenderDevice* p_raw_device,
			Core::ktkIRenderSwapchain* p_raw_swapchain) override;

		// called from a thread! Not render thread!!!!
		// not cached , without cache
		void LoadGeometry(
			ktk::enum_base_t resource_loading_type, ktk::entity_t id) override;
		void LoadGeometry(ktk::enum_base_t resource_loading_type,
			const ktk::filesystem::path& path_to_file,
			ktk::entity_t id) override;

		// call only in render thread
		void Update(void) noexcept;

		ktkRenderTextureManager* Get_ManagerTexture(void) const noexcept;
		ktkRenderShaderManager* Get_ManagerShader(void) const noexcept;
		ktkRenderGeometryManager* Get_ManagerGeometry(void) const noexcept;

		ktkRenderStats* Get_Statistic(
			Core::eRenderStatistics type) noexcept override;

	private:
		Core::ktkIRenderDevice* m_p_render_device;
		ktkRenderTextureManager* m_p_render_manager_texture;
		ktkRenderShaderManager* m_p_render_manager_shader;
		ktkRenderGeometryManager* m_p_render_manager_geometry;
		Core::ktkMainManager* m_p_main_manager;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK