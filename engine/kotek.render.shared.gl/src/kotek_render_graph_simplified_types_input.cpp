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
		} // namespace gl
	}     // namespace Render
} // namespace Kotek