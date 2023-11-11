#include "../include/kotek_render_graph_simplified_types_input.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkRenderGraphSimplifiedStorageInput::ktkRenderGraphSimplifiedStorageInput(void)
{
}

ktkRenderGraphSimplifiedStorageInput::~ktkRenderGraphSimplifiedStorageInput(
	void)
{
}

void ktkRenderGraphSimplifiedStorageInput::Add_Image(
	const ktk::ustring& shader_name, const ktk::ustring& image_name,
	const gl::ktkRenderGraphTextureInfo& info_create) noexcept
{
	KOTEK_ASSERT(shader_name.empty() == false,
		"can't register because shader name is empty");

	KOTEK_ASSERT(image_name.empty() == false,
		"you can't pass an empty image name for registration!");

	KOTEK_ASSERT(
		this->m_input_textures.find(image_name) == this->m_input_textures.end(),
		"you must have a unique and unregistered image, found a "
		"duplicate: {}",
		reinterpret_cast<const char*>(image_name.c_str()));

	auto& map_image_name_and_info = this->m_input_textures[shader_name];

	if (map_image_name_and_info.find(image_name) ==
		map_image_name_and_info.end())
	{
		map_image_name_and_info[image_name] = info_create;

#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("added texture {} to shader {}", shader_name, image_name);
#endif
	}
	else
	{
		KOTEK_ASSERT(false, "you overwrite information");
	}
}

const ktk::unordered_map<ktk::ustring,
	ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphTextureInfo>>&
ktkRenderGraphSimplifiedStorageInput::Get_Images(void) const noexcept
{
	return this->m_input_textures;
}

void ktkRenderGraphSimplifiedStorageInput::Add_Buffer(
	const ktk::ustring& shader_name, const ktk::ustring& buffer_name,
	const gl::ktkRenderGraphBufferInfo& info_buffer) noexcept
{
#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(info_buffer.Get_BufferName().empty() == false,
		"you must define some name for your buffer!");
#endif

	KOTEK_ASSERT(shader_name.empty() == false,
		"we can't detect to what shader you want to allocate the buffer!");

	KOTEK_ASSERT(info_buffer.Get_BufferObject() != GL_ARRAY_BUFFER,
		"you must not pass this thing here");
	KOTEK_ASSERT(info_buffer.Get_BufferObject() != GL_ELEMENT_ARRAY_BUFFER,
		"you must not pass this thing here");

	auto& map_buffer_name_and_info = this->m_input_buffers[shader_name];

	if (this->m_input_buffers.find(buffer_name) == this->m_input_buffers.end())
	{
		map_buffer_name_and_info[buffer_name] = info_buffer;

#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("added buffer {} to shader {}", buffer_name, shader_name);
#endif
	}
	else
	{
		KOTEK_ASSERT(false, "can't overwrite existed buffer {}",
			info_buffer.Get_BufferName());
	}
}

const ktk::unordered_map<ktk::ustring,
	ktk::unordered_map<ktk::ustring, gl::ktkRenderGraphBufferInfo>>&
ktkRenderGraphSimplifiedStorageInput::Get_Buffers(void) const noexcept
{
	return this->m_input_buffers;
}

void ktkRenderGraphSimplifiedStorageInput::Add_Shader(
	const ktk::ustring& user_name_for_access_in_the_code,
	eShaderType shader_type,
	const gl::ktkRenderGraphShaderTextInfo& info) noexcept
{
	KOTEK_ASSERT(user_name_for_access_in_the_code.empty() == false,
		"can't add an empty string");

	KOTEK_ASSERT(shader_type != eShaderType::kShaderType_Unknown,
		"you can't pass an invalid shader type here");

	KOTEK_ASSERT(info.Is_DataValid(),
		"data is not valid check your class please, your type in "
		"class is {}",
		helper::Translate_ShaderLoadingDataType(info.Get_Type()));

	KOTEK_ASSERT(info.Get_ShaderName().empty() == false,
		"shader name must be valid (not empty)!");

#ifdef KOTEK_DEBUG
	if (this->m_input_shaders.find(user_name_for_access_in_the_code) !=
		this->m_input_shaders.end())
	{
		if (this->m_input_shaders.at(user_name_for_access_in_the_code)
				.find(info.Get_ShaderName()) !=
			this->m_input_shaders.at(user_name_for_access_in_the_code).end())
		{
			KOTEK_ASSERT(
				this->m_input_shaders.at(user_name_for_access_in_the_code)
						.at(info.Get_ShaderName())
						.find(shader_type) ==
					this->m_input_shaders.at(user_name_for_access_in_the_code)
						.at(info.Get_ShaderName())
						.end(),
				"found duplicate by shader type: {}",
				helper::Translate_ShaderType(shader_type));
		}
	}
#endif

	this->m_input_shaders[user_name_for_access_in_the_code]
						 [info.Get_ShaderName()][shader_type] = info;
}

const ktk::unordered_map<ktk::ustring,
	ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>>&
ktkRenderGraphSimplifiedStorageInput::Get_Shader(
	const ktk::ustring& user_name_for_access_in_the_code) const noexcept
{
	KOTEK_ASSERT(user_name_for_access_in_the_code.empty() == false,
		"you can't pass an empty string here");

	KOTEK_ASSERT(this->m_input_shaders.find(user_name_for_access_in_the_code) !=
			this->m_input_shaders.end(),
		"can't find the specified shader name in the map: {}",
		reinterpret_cast<const char*>(
			user_name_for_access_in_the_code.c_str()));

	return this->m_input_shaders.at(user_name_for_access_in_the_code);
}

const ktk::unordered_map<ktk::ustring,
	ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<eShaderType, gl::ktkRenderGraphShaderTextInfo>>>&
ktkRenderGraphSimplifiedStorageInput::Get_Shaders(void) const noexcept
{
	return this->m_input_shaders;
}

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
