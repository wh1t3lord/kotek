#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

enum class eShaderType;

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

class ktkShaderModule
{
public:
	ktkShaderModule(void);
	~ktkShaderModule(void);

	void Set_Shader(gl::eShaderType type, GLuint handle_id) noexcept;

	GLuint Get_Shader(void) const noexcept;

	gl::eShaderType Get_ShaderType(void) const noexcept;

private:
	/// \~english @brief this is the handle (result) of glCreateShader
	/// operation
	GLuint m_shader_handle;

	/// \~english @brief enum for determining what is the type of shader
	gl::eShaderType m_shader_type;
};

class ktkBufferModule
{
public:
	/// \~english @brief Just default construction make data invalid for usage
	/// @param void, nothing
	ktkBufferModule(void);

	/// \~english @brief Just destructor. There's no functions for deleting
	/// information! Deleting is in ktkRenderGraphSimplifiedResourceManager
	/// @param void, nothing
	~ktkBufferModule(void);

	/// \~english @brief returns buffer object handle that was generated through
	/// glGenBuffers function
	/// @param void, nothing
	/// @return buffer object handle that was generated through glGenBuffers
	/// function
	GLuint Get_Buffer(void) const noexcept;

	/// \~english @brief returns buffer object type like GL_UNIFORM_BUFFER,
	/// GL_SHADER_BUFFER_STORAGE
	/// @param void, nothing
	/// @return buffer object type it could be GL_UNIFORM_BUFFER,
	/// GL_SHADER_STORAGE_BUFFER and etc
	GLenum Get_BufferObjectType(void) const noexcept;

	/// \~english @brief This method is not for user. It uses in Create_Buffers
	/// method of ktkRenderGraphSimplifiedResourceManager. Don't use it
	/// somewhere else, because it should be private method, but it doesn't make
	/// any sense if you follow the rules. Don't use it by your own if you don't
	/// understand how to use it. If you re-write information, please be sure
	/// that you deleted previous information for GPU using glDeleteBuffers
	/// function.
	/// @param buffer_object_type it is GL_UNIFORM_BUFFER,
	/// GL_SHADER_STORAGE_BUFFER and etc
	/// @param handle_from_gl_gen_buffers it is GLuint handle that you passed to
	/// glGenBuffers function as second parameter in it.
	void Set_Buffer(
		GLenum buffer_object_type, GLuint handle_from_gl_gen_buffers) noexcept;

private:
	/// \~english @brief this field contains data from glGenBuffers result
	/// handle
	GLuint m_buffer_handle;

	/// \~english @brief this field contains data that represent what type the
	/// buffer is like GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER and etc
	GLenum m_buffer_object_type;
};

// for indirect rendering
struct ktkDrawVertexIndirectCommand
{
	GLuint m_count;
	GLuint m_instance_count;
	GLuint m_first;
	GLuint m_reserved;
};

// for indirect rendering (indexed)
struct ktkDrawIndexIndirectCommand
{
	GLuint m_count;
	GLuint m_instance_count;
	GLuint m_first_index;
	GLuint m_base_vertex;
	GLuint m_reserved_must_be_zero;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
