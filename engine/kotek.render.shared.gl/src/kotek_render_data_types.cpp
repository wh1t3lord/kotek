#include "../include/kotek_render_data_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gl
{
	ktkShaderModule::ktkShaderModule(void) :
		m_shader_handle{}, m_shader_type{gl::eShaderType::kShaderType_Unknown}
	{
	}

	ktkShaderModule::~ktkShaderModule(void) {}

	void ktkShaderModule::Set_Shader(
		gl::eShaderType type, GLuint handle_id) noexcept
	{
		this->m_shader_type = type;
		this->m_shader_handle = handle_id;
	}

	GLuint ktkShaderModule::Get_Shader(void) const noexcept
	{
		return this->m_shader_handle;
	}

	gl::eShaderType ktkShaderModule::Get_ShaderType(void) const noexcept
	{
		return this->m_shader_type;
	}
} // namespace gl

namespace gl
{
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
