#pragma once

#include "kotek_render_graph_simplified_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

// TODO: move to shared resources like in shared project, because
// implementation will be the same and will just shrink
class ktkRenderGraphSimplifiedStorageInput
{
public:
	ktkRenderGraphSimplifiedStorageInput(void);
	~ktkRenderGraphSimplifiedStorageInput(void);

	void Add_Image(const ktk::ustring& shader_name,
		const ktk::ustring& image_name,
		const gl::ktkRenderGraphTextureInfo& info_create) noexcept;

	const ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphTextureInfo>>&
	Get_Images(void) const noexcept;

	void Add_Buffer(const ktk::ustring& shader_name,
		const ktk::ustring& buffer_name,
		const gl::ktkRenderGraphBufferInfo& info_buffer) noexcept;

	const ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphBufferInfo>>&
	Get_Buffers(void) const noexcept;

	void Add_Shader(const ktk::ustring& user_name_for_access_in_the_code,
		eShaderType shader_type,
		const gl::ktkRenderGraphShaderTextInfo& info) noexcept;

	const ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>&
	Get_Shader(
		const ktk::ustring& user_name_for_access_in_the_code) const noexcept;

	const ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>>&
	Get_Shaders(void) const noexcept;

private:
	ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>>
		m_input_shaders;

	ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphTextureInfo>>
		m_input_textures;

	ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphBufferInfo>>
		m_input_buffers;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK