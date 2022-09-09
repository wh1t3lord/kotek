#include "../include/kotek_render_graph_simplified_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphShaderTextInfo::ktkRenderGraphShaderTextInfo(
				eShaderLoadingDataType type_loading_data,
				const ktk::string& path_to_file_or_source_code_string) :
				m_type{type_loading_data},
				m_data{path_to_file_or_source_code_string}
			{
			}

			ktkRenderGraphShaderTextInfo::ktkRenderGraphShaderTextInfo(
				eShaderLoadingDataType type_loading_data, void* p_data) :
				m_type{type_loading_data},
				m_data{p_data}
			{
			}

			ktkRenderGraphShaderTextInfo::ktkRenderGraphShaderTextInfo(void) :
				m_type{eShaderLoadingDataType::
						kShaderLoadingDataType_NotInitialized},
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

			const ktk::variant<void*, ktk::string>&
			ktkRenderGraphShaderTextInfo::Get_Data(void) const noexcept
			{
				return this->m_data;
			}

			void ktkRenderGraphShaderTextInfo::Set_Data(
				const ktk::variant<void*, ktk::string>& data) noexcept
			{
				this->m_data = data;
			}

			bool ktkRenderGraphShaderTextInfo::Is_DataValid(void) const noexcept
			{
				bool result{};

				if (this->m_type ==
					eShaderLoadingDataType::
						kShaderLoadingDataType_NotInitialized)
					return result;

				if (this->m_type ==
						eShaderLoadingDataType::
							kShaderLoadingDataType_FilePathString ||
					this->m_type ==
						eShaderLoadingDataType::
							kShaderLoadingDataType_SourceCode_TextString)
				{
					if (std::get<ktk::string>(this->m_data).empty() == false)
					{
						result = true;
					}
				}
				else if (this->m_type ==
						eShaderLoadingDataType::
							kShaderLoadingDataType_ByteArrayFile ||
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

			ktkRenderGraphBufferInfo::ktkRenderGraphBufferInfo(void) {}

			ktkRenderGraphBufferInfo::~ktkRenderGraphBufferInfo(void) {}

			ktkRenderGraphTextureInfo::ktkRenderGraphTextureInfo(void) :
				m_target{}, m_level{}, m_internalformat{}, m_width{},
				m_height{}, m_depth{}, m_border{}, m_format{}
			{
			}

			ktkRenderGraphTextureInfo::~ktkRenderGraphTextureInfo(void) {}

			GLenum ktkRenderGraphTextureInfo::Get_Target(void) const noexcept
			{
				return this->m_target;
			}

			void ktkRenderGraphTextureInfo::Set_Target(GLenum value) noexcept
			{
				this->m_target = value;
			}

			GLint ktkRenderGraphTextureInfo::Get_Level(void) const noexcept
			{
				return this->m_level;
			}

			void ktkRenderGraphTextureInfo::Set_Level(GLint value) noexcept
			{
				this->m_level = value;
			}

			GLint ktkRenderGraphTextureInfo::Get_InternalFormat(
				void) const noexcept
			{
				return this->m_internalformat;
			}

			GLsizei ktkRenderGraphTextureInfo::Get_Width(void) const noexcept
			{
				return this->m_width;
			}

			void ktkRenderGraphTextureInfo::Set_Width(GLsizei value) noexcept
			{
				this->m_width = value;
			}

			GLsizei ktkRenderGraphTextureInfo::Get_Height(void) const noexcept
			{
				return this->m_height;
			}

			void ktkRenderGraphTextureInfo::Set_Height(GLsizei value) noexcept
			{
				this->m_height = value;
			}

			GLsizei ktkRenderGraphTextureInfo::Get_Depth(void) const noexcept
			{
				return this->m_depth;
			}

			void ktkRenderGraphTextureInfo::Set_Depth(GLsizei value) noexcept
			{
				this->m_depth = value;
			}

			GLint ktkRenderGraphTextureInfo::Get_Border(void) const noexcept
			{
				return this->m_border;
			}
			void ktkRenderGraphTextureInfo::Set_Border(GLint value) noexcept
			{
				this->m_border = value;
			}

			GLenum ktkRenderGraphTextureInfo::Get_Format(void) const noexcept
			{
				return this->m_format;
			}

			void ktkRenderGraphTextureInfo::Set_Format(GLenum value) noexcept
			{
				this->m_format = value;
			}
		} // namespace gl
	}     // namespace Render
} // namespace Kotek