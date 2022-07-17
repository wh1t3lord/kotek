#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			enum class eShaderLoadingDataType;
			enum class eShaderType;
		}
	} // namespace Render
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

			private:
				eShaderLoadingDataType m_type;
				ktk::variant<void*, ktk::string> m_data;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek