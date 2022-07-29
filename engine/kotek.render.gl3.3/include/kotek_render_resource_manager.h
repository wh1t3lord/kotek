#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderDevice;
			class ktkRenderTextureManager;
			class ktkRenderShaderManager;
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderResourceManager
				: public Core::ktkIRenderResourceManager
			{
			public:
				ktkRenderResourceManager(
					ktkRenderDevice* p_device, Core::ktkMainManager* p_manager);
				ktkRenderResourceManager(void) = delete;

				~ktkRenderResourceManager(void);

				ktkRenderResourceManager(
					const ktkRenderResourceManager&) = delete;
				ktkRenderResourceManager& operator=(
					const ktkRenderResourceManager&) = delete;
				ktkRenderResourceManager(ktkRenderResourceManager&&) = delete;
				ktkRenderResourceManager& operator=(
					ktkRenderResourceManager&&) = delete;

				void initialize(Core::ktkIRenderDevice* p_raw_device,
					Core::ktkIRenderSwapchain* p_raw_swapchain) override;

				void shutdown(Core::ktkIRenderDevice* p_raw_device) override;

				void Resize(Core::ktkIRenderDevice* p_raw_device,
					Core::ktkIRenderSwapchain* p_raw_swapchain) override;

				ktkRenderTextureManager* Get_ManagerTexture(
					void) const noexcept;
				ktkRenderShaderManager* Get_ManagerShader(void) const noexcept;

			private:
				ktkRenderDevice* m_p_render_device;
				ktkRenderTextureManager* m_p_render_manager_texture;
				ktkRenderShaderManager* m_p_render_manager_shader;
				Core::ktkMainManager* m_p_main_manager;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek
