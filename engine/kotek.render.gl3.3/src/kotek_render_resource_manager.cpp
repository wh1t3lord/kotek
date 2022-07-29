#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_texture_manager.h"
#include "../include/kotek_render_shader_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderResourceManager::ktkRenderResourceManager(
				ktkRenderDevice* p_device, Core::ktkMainManager* p_manager) :
				m_p_render_device{p_device},
				m_p_render_manager_texture{}, m_p_render_manager_shader{},
				m_p_main_manager{p_manager}
			{
			}

			ktkRenderResourceManager::~ktkRenderResourceManager(void) {}

			void ktkRenderResourceManager::initialize(
				Core::ktkIRenderDevice* p_raw_device,
				Core::ktkIRenderSwapchain* p_raw_swapchain)
			{
				KOTEK_ASSERT(
					p_raw_device, "you can't pass an invalid interface");
				KOTEK_ASSERT(
					p_raw_swapchain, "you can't pass an invalid interface");

				this->m_p_render_manager_texture =
					new ktkRenderTextureManager(this->m_p_main_manager);
				this->m_p_render_manager_shader =
					new ktkRenderShaderManager(this->m_p_main_manager);

				this->m_p_render_manager_texture->Initialize();
				this->m_p_render_manager_shader->Initialize();
			}

			void ktkRenderResourceManager::shutdown(
				Core::ktkIRenderDevice* p_raw_device)
			{
				KOTEK_ASSERT(
					p_raw_device, "you can't pass an invalid interface");

				if (this->m_p_render_manager_texture)
				{
					this->m_p_render_manager_texture->Shutdown();
					delete this->m_p_render_manager_texture;
					this->m_p_render_manager_texture = nullptr;
				}

				if (this->m_p_render_manager_shader)
				{
					this->m_p_render_manager_shader->Shutdown();
					delete this->m_p_render_manager_shader;
					this->m_p_render_manager_shader = nullptr;
				}
			}

			void ktkRenderResourceManager::Resize(
				Core::ktkIRenderDevice* p_raw_device,
				Core::ktkIRenderSwapchain* p_raw_swapchain)
			{
				KOTEK_ASSERT(
					p_raw_device, "you can't pass an invalid interface");
				KOTEK_ASSERT(
					p_raw_swapchain, "you can't pass an invalid interface");
			}

			ktkRenderTextureManager*
			ktkRenderResourceManager::Get_ManagerTexture(void) const noexcept
			{
				return this->m_p_render_manager_texture;
			}

			ktkRenderShaderManager* ktkRenderResourceManager::Get_ManagerShader(
				void) const noexcept
			{
				return this->m_p_render_manager_shader;
			}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek