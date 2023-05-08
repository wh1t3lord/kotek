#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	enum class eShaderLoadingDataType;
	enum class eShaderType;
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
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

	class ktkRenderGraphBufferInfo
	{
	public:
		ktkRenderGraphBufferInfo(GLenum type, GLenum usage,
			const ktk::cstring& uniform_block_name,
			ktk::size_t memory_for_allocation, ktk::size_t align_of_memory,
			const ktk::string& shader_name, const ktk::cstring& buffer_name);

		ktkRenderGraphBufferInfo(void);
		~ktkRenderGraphBufferInfo(void);

		GLenum Get_BufferObject(void) const noexcept;
		GLenum Get_Usage(void) const noexcept;
		ktk::size_t Get_Memory(void) const noexcept;
		ktk::size_t Get_AlignOfMemory(void) const noexcept;

		const ktk::cstring& Get_UniformBlockName(void) const noexcept;
		const ktk::string& Get_ShaderName(void) const noexcept;
		const ktk::cstring& Get_BufferName(void) const noexcept;

	private:
		/// \~english @brief buffer object in OpenGL see this
		/// https://www.khronos.org/opengl/wiki/Buffer_Object#:~:text=Buffer%20Objects%20are%20OpenGL%20Objects%20that%20store%20an%20array%20of%20unformatted%20memory%20allocated%20by%20the%20OpenGL%20context%20(AKA%20the%20GPU).%20These%20can%20be%20used%20to%20store%20vertex%20data%2C%20pixel%20data%20retrieved%20from%20images%20or%20the%20framebuffer%2C%20and%20a%20variety%20of%20other%20things.
		GLenum m_buffer_object;

		/// \~english @brief you specify usage of this field like GL_STATIC_DRAW
		/// and etc see this
		/// https://www.khronos.org/opengl/wiki/Buffer_Object#:~:text=There%20are%20three%20hints%20for%20how%20frequently%20the%20user%20will%20be%20changing%20the%20buffer%27s%20data.
		GLenum m_usage;

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
		ktk::string m_shader_name;
#endif
	};

	class ktkRenderGraphShaderTextInfo
	{
	public:
		explicit ktkRenderGraphShaderTextInfo(
			eShaderLoadingDataType type_loading_data,
			const ktk::string& path_to_file_or_source_code_string);

		explicit ktkRenderGraphShaderTextInfo(
			eShaderLoadingDataType type_loading_data, void* p_data);

		ktkRenderGraphShaderTextInfo(void);

		~ktkRenderGraphShaderTextInfo(void);

		eShaderLoadingDataType Get_Type(void) const noexcept;
		void Set_Type(eShaderLoadingDataType type) noexcept;

		const ktk::variant<void*, ktk::string>& Get_Data(void) const noexcept;
		void Set_Data(const ktk::variant<void*, ktk::string>& data) noexcept;

		bool Is_DataValid(void) const noexcept;

	private:
		eShaderLoadingDataType m_type;
		ktk::variant<void*, ktk::string> m_data;
	};

	template <typename CreateInfoType>
	class ktkRenderGraphResourceInfo
	{
	public:
		ktkRenderGraphResourceInfo(const ktk::string& render_pass_name,
			const ktk::string& resource_name, const CreateInfoType& info) :
			m_info{info},
			m_render_pass_name{render_pass_name}, m_resource_name{resource_name}
		{
		}

		ktkRenderGraphResourceInfo(void) : m_is_created_from_output{}, m_info{}
		{
		}

		~ktkRenderGraphResourceInfo(void) {}

		bool Is_CreatedFromOutput(void) const noexcept
		{
			return this->m_is_created_from_output;
		}

		void Set_CreatedFromOutput(bool status) noexcept
		{
			this->m_is_created_from_output = status;
		}

		void Set_Info(const CreateInfoType& info) noexcept
		{
			this->m_info = info;
		}

		const CreateInfoType& Get_Info(void) const noexcept
		{
			return this->m_info;
		}

		const ktk::string& Get_ResourceName(void) const noexcept
		{
			return this->m_resource_name;
		}

		void Set_ResourceName(const ktk::string& resource_name) noexcept
		{
			this->m_resource_name = resource_name;
		}

		const ktk::string& Get_RenderPassName(void) const noexcept
		{
			return this->m_render_pass_name;
		}

		void Set_RenderPassName(const ktk::string& render_pass_name) noexcept
		{
			this->m_render_pass_name = render_pass_name;
		}

	private:
		bool m_is_created_from_output;
		CreateInfoType m_info;
		ktk::string m_render_pass_name;
		ktk::string m_resource_name;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
