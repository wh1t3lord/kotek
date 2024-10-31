#pragma once

#include "kotek_render_graph_simplified_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

	class ktkRenderGraphSimplifiedStorageOutput
	{
	public:
		ktkRenderGraphSimplifiedStorageOutput(void);
		~ktkRenderGraphSimplifiedStorageOutput(void);

		void Add_Buffer(const ktk::ustring& buffer_name,
			const gl::ktkRenderGraphBufferInfo& info) noexcept;
		const ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphBufferInfo>&
		Get_Buffers(void) const noexcept;

		void Add_Image(const ktk::ustring& image_name,
			const gl::ktkRenderGraphTextureInfo& info) noexcept;
		const ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphTextureInfo>&
		Get_Images(void) const noexcept;

		void Set_UseBackBuffer(bool status) noexcept;
		bool Is_UseBackBuffer(void) const noexcept;

		bool Empty(void) const noexcept;

	private:
		bool m_is_use_backbuffer_by_default;
		ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphTextureInfo>
			m_output_textures;
		ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphBufferInfo>
			m_output_buffers;
	};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK