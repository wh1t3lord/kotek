#include "../include/kotek_render_graph_simplified_types_input.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphSimplifiedStorageInput::
				ktkRenderGraphSimplifiedStorageInput(void)
			{
			}

			ktkRenderGraphSimplifiedStorageInput::
				~ktkRenderGraphSimplifiedStorageInput(void)
			{
			}

			void ktkRenderGraphSimplifiedStorageInput::Add_Image(
				const ktk::string& image_name,
				const gl::ktkRenderGraphTextureInfo& info_create) noexcept
			{
				KOTEK_ASSERT(image_name.empty() == false,
					"you can't pass an empty image name for registration!");

				KOTEK_ASSERT(this->m_input_textures.find(image_name) ==
						this->m_input_textures.end(),
					"you must have a unique and unregistered image, found a "
					"duplicate: {}",
					image_name.get_as_is());

				this->m_input_textures[image_name] = info_create;
			}

			const ktk::unordered_map<ktk::string,
				gl::ktkRenderGraphTextureInfo>&
			ktkRenderGraphSimplifiedStorageInput::Get_Images(
				void) const noexcept
			{
				return this->m_input_textures;
			}

			void ktkRenderGraphSimplifiedStorageInput::Add_Buffer(
				const ktk::string& buffer_name,
				const gl::ktkRenderGraphBufferInfo& info_buffer) noexcept
			{
				KOTEK_ASSERT(buffer_name.empty() == false,
					"you can't pass an empty buffer name for "
					"registration!");

				// TODO: implement this
			}

			const ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>&
			ktkRenderGraphSimplifiedStorageInput::Get_Buffers(
				void) const noexcept
			{
				return this->m_input_buffers;
			}

			void ktkRenderGraphSimplifiedStorageInput::Add_Shader(
				const ktk::string& user_name_for_access_in_the_code,
				eShaderType shader_type,
				const gl::ktkRenderGraphShaderTextInfo& info) noexcept
			{
				KOTEK_ASSERT(user_name_for_access_in_the_code.empty() == false,
					"can't add an empty string");

				KOTEK_ASSERT(this->m_input_shaders.find(
								 user_name_for_access_in_the_code) ==
						this->m_input_shaders.end(),
					"found duplicate name in the map: {}",
					user_name_for_access_in_the_code);

				KOTEK_ASSERT(shader_type != eShaderType::kShaderType_Unknown,
					"you can't pass an invalid shader type here");

				KOTEK_ASSERT(info.Is_DataValid(),
					"data is not valid check your class please, your type in "
				    "class is {}",
					helper::Translate_ShaderLoadingDataType(info.Get_Type()));
			}

			const ktk::unordered_map<eShaderType,
				gl::ktkRenderGraphShaderTextInfo>&
			ktkRenderGraphSimplifiedStorageInput::Get_Shader(
				const ktk::string& user_name_for_access_in_the_code)
				const noexcept
			{
			}

			const ktk::unordered_map<ktk::string,
				ktk::unordered_map<eShaderType,
					gl::ktkRenderGraphShaderTextInfo>>&
			ktkRenderGraphSimplifiedStorageInput::Get_Shaders(
				void) const noexcept
			{
			}

		} // namespace gl
	}     // namespace Render
} // namespace Kotek