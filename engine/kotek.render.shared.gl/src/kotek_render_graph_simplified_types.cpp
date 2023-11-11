#include "../include/kotek_render_graph_simplified_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkRenderGraphShaderTextInfo::ktkRenderGraphShaderTextInfo(
	eShaderLoadingDataType type_loading_data, const ktk::ustring& shader_name,
	const ktk::ustring& path_to_file_or_source_code_string) :
	m_type{type_loading_data},
	m_shader_name{shader_name}, m_data{path_to_file_or_source_code_string}
{
}

ktkRenderGraphShaderTextInfo::ktkRenderGraphShaderTextInfo(
	eShaderLoadingDataType type_loading_data, const ktk::ustring& shader_name,
	void* p_data) :
	m_type{type_loading_data},
	m_shader_name{shader_name}, m_data{p_data}
{
}

ktkRenderGraphShaderTextInfo::ktkRenderGraphShaderTextInfo(void) :
	m_type{eShaderLoadingDataType::kShaderLoadingDataType_NotInitialized},
	m_data{}
{
}

ktkRenderGraphShaderTextInfo::~ktkRenderGraphShaderTextInfo(void) {}

eShaderLoadingDataType ktkRenderGraphShaderTextInfo::Get_Type(
	void) const noexcept
{
	return this->m_type;
}

void ktkRenderGraphShaderTextInfo::Set_Type(
	eShaderLoadingDataType type) noexcept
{
	this->m_type = type;
}

const ktk::variant<void*, ktk::ustring>& ktkRenderGraphShaderTextInfo::Get_Data(
	void) const noexcept
{
	return this->m_data;
}

void ktkRenderGraphShaderTextInfo::Set_Data(
	const ktk::variant<void*, ktk::ustring>& data) noexcept
{
	this->m_data = data;
}

bool ktkRenderGraphShaderTextInfo::Is_DataValid(void) const noexcept
{
	bool result{};

	if (this->m_type ==
		eShaderLoadingDataType::kShaderLoadingDataType_NotInitialized)
		return result;

	if (this->m_type ==
			eShaderLoadingDataType::kShaderLoadingDataType_FilePathString ||
		this->m_type ==
			eShaderLoadingDataType::
				kShaderLoadingDataType_SourceCode_TextString)
	{
		if (std::get<ktk::ustring>(this->m_data).empty() == false)
		{
			result = true;
		}
	}
	else if (this->m_type ==
			eShaderLoadingDataType::kShaderLoadingDataType_ByteArrayFile ||
		this->m_type ==
			eShaderLoadingDataType::
				kShaderLoadingDataType_ByteArrayCompiledSPIRV)
	{
		if (std::get<void*>(this->m_data) != nullptr)
		{
			result = true;
		}
	}
	else
	{
		KOTEK_ASSERT(false, "can't be!!");
	}

	return result;
}

const ktk::ustring& gl::ktkRenderGraphShaderTextInfo::Get_ShaderName(
	void) const noexcept
{
	return this->m_shader_name;
}

ktkRenderGraphBufferInfo::ktkRenderGraphBufferInfo(GLenum type, GLenum usage,
	const ktk::cstring& uniform_block_name, GLuint binding_point,
	ktk::size_t memory_for_allocation, ktk::size_t align_of_memory,
	const ktk::ustring& shader_name, const ktk::cstring& buffer_name) :
	m_buffer_object{type},
	m_usage{usage}, m_binding_point_index{binding_point},
	m_memory{memory_for_allocation}, m_memory_align_value{align_of_memory},
	m_uniform_block_in_your_shader{uniform_block_name},
	m_buffer_name{buffer_name}
#ifdef KOTEK_DEBUG
	,
	m_shader_name{shader_name}
#endif
{
}

ktkRenderGraphBufferInfo::ktkRenderGraphBufferInfo(void) :
	m_buffer_object{GL_UNIFORM_BUFFER}, m_usage{GL_STATIC_DRAW},
	m_binding_point_index{}, m_memory{}, m_memory_align_value{}
{
}

ktkRenderGraphBufferInfo::~ktkRenderGraphBufferInfo(void) {}

GLenum ktkRenderGraphBufferInfo::Get_BufferObject(void) const noexcept
{
	return this->m_buffer_object;
}

GLenum ktkRenderGraphBufferInfo::Get_Usage(void) const noexcept
{
	return this->m_usage;
}

GLuint ktkRenderGraphBufferInfo::Get_BindingPointIndex(void) const noexcept
{
	return this->m_binding_point_index;
}

ktk::size_t ktkRenderGraphBufferInfo::Get_Memory(void) const noexcept
{
	return this->m_memory;
}

ktk::size_t ktkRenderGraphBufferInfo::Get_AlignOfMemory(void) const noexcept
{
	return this->m_memory_align_value;
}

const ktk::cstring& ktkRenderGraphBufferInfo::Get_UniformBlockName(
	void) const noexcept
{
	return this->m_uniform_block_in_your_shader;
}

const ktk::ustring& ktkRenderGraphBufferInfo::Get_ShaderName(
	void) const noexcept
{
#ifdef KOTEK_DEBUG
	return this->m_shader_name;
#else
	return ktk::ustring();
#endif
}

const ktk::cstring& ktkRenderGraphBufferInfo::Get_BufferName(
	void) const noexcept
{
	return this->m_buffer_name;
}

ktkRenderGraphTextureInfo::ktkRenderGraphTextureInfo(void) :
	m_target{}, m_level{},
	m_internalformat{}, m_width{}, m_height{}, m_depth{}, m_border{}, m_format{}
{
}

ktkRenderGraphTextureInfo::~ktkRenderGraphTextureInfo(void) {}

ktk::uint32_t ktkRenderGraphTextureInfo::Get_Target(void) const noexcept
{
	return this->m_target;
}

void ktkRenderGraphTextureInfo::Set_Target(ktk::uint32_t value) noexcept
{
	this->m_target = value;
}

ktk::int32_t ktkRenderGraphTextureInfo::Get_Level(void) const noexcept
{
	return this->m_level;
}

void ktkRenderGraphTextureInfo::Set_Level(ktk::int32_t value) noexcept
{
	this->m_level = value;
}

ktk::int32_t ktkRenderGraphTextureInfo::Get_InternalFormat(void) const noexcept
{
	return this->m_internalformat;
}

ktk::int32_t ktkRenderGraphTextureInfo::Get_Width(void) const noexcept
{
	return this->m_width;
}

void ktkRenderGraphTextureInfo::Set_Width(ktk::int32_t value) noexcept
{
	this->m_width = value;
}

ktk::int32_t ktkRenderGraphTextureInfo::Get_Height(void) const noexcept
{
	return this->m_height;
}

void ktkRenderGraphTextureInfo::Set_Height(ktk::int32_t value) noexcept
{
	this->m_height = value;
}

ktk::int32_t ktkRenderGraphTextureInfo::Get_Depth(void) const noexcept
{
	return this->m_depth;
}

void ktkRenderGraphTextureInfo::Set_Depth(ktk::int32_t value) noexcept
{
	this->m_depth = value;
}

ktk::int32_t ktkRenderGraphTextureInfo::Get_Border(void) const noexcept
{
	return this->m_border;
}
void ktkRenderGraphTextureInfo::Set_Border(ktk::int32_t value) noexcept
{
	this->m_border = value;
}

ktk::uint32_t ktkRenderGraphTextureInfo::Get_Format(void) const noexcept
{
	return this->m_format;
}

void ktkRenderGraphTextureInfo::Set_Format(ktk::uint32_t value) noexcept
{
	this->m_format = value;
}

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
