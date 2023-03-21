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
		gl::eShaderType type, ktk::uint32_t handle_id) noexcept
	{
		this->m_shader_type = type;
		this->m_shader_handle = handle_id;
	}

	ktk::uint32_t ktkShaderModule::Get_Shader(void) const noexcept
	{
		return this->m_shader_handle;
	}

	gl::eShaderType ktkShaderModule::Get_ShaderType(void) const noexcept
	{
		return this->m_shader_type;
	}

	ktkDrawVertexIndirectCommand::ktkDrawVertexIndirectCommand() :
		m_count{}, m_instance_count{}, m_first{}, m_reserved{}
	{
	}

	ktkDrawVertexIndirectCommand::~ktkDrawVertexIndirectCommand() {}

	GLuint ktkDrawVertexIndirectCommand::Get_Count(void) const noexcept
	{
		return this->m_count;
	}
	void ktkDrawVertexIndirectCommand::Set_Count(GLuint value) noexcept
	{
		this->m_count = value;
	}

	GLuint ktkDrawVertexIndirectCommand::Get_InstanceCount(void) const noexcept
	{
		return this->m_instance_count;
	}
	void ktkDrawVertexIndirectCommand::Set_InstanceCount(GLuint value) noexcept
	{
		this->m_instance_count = value;
	}

	GLuint ktkDrawVertexIndirectCommand::Get_First(void) const noexcept
	{
		return this->m_first;
	}
	void ktkDrawVertexIndirectCommand::Set_First(GLuint value) noexcept
	{
		this->m_first = value;
	}

	GLuint ktkDrawVertexIndirectCommand::Get_Reserved(void) const noexcept
	{
		return this->m_first;
	}
	void ktkDrawVertexIndirectCommand::Set_Reserved(GLuint value) noexcept
	{
		this->m_first = value;
	}

	ktkDrawIndexIndirectCommand::ktkDrawIndexIndirectCommand() :
		m_count{}, m_instance_count{}, m_first_index{}, m_base_vertex{},
		m_reserved_must_be_zero{}
	{
	}

	ktkDrawIndexIndirectCommand::~ktkDrawIndexIndirectCommand() {}

	GLuint ktkDrawIndexIndirectCommand::Get_Count(void) const noexcept
	{
		return this->m_count;
	}
	void ktkDrawIndexIndirectCommand::Set_Count(GLuint value) noexcept
	{
		this->m_count = value;
	}

	GLuint ktkDrawIndexIndirectCommand::Get_InstanceCount(void) const noexcept
	{
		return this->m_instance_count;
	}
	void ktkDrawIndexIndirectCommand::Set_InstanceCount(GLuint value) noexcept
	{
		this->m_instance_count = value;
	}

	GLuint ktkDrawIndexIndirectCommand::Get_FirstIndex(void) const noexcept
	{
		return this->m_first_index;
	}
	void ktkDrawIndexIndirectCommand::Set_FirstIndex(GLuint value) noexcept
	{
		this->m_first_index = value;
	}

	GLuint ktkDrawIndexIndirectCommand::Get_BaseVertex(void) const noexcept
	{
		return this->m_base_vertex;
	}
	void ktkDrawIndexIndirectCommand::Set_BaseVertex(GLuint value) noexcept
	{
		this->m_base_vertex = value;
	}

	GLuint ktkDrawIndexIndirectCommand::Get_ReservedMustBeZero(
		void) const noexcept
	{
		return this->m_reserved_must_be_zero;
	}
	void ktkDrawIndexIndirectCommand::Set_ReservedMustBeZero(
		GLuint value) noexcept
	{
		this->m_reserved_must_be_zero = value;
	}
} // namespace gl

namespace gl
{
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
