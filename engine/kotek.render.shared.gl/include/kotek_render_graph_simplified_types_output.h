#pragma once

#include "kotek_render_graph_simplified_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gl
{
	class ktkRenderGraphSimplifiedStorageOutput
	{
	public:
		ktkRenderGraphSimplifiedStorageOutput(void);
		~ktkRenderGraphSimplifiedStorageOutput(void);

		void Add_Buffer(const ktk::string& buffer_name,
			const gl::ktkRenderGraphBufferInfo& info) noexcept;
		const ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>&
		Get_Buffers(void) const noexcept;

		void Add_Image(const ktk::string& image_name,
			const gl::ktkRenderGraphTextureInfo& info) noexcept;
		const ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>&
		Get_Images(void) const noexcept;

		void Set_UseBackBuffer(bool status) noexcept;
		bool Is_UseBackBuffer(void) const noexcept;

		bool Empty(void) const noexcept;

	private:
		bool m_is_use_backbuffer_by_default;
		ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>
			m_output_textures;
		ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>
			m_output_buffers;
	};
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK