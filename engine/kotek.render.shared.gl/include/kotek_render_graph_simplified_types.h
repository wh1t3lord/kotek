#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			enum class eShaderLoadingDataType;
			enum class eShaderType;
		} // namespace gl
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraphTextureInfo
			{
			public:
				ktkRenderGraphTextureInfo(void);
				~ktkRenderGraphTextureInfo(void);

				GLenum Get_Target(void) const noexcept;
				void Set_Target(GLenum value) noexcept;

				GLint Get_Level(void) const noexcept;
				void Set_Level(GLint value) noexcept;

				GLint Get_InternalFormat(void) const noexcept;

				GLsizei Get_Width(void) const noexcept;
				void Set_Width(GLsizei value) noexcept;

				GLsizei Get_Height(void) const noexcept;
				void Set_Height(GLsizei value) noexcept;

				GLsizei Get_Depth(void) const noexcept;
				void Set_Depth(GLsizei value) noexcept;

				GLint Get_Border(void) const noexcept;
				void Set_Border(GLint value) noexcept;

				GLenum Get_Format(void) const noexcept;
				void Set_Format(GLenum value) noexcept;

			private:
				GLenum m_target;
				GLint m_level;
				GLint m_internalformat;
				GLsizei m_width;
				GLsizei m_height;
				GLsizei m_depth;
				GLint m_border;
				GLenum m_format;
			};

			class ktkRenderGraphBufferInfo
			{
			public:
				ktkRenderGraphBufferInfo(void);
				~ktkRenderGraphBufferInfo(void);

			private:
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

				const ktk::variant<void*, ktk::string>& Get_Data(
					void) const noexcept;
				void Set_Data(
					const ktk::variant<void*, ktk::string>& data) noexcept;

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
					const ktk::string& resource_name,
					const CreateInfoType& info) :
					m_info{info},
					m_render_pass_name{render_pass_name}, m_resource_name{
															  resource_name}
				{
				}

				ktkRenderGraphResourceInfo(void) :
					m_is_created_from_output{}, m_info{}
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

				void Set_RenderPassName(
					const ktk::string& render_pass_name) noexcept
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
	}     // namespace Render
} // namespace Kotek