#include "../include/kotek_render_data_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkShaderModule::ktkShaderModule(void) :
	m_shader_handle{}, m_shader_type{gl::eShaderType::kShaderType_Unknown}
{
}

ktkShaderModule::~ktkShaderModule(void) {}

void ktkShaderModule::Set_Shader(
	gl::eShaderType type, GLuint handle_id) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	this->m_shader_type = type;
	this->m_shader_handle = handle_id;
}

GLuint ktkShaderModule::Get_Shader(void) const KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return this->m_shader_handle;
}

gl::eShaderType ktkShaderModule::Get_ShaderType(
	void) const KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return this->m_shader_type;
}

ktkBufferModule::ktkBufferModule(void) :
	m_buffer_handle{}, m_buffer_object_type{}
{
}

ktkBufferModule::~ktkBufferModule(void) {}

GLuint ktkBufferModule::Get_Buffer(void) const KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return this->m_buffer_handle;
}

GLenum ktkBufferModule::Get_BufferObjectType(
	void) const KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return this->m_buffer_object_type;
}

void ktkBufferModule::Set_Buffer(GLenum buffer_object_type,
	GLuint handle_from_gl_gen_buffers) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	this->m_buffer_handle = handle_from_gl_gen_buffers;
	this->m_buffer_object_type = buffer_object_type;
}

GLuint ktkBufferModule::Get_BindingPointIndex(void) const noexcept
{
	return this->m_binding_point_index;
}

void ktkBufferModule::Set_BindingPointIndex(GLuint id) noexcept
{
	this->m_binding_point_index = id;
}

const char* ktkBufferModule::Get_UniformBlockName(void) const noexcept
{
#ifdef KOTEK_DEBUG
	return this->m_uniform_block_name.c_str();
#else
	return nullptr;
#endif
}

void ktkBufferModule::Set_UniformBlockName(
	const kun_ktk static_cstring<32>& block_name) noexcept
{
#ifdef KOTEK_DEBUG
	this->m_uniform_block_name = block_name;
#endif
}

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK