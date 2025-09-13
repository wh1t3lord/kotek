#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX
enum class eShaderType;
KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

class ktkShaderModule
{
public:
	ktkShaderModule(void);
	~ktkShaderModule(void);

private:
	bgfx::eShaderType m_shader_type;
};

class ktkBufferModule
{
public:
	ktkBufferModule(void);
	~ktkBufferModule(void);

	GLuint Get_Buffer(void) const noexcept;
	GLenum Get_BufferObjectType(void) const noexcept;

private:
#ifdef KOTEK_DEBUG
	kun_ktk static_cstring<32> m_uniform_block_name;
#endif
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

constexpr unsigned char kVertexInputAttribute_Position = 0;
constexpr unsigned char kVertexInputAttribute_UV = 1;
constexpr unsigned char kVertexInputAttribute_DrawID = 3;
constexpr unsigned char kVertexInputAttribute_BaseInstance = 4;

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
