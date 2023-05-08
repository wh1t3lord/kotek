#pragma once

#include "kotek_render_graph_simplified_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
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

		/// \~english @brief use this when you want to allocate some buffer for
		/// shader that you allocate through Add_Shader method
		/// @param shader_name to what shader we need to allocate the buffer
		/// @param info_buffer data about your buffer see
		/// ktkRenderGraphBufferInfo class
		void Add_Buffer(const ktk::string& shader_name,
			const gl::ktkRenderGraphBufferInfo& info_buffer) noexcept;

		const ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>&
		Get_Buffers(void) const noexcept;

		void Add_Shader(const ktk::string& user_name_for_access_in_the_code,
			eShaderType shader_type,
			const gl::ktkRenderGraphShaderTextInfo& info) noexcept;

		const ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>&
		Get_Shader(
			const ktk::string& user_name_for_access_in_the_code) const noexcept;

		const ktk::unordered_map<ktk::string,
			ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>>&
		Get_Shaders(void) const noexcept;

	private:
		ktk::unordered_map<ktk::string,
			ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>>
			m_input_shaders;

		ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>
			m_input_textures;

		ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>
			m_input_buffers;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK