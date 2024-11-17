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

	GLuint Get_BindingPointIndex(void) const noexcept;
	void Set_BindingPointIndex(GLuint id) noexcept;

	const char* Get_UniformBlockName(void) const noexcept;
	void Set_UniformBlockName(
		const kun_ktk static_cstring<32>& block_name) noexcept;

private:
	/// \~english @brief this field contains data from glGenBuffers result
	/// handle
	GLuint m_buffer_handle;

	/// \~english @brief this is what you write in layout(std140, binding=index)
	/// where index is represented by this field (m_binding_point_index)
	GLuint m_binding_point_index;

	/// \~english @brief this field contains data that represent what type the
	/// buffer is like GL_UNIFORM_BUFFER, GL_SHADER_STORAGE_BUFFER and etc
	GLenum m_buffer_object_type;

#ifdef KOTEK_DEBUG
	kun_ktk static_cstring<32> m_uniform_block_name;
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

class ktkVertex
{
public:
	ktkVertex()
	{
		this->m_position[0] = 0.0f;
		this->m_position[1] = 0.0f;
		this->m_position[2] = 0.0f;
	}

	ktkVertex(float x, float y, float z) { this->Set_Position(x, y, z); }

	~ktkVertex() {}

	void Set_Position(float x, float y, float z) noexcept
	{
		this->m_position[0] = x;
		this->m_position[1] = y;
		this->m_position[2] = z;
	}

	void* Get_Data() noexcept { return this->m_position; }

private:
	float m_position[3];
};

class ktkGeometry
{
public:
	ktkGeometry() {}
	ktkGeometry(kun_ktk enum_base_t geometry_type,
		const kun_ktk vector<kun_ktk kun_math vec3f_t>& vertex_data,
		const kun_ktk vector<kun_ktk uint32_t>& index_data) :
		m_geometry_type{geometry_type},
		m_vertex_data{vertex_data}, m_index_data{index_data}
	{
	}

	ktkGeometry(kun_ktk cstring geometry_type,
		const kun_ktk vector<kun_ktk kun_math vec3f_t>& vertex_data,
		const kun_ktk vector<kun_ktk uint32_t>& index_data) :
		m_geometry_type{geometry_type},
		m_vertex_data{vertex_data}, m_index_data{index_data}
	{
	}

	~ktkGeometry() {}

	void Set_GeometryType(kun_ktk enum_base_t value)
	{
		this->m_geometry_type = value;
	}

	void Set_GeometryType(const kun_ktk cstring& value)
	{
		this->m_geometry_type = value;
	}

	const kun_ktk variant<kun_ktk enum_base_t, kun_ktk cstring>&
	Get_GeometryType(void) const
	{
		return this->m_geometry_type;
	}

	const kun_ktk vector<kun_ktk kun_math vec3f_t>& Get_VertexData() const
	{
		return this->m_vertex_data;
	}

	void Set_VertexData(const kun_ktk vector<kun_ktk kun_math vec3f_t>& data)
	{
		this->m_vertex_data = data;
	}

	const kun_ktk vector<kun_ktk uint32_t>& Get_IndexData() const
	{
		return this->m_index_data;
	}

	void Set_IndexData(const kun_ktk vector<kun_ktk uint32_t>& data)
	{
		this->m_index_data = data;
	}

private:
	/// \~english @brief If it is enum_base_t type it means it is
	/// eStaticGeometryType
	kun_ktk variant<kun_ktk enum_base_t, kun_ktk cstring> m_geometry_type;
	kun_ktk vector<kun_ktk kun_math vec3f_t> m_vertex_data;
	kun_ktk vector<kun_ktk uint32_t> m_index_data;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
