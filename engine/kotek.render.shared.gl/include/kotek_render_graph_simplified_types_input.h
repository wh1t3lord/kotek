#pragma once

#include "kotek_render_graph_simplified_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			// TODO: move to shared resources like in shared project, because
			// implementation will be the same and will just shrink
			class ktkRenderGraphSimplifiedStorageInput
			{
			public:
				ktkRenderGraphSimplifiedStorageInput(void);
				~ktkRenderGraphSimplifiedStorageInput(void);

				void Add_Image(const ktk::string& image_name,
					const gl::ktkRenderGraphTextureInfo& info_create) noexcept;

				const ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>&
				Get_Images(void) const noexcept;

				void Add_Buffer(const ktk::string& buffer_name,
					const gl::ktkRenderGraphBufferInfo& info_buffer) noexcept;

				const ktk::unordered_map<ktk::string,
					gl::ktkRenderGraphBufferInfo>&
				Get_Buffers(void) const noexcept;

			private:
				ktk::unordered_map<ktk::string,
					ktk::unordered_map<eShaderType,
						gl::ktkRenderGraphShaderTextInfo>>
					m_input_shaders;

				ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>
					m_input_textures;

				ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>
					m_input_buffers;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek