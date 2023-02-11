#include "../include/kotek_render_graph_simplified_types_output.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

namespace gl
{
	ktkRenderGraphSimplifiedStorageOutput::
		ktkRenderGraphSimplifiedStorageOutput(void) :
		m_is_use_backbuffer_by_default{true}
	{
	}

	ktkRenderGraphSimplifiedStorageOutput::
		~ktkRenderGraphSimplifiedStorageOutput(void)
	{
	}

	void ktkRenderGraphSimplifiedStorageOutput::Add_Buffer(
		const ktk::string& buffer_name,
		const gl::ktkRenderGraphBufferInfo& info) noexcept
	{
		KOTEK_ASSERT(buffer_name.empty() == false,
			"you can't pass an empty buffer name");

		KOTEK_ASSERT(this->m_output_buffers.find(buffer_name) ==
				this->m_output_buffers.end(),
            "you can't add a duplicate: {}",
            reinterpret_cast<const char*>(buffer_name.c_str()));

        this->m_output_buffers[buffer_name] = info;
	}

	const ktk::unordered_map<ktk::string, gl::ktkRenderGraphBufferInfo>&
	ktkRenderGraphSimplifiedStorageOutput::Get_Buffers(void) const noexcept
	{
		return this->m_output_buffers;
	}

	void ktkRenderGraphSimplifiedStorageOutput::Add_Image(
		const ktk::string& image_name,
		const gl::ktkRenderGraphTextureInfo& info) noexcept
	{
		KOTEK_ASSERT(
			image_name.empty() == false, "you can't pass an empty image name");
		KOTEK_ASSERT(this->m_output_textures.find(image_name) ==
				this->m_output_textures.end(),
            "you can't add the duplicate: {}",
            reinterpret_cast<const char*>(image_name.c_str()));

        this->m_output_textures[image_name] = info;
	}

	const ktk::unordered_map<ktk::string, gl::ktkRenderGraphTextureInfo>&
	ktkRenderGraphSimplifiedStorageOutput::Get_Images(void) const noexcept
	{
		return this->m_output_textures;
	}

	void ktkRenderGraphSimplifiedStorageOutput::Set_UseBackBuffer(
		bool status) noexcept
	{
		this->m_is_use_backbuffer_by_default = status;
	}

	bool ktkRenderGraphSimplifiedStorageOutput::Is_UseBackBuffer(
		void) const noexcept
	{
		return this->m_is_use_backbuffer_by_default;
	}

	bool ktkRenderGraphSimplifiedStorageOutput::Empty(void) const noexcept
	{
		return this->m_output_buffers.empty() &&
			this->m_output_textures.empty();
	}
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
