#include "kotek_render_shader_manager.h"
#include "../kotek.core/kotek_main_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderShaderManager::ktkRenderShaderManager(Core::ktkMainManager* p_main_manager) : m_p_main_manager(p_main_manager) 
			{
				KOTEK_ASSERT(p_main_manager, "must be valid");
			}

			ktkRenderShaderManager::~ktkRenderShaderManager(void) {}

			void ktkRenderShaderManager::Initialize(void) {}

			void ktkRenderShaderManager::Shutdown(void) {}

			ktkRenderShaderManager::shader_module_t
			ktkRenderShaderManager::LoadShader(
				const ktk::path& path, shader_type_t type) noexcept
			{
				return shader_module_t();
			}

			ktkRenderShaderManager::shader_module_t
			ktkRenderShaderManager::LoadShader(
				const ktk::path& path) noexcept
			{
				return shader_module_t();
			}

			ktkRenderShaderManager::shader_module_t
			ktkRenderShaderManager::LoadShaderAsString(
				const ktk::string& code_as_string, shader_type_t type) noexcept
			{
				return shader_module_t();
			}

			void ktkRenderShaderManager::DestroyShader(
				const shader_module_t& instance) noexcept
			{
			}

			ktkRenderShaderManager::shader_module_t::shader_module_t(void) :
				m_program{}
			{
			}
			
			ktkRenderShaderManager::shader_module_t::~shader_module_t(void) {}

			void ktkRenderShaderManager::shader_module_t::SetShader(
				shader_type_t type, GLuint handle_id) noexcept
			{
			}

			GLuint ktkRenderShaderManager::shader_module_t::GetShader(
				shader_type_t type) const noexcept
			{
				return GLuint();
			}

			const ktk::unordered_map<shader_type_t, GLuint>&
			ktkRenderShaderManager::shader_module_t::GetShaders(
				void) const noexcept
			{
				return this->m_shader_handles;
			}

			void ktkRenderShaderManager::shader_module_t::SetProgram(
				GLuint handle_id) noexcept
			{
			}

			GLuint ktkRenderShaderManager::shader_module_t::GetProgram(
				void) const noexcept
			{
				return this->m_program;
			}

		} // namespace gl
	}     // namespace Render
} // namespace Kotek