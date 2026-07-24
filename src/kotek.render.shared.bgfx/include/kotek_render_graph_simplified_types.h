#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX
enum class eShaderLoadingDataType;
enum class eShaderType;
KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX
class ktkRenderGraphTextureInfo
{
public:
	ktkRenderGraphTextureInfo(void);
	~ktkRenderGraphTextureInfo(void);

	ktk::uint32_t Get_Target(void) const noexcept;
	void Set_Target(ktk::uint32_t value) noexcept;

	ktk::int32_t Get_Level(void) const noexcept;
	void Set_Level(ktk::int32_t value) noexcept;

	ktk::int32_t Get_InternalFormat(void) const noexcept;

	ktk::int32_t Get_Width(void) const noexcept;
	void Set_Width(ktk::int32_t value) noexcept;

	ktk::int32_t Get_Height(void) const noexcept;
	void Set_Height(ktk::int32_t value) noexcept;

	ktk::int32_t Get_Depth(void) const noexcept;
	void Set_Depth(ktk::int32_t value) noexcept;

	ktk::int32_t Get_Border(void) const noexcept;
	void Set_Border(ktk::int32_t value) noexcept;

	ktk::uint32_t Get_Format(void) const noexcept;
	void Set_Format(ktk::uint32_t value) noexcept;

private:
	ktk::uint32_t m_target;
	ktk::int32_t m_level;
	ktk::int32_t m_internalformat;
	ktk::int32_t m_width;
	ktk::int32_t m_height;
	ktk::int32_t m_depth;
	ktk::int32_t m_border;
	ktk::uint32_t m_format;
};

/// \~english @brief backend-agnostic buffer target (replaces the former GL
/// constants GL_*_BUFFER; the render backends were removed 2026-07-22 and
/// shared types must not carry any GAPI types)
enum class eRenderGraphBufferObject : ktk::uint32_t
{
	kUniform = 0,
	kVertex,
	kIndex,
	kStorage
};

/// \~english @brief backend-agnostic buffer usage (replaces the former GL
/// constants GL_*_DRAW)
enum class eRenderGraphBufferUsage : ktk::uint32_t
{
	kStatic = 0,
	kDynamic
};

// todo: probably deleete it!
class ktkRenderGraphBufferInfo
{
public:
	ktkRenderGraphBufferInfo(eRenderGraphBufferObject type,
		eRenderGraphBufferUsage usage,
		const ktk::cstring& uniform_block_name, ktk::uint32_t binding_point,
		ktk::size_t memory_for_allocation, ktk::size_t align_of_memory,
		const ktk::ustring& shader_name, const ktk::cstring& buffer_name);

	ktkRenderGraphBufferInfo(void);
	~ktkRenderGraphBufferInfo(void);

	eRenderGraphBufferObject Get_BufferObject(void) const noexcept;
	eRenderGraphBufferUsage Get_Usage(void) const noexcept;
	ktk::uint32_t Get_BindingPointIndex(void) const noexcept;
	ktk::size_t Get_Memory(void) const noexcept;
	ktk::size_t Get_AlignOfMemory(void) const noexcept;

	const ktk::cstring& Get_UniformBlockName(void) const noexcept;
	const ktk::ustring& Get_ShaderName(void) const noexcept;
	const ktk::cstring& Get_BufferName(void) const noexcept;

private:
	/// \~english @brief backend-agnostic buffer target (uniform, vertex,
	/// index, storage)
	eRenderGraphBufferObject m_buffer_object;

	/// \~english @brief backend-agnostic buffer usage (static or dynamic)
	eRenderGraphBufferUsage m_usage;

	/// \~english @brief this is what you write in layout(std140, binding=index)
	/// where index is represented by this field (m_binding_point_index)
	ktk::uint32_t m_binding_point_index;

	/// \~english @brief how much memory should be allocated to this
	/// instance
	ktk::size_t m_memory;

	/// \~english @brief to what value you should align your buffer
	ktk::size_t m_memory_align_value;

	/// \~english @brief don't allocate buffers for shaders that are for
	/// vertecies and indecies
	ktk::cstring m_uniform_block_in_your_shader;

	/// \~english @brief debug buffer name that user defines
	ktk::cstring m_buffer_name;
#ifdef KOTEK_DEBUG
	/// \~english @brief When the development build is DEBUG it means that
	/// you can see to what shader this buffer is attached by its name
	ktk::ustring m_shader_name;
#endif
};

class ktkRenderGraphShaderTextInfo
{
public:
	explicit ktkRenderGraphShaderTextInfo(
		eShaderLoadingDataType type_loading_data,
		const ktk::ustring& shader_name,
		const ktk::ustring& path_to_file_or_source_code_string);

	explicit ktkRenderGraphShaderTextInfo(
		eShaderLoadingDataType type_loading_data,
		const ktk::ustring& shader_name, void* p_data);

	ktkRenderGraphShaderTextInfo(void);

	~ktkRenderGraphShaderTextInfo(void);

	eShaderLoadingDataType Get_Type(void) const noexcept;
	void Set_Type(eShaderLoadingDataType type) noexcept;

	const ktk::variant<void*, ktk::ustring>& Get_Data(void) const noexcept;
	void Set_Data(const ktk::variant<void*, ktk::ustring>& data) noexcept;

	bool Is_DataValid(void) const noexcept;

	const ktk::ustring& Get_ShaderName(void) const noexcept;

private:
	eShaderLoadingDataType m_type;
	ktk::ustring m_shader_name;
	ktk::variant<void*, ktk::ustring> m_data;
};

template <typename CreateInfoType>
class ktkRenderGraphResourceInfo
{
public:
	ktkRenderGraphResourceInfo(const ktk::ustring& render_pass_name,
		const ktk::ustring& resource_name, const CreateInfoType& info) :
		m_info{info},
		m_render_pass_name{render_pass_name}, m_resource_name{resource_name}
	{
	}

	ktkRenderGraphResourceInfo(void) : m_is_created_from_output{}, m_info{} {}

	~ktkRenderGraphResourceInfo(void) {}

	bool Is_CreatedFromOutput(void) const noexcept
	{
		return this->m_is_created_from_output;
	}

	void Set_CreatedFromOutput(bool status) noexcept
	{
		this->m_is_created_from_output = status;
	}

	void Set_Info(const CreateInfoType& info) noexcept { this->m_info = info; }

	const CreateInfoType& Get_Info(void) const noexcept { return this->m_info; }

	const ktk::ustring& Get_ResourceName(void) const noexcept
	{
		return this->m_resource_name;
	}

	void Set_ResourceName(const ktk::ustring& resource_name) noexcept
	{
		this->m_resource_name = resource_name;
	}

	const ktk::ustring& Get_RenderPassName(void) const noexcept
	{
		return this->m_render_pass_name;
	}

	void Set_RenderPassName(const ktk::ustring& render_pass_name) noexcept
	{
		this->m_render_pass_name = render_pass_name;
	}

private:
	bool m_is_created_from_output;
	CreateInfoType m_info;

	#ifdef KOTEK_DEBUG
	kun_ktk static_cstring<32> m_render_pass_name;
	kun_ktk static_cstring<32> m_resource_name;
	#endif
};

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
