#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	enum class eShaderType;
}
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gl
{
	class ktkShaderModule
	{
	public:
		ktkShaderModule(void);
		~ktkShaderModule(void);

		void Set_Shader(gl::eShaderType type, ktk::uint32_t handle_id) noexcept;

		ktk::uint32_t Get_Shader(void) const noexcept;

		gl::eShaderType Get_ShaderType(void) const noexcept;

	private:
		/// @brief this is the handle (result) of glCreateShader
		/// operation
		ktk::uint32_t m_shader_handle;

		/// @brief enum for determining what is the type of shader
		gl::eShaderType m_shader_type;
	};

	// for indirect rendering
	class ktkDrawVertexIndirectCommand
	{
	public:
		ktkDrawVertexIndirectCommand();
		~ktkDrawVertexIndirectCommand();

		GLuint Get_Count(void) const noexcept;
		void Set_Count(GLuint value) noexcept;

		GLuint Get_InstanceCount(void) const noexcept;
		void Set_InstanceCount(GLuint value) noexcept;

		GLuint Get_First(void) const noexcept;
		void Set_First(GLuint value) noexcept;

		GLuint Get_Reserved(void) const noexcept;
		void Set_Reserved(GLuint value) noexcept;

	private:
		GLuint m_count;
		GLuint m_instance_count;
		GLuint m_first;
		GLuint m_reserved;
	};

	// for indirect rendering
	class ktkDrawIndexIndirectCommand
	{
	public:
		ktkDrawIndexIndirectCommand();
		~ktkDrawIndexIndirectCommand();

		GLuint Get_Count(void) const noexcept;
		void Set_Count(GLuint value) noexcept;

		GLuint Get_InstanceCount(void) const noexcept;
		void Set_InstanceCount(GLuint value) noexcept;

		GLuint Get_FirstIndex(void) const noexcept;
		void Set_FirstIndex(GLuint value) noexcept;

		GLuint Get_BaseVertex(void) const noexcept;
		void Set_BaseVertex(GLuint value) noexcept;

		GLuint Get_ReservedMustBeZero(void) const noexcept;
		void Set_ReservedMustBeZero(GLuint value) noexcept;

	private:
		GLuint m_count;
		GLuint m_instance_count;
		GLuint m_first_index;
		GLuint m_base_vertex;
		GLuint m_reserved_must_be_zero;
	};
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
