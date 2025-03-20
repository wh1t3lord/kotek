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

struct ktkDrawElementsIndirectCommand
{
	/// @brief \~english you need to specify elements (e.g. indecies that's
	/// using for drawing)
	unsigned int count;
	/// @brief \~english current amount of instances for drawing (instancing)
	unsigned int instanceCount;
	/// @brief \~english offset for element buffer where indecies were uploaded
	unsigned int firstIndex;
	/// @brief \~english offset for array buffer where vertecies were uploaded
	int baseVertex;
	unsigned int baseInstance;
};

struct ktkDrawArraysIndirectCommand
{
	unsigned int count;
	unsigned int instanceCount;
	unsigned int firstVertex;
	unsigned int baseInstance;
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
		m_geometry_type{geometry_type}, m_vertex_data{vertex_data},
		m_index_data{index_data}
	{
	}

	ktkGeometry(kun_ktk cstring geometry_type,
		const kun_ktk vector<kun_ktk kun_math vec3f_t>& vertex_data,
		const kun_ktk vector<kun_ktk uint32_t>& index_data) :
		m_geometry_type{geometry_type}, m_vertex_data{vertex_data},
		m_index_data{index_data}
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

/// @brief glVertexAttribPointer(semantic_id,
/// ktkVertexSemanticData::number_of_components,
/// ktkVertexSemanticData::component_type, ktkVertexSemanticData::normalized,
/// ktkVertexSemanticData::stride, ktkVertexSemanticData::offset);
/// or as naive example glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
/// sizeof(ktkVertex), 0);
struct ktkVertexSemanticData
{
	/// @brief \~english Specifies the number of components per generic vertex
	/// attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant
	/// GL_BGRA is accepted by glVertexAttribPointer. The initial value is 4.
	kun_ktk uint8_t number_of_components;
	/// @brief \~english For glVertexAttribPointer, specifies whether
	/// fixed-point data values should be normalized (GL_TRUE) or converted
	/// directly as fixed-point values (GL_FALSE) when they are accessed.
	GLboolean normalized;
	/// @brief \~english Specifies the byte offset between consecutive generic
	/// vertex attributes. If stride is 0, the generic vertex attributes are
	/// understood to be tightly packed in the array. The initial value is 0.
	kun_ktk uint16_t stride;
	/// @brief Specifies a offset of the first component of the first generic
	/// vertex attribute in the array in the data store of the buffer currently
	/// bound to the GL_ARRAY_BUFFER target. The initial value is 0.
	kun_ktk uint16_t offset;
	/// @brief \~english Specifies the data type of each component in the array.
	/// The symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,
	/// GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT are accepted by
	/// glVertexAttribPointer and glVertexAttribIPointer. Additionally
	/// GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED, GL_INT_2_10_10_10_REV,
	/// GL_UNSIGNED_INT_2_10_10_10_REV and GL_UNSIGNED_INT_10F_11F_11F_REV are
	/// accepted by glVertexAttribPointer. GL_DOUBLE is also accepted by
	/// glVertexAttribLPointer and is the only token accepted by the type
	/// parameter for that function. The initial value is GL_FLOAT.
	GLenum component_type;
};

constexpr unsigned char kVertexInputAttribute_Position = 0;
constexpr unsigned char kVertexInputAttribute_UV = 1;
constexpr unsigned char kVertexInputAttribute_DrawID = 3;
constexpr unsigned char kVertexInputAttribute_BaseInstance = 4;

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
