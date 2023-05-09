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

/// \~english @brief this class contains all necessary information for
/// simplified render graph usage. It contains buffer handle that was generated
/// by glGenBuffers calling and buffer object type (e.g. GL_UNIFORM_BUFFER,
/// GL_SHADER_STORAGE_BUFFER and etc)
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

	/// \~english @brief it has implementation when development build is
	/// KOTEK_DEBUG otherwise there is no implementation and will be return 0.
	/// This method return information about final memory allocation that was
	/// aligned by value that user passed when he creates it in storage input
	/// class. (e.g. Add_Buffer calling)
	/// @param void, nothing
	/// @return returns 0 when development build IS NOT KOTEK_DEBUG otherwise
	/// returns value (in bytes!) that user passed for constructor. So use it only when
	/// development build is KOTEK_DEBUG!
	ktk::size_t Get_AlignedMemoryForAllocation(void) const noexcept;

	/// \~english @brief it has implementation when development build is
	/// KOTEK_DEBUG otherwise there is no implementation and will be returned 0.
	/// This method sets value to m_aligned_memory_for_allocation field
	/// @param value is ktk::size_t type and represents the final value for
	/// memory allocation. Value is in bytes!
	void Set_AlignedMemoryForAllocation(ktk::size_t value) noexcept;

	/// \~english @brief it has implementation when development build is
	/// KOTEK_DEBUG otherwise there is no implementation and will be returned 0.
	/// This method returns information about value for alingment for required
	/// memory. What does it mean? It means that if I pass value 59 (in bytes)
	/// but my alignment value is 2 the final value will be
	/// ktk::align_down<ktk::size_t>(59, 2) equals  58 because we use align_down
	/// and it 'searches' for the close value to 59 but not higher than 59 for
	/// align_up result will be 60
	/// @param void, nothing to pass
	/// @return returns 0 when development build IS NOT KOTEK_DEBUG otherwise
	/// returns value (in bytes!) that user passed for constructor. So use it only when
	/// development build is KOTEK_DEBUG
	ktk::size_t Get_MemoryAlign(void) const noexcept;

	/// \~english @brief it has implementation when development build is
	/// KOTEK_DEBUG otherwise there is no implementation and will be returned 0.
	/// This method sets value to m_memory_align field.
	/// @param value is ktk::size_t type and represents the alignment when
	/// ktk::align_down is issued its second parameter of that function
	void Set_MemoryAlign(ktk::size_t value) noexcept;

	/// \~english @brief it has implementation when development build is
	/// KOTEK_DEBUG otherwise there is no implementation and will be returned 0.
	/// This method return information about what user initially passed value as
	/// memory size for allocation. Because after that when we want to create a
	/// buffer we find the aligned value to the alignment value by using
	/// ktk::align_down function.
	/// @param void, nothing to pass
	/// @return returns 0 when development build IS NOT KOTEK_DEBUG otherwise
	/// returns value (in bytes!) that user passed for constructor. So use it only when
	/// development build is KOTEK_DEBUG
	ktk::size_t Get_NotAlignedMemoryForAllocation(void) const noexcept;

	/// \~english @brief it has implementation when development build is
	/// KOTEK_DEBUG otherwise there is no implementation and will be returned 0.
	/// This method sets value to  m_not_aligned_memory_for_allocation field
	/// @param value is ktk::size_t type and represents initial not aligned
	/// value for memory allocation. It uses when ktk::align_down function is
	/// issued and its first parameter.
	void Set_NotAlignedMemoryForAllocation(ktk::size_t value) noexcept;

private:
	/// \~english @brief this field contains data from glGenBuffers result
	/// handle
	GLuint m_buffer_handle;

	/// \~english @brief this field contains data that represent what type the
	/// buffer is like GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER and etc
	GLenum m_buffer_object_type;

#ifdef KOTEK_DEBUG
	ktk::size_t m_aligned_memory_for_allocation;
	ktk::size_t m_memory_align;
	ktk::size_t m_not_aligned_memory_for_allocation;
#endif
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
