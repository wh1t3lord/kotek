#include "../include/kotek_render_data_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkShaderModule::ktkShaderModule(void) :
				m_shader_handle{}, m_shader_type{
									   gl::eShaderType::kShaderType_Unknown}
			{
			}

			ktkShaderModule::~ktkShaderModule(void) {}

			void ktkShaderModule::Set_Shader(
				gl::eShaderType type, GLuint handle_id) noexcept
			{
			}

			GLuint ktkShaderModule::Get_Shader(void) const noexcept
			{
				return this->m_shader_handle;
			}

			gl::eShaderType ktkShaderModule::Get_ShaderType(void) const noexcept
			{
				return this->m_shader_type;
			}
		} // namespace gl3_3

		namespace gl
		{
		}
	} // namespace Render
} // namespace Kotek
