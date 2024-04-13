#include "../include/kotek_render_shader_manager.h"
#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>
#include "../include/kotek_render_buffer_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkRenderShaderManager::ktkRenderShaderManager(
	Core::ktkMainManager* p_main_manager) :
	m_is_reallocation_feature_supported{},
	m_total_memory{}, m_current_memory{}, m_p_main_manager{p_main_manager}
{
	KOTEK_ASSERT(p_main_manager, "must be valid");

	this->m_p_filesystem = p_main_manager->GetFileSystem();
}

ktkRenderShaderManager::~ktkRenderShaderManager(void) {}

// TODO: implement reallocation
void ktkRenderShaderManager::Initialize(
	ktk::size_t value_in_bytes, bool enable_reallocation_feature)
{
	this->m_is_reallocation_feature_supported = enable_reallocation_feature;
	this->m_total_memory = value_in_bytes;
	this->m_current_memory = this->m_total_memory;

#ifdef KOTEK_DEBUG
	auto p_translate_callback = [](bool val) -> const char*
	{
		if (val)
			return "enabled";
		else
			return "disabled";
	};

	KOTEK_MESSAGE("allocated memory for shader manager: {} Mb ({} Kb), "
				  "reallocation feature: {}",
		(static_cast<float>(value_in_bytes) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Megabytes)),
		(static_cast<float>(value_in_bytes) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Kilobytes)),
		p_translate_callback(enable_reallocation_feature));
#endif
}

void ktkRenderShaderManager::Shutdown(void) {}

ktkShaderModule ktkRenderShaderManager::LoadShader(
	const ktk_filesystem_path& path,
	gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	auto content = this->m_p_filesystem->ReadFile(path);

	return this->LoadShaderAsString(content, type);
}

ktkShaderModule ktkRenderShaderManager::LoadShader(
	const ktk_filesystem_path& path) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(path.empty() == false, "you can't pass an empty path to file");
	KOTEK_ASSERT(
		path.has_extension(), "you must pass filename with extension at least");

	ktkShaderModule result;

	auto real_path = path;
	if (!this->m_p_filesystem->IsValidPath(path))
	{
		// so you passed a name with extension

		// TODO: implement changing subfolder to any other custom, but does it
		// make any sense?
		auto path_to_folder = this->m_p_filesystem->GetFolderByEnum(
			Core::eFolderIndex::kFolderIndex_Shaders_GLSL);

		path_to_folder /= real_path;

		if (!this->m_p_filesystem->IsValidPath(path_to_folder))
		{
			KOTEK_ASSERT(false, "path is not valid at all!");
		}
		else
		{
			real_path = path_to_folder;
		}
	}

	const auto& utf8_path = real_path.u8string();

	auto type =
		this->DetectType(reinterpret_cast<const char*>(utf8_path.c_str()));

	KOTEK_ASSERT(
		type != eShaderType::kShaderType_Unknown, "failed to detect type");

	result = this->LoadShader(real_path, type);

	return result;
}

ktkShaderModule ktkRenderShaderManager::LoadShaderAsString(
	const ktk::ustring& code_as_string,
	gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(
		code_as_string.empty() == false, "you can't pass an empty string here");

	KOTEK_ASSERT(type != gl::eShaderType::kShaderType_Unknown,
		"you can't pass an unknown shader, you have to determine "
		"what is the shader's type (Vertex, Fragment and etc)");

	ktkShaderModule result;

	const char* p_str = reinterpret_cast<const char*>(code_as_string.c_str());

	GLuint shader_handle{};

	switch (type)
	{
	case gl::eShaderType::kShaderType_Vertex:
	{
		shader_handle = glCreateShader(GL_VERTEX_SHADER);
		break;
	}
	case gl::eShaderType::kShaderType_Fragment:
	{
		shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "other not implemented yet!");
		break;
	}
	}

	glShaderSource(shader_handle, 1, &p_str, nullptr);
	glCompileShader(shader_handle);

#ifdef KOTEK_DEBUG
	int success;
	char buffer[512];
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(shader_handle, sizeof(buffer), nullptr, buffer);

		KOTEK_ASSERT(false, "{}", buffer);
	}
#endif

	result.Set_Shader(type, shader_handle);

	return result;
}

void ktkRenderShaderManager::DestroyShader(
	const ktkShaderModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	if (instance.Get_ShaderType() != gl::eShaderType::kShaderType_Unknown)
	{
		glDeleteShader(instance.Get_Shader());
	}
#ifdef KOTEK_DEBUG
	else
	{
		KOTEK_ASSERT(false,
			"something is wrong and you got invalid shader module "
			"otherwise it means that your instance wasn't "
			"initialized properly, debug your loading procedures "
			"of shader manager");
	}
#endif
}

gl::eShaderType ktkRenderShaderManager::DetectType(
	const ktk::cstring& path_to_file) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING("you have an empty path, engine "
							  "can't detect type, [{}]",
			reinterpret_cast<const char*>(path_to_file.c_str()));
		return eShaderType::kShaderType_Unknown;
	}

	if (this->m_p_filesystem->IsValidPath(path_to_file) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"invalid path to file, can't analyze this path: [{}]",
			reinterpret_cast<const char*>(path_to_file.c_str()));
		return eShaderType::kShaderType_Unknown;
	}

	ktk_filesystem_path temp(path_to_file);

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("detecting shader for type: [{}]",
		reinterpret_cast<const char*>(path_to_file.c_str()));
#endif

	if (temp.has_filename())
	{
		const auto& filename = temp.filename();

		ktk::cstring temp_filename(filename.c_str());

		if (temp_filename.find(_kShaderPrefix_Vertex) != ktk::ustring::npos)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("detected: Vertex [{}]",
				static_cast<ktk::enum_base_t>(eShaderType::kShaderType_Vertex));
#endif

			return eShaderType::kShaderType_Vertex;
		}
		else if (temp_filename.find(_kShaderPrefix_Fragment) !=
			ktk::ustring::npos)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("detected: Pixel [{}]",
				static_cast<ktk::enum_base_t>(
					eShaderType::kShaderType_Fragment));
#endif

			return eShaderType::kShaderType_Fragment;
		}
		else if (temp_filename.find(_kShaderPrefix_Compute) !=
			ktk::ustring::npos)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("detected: Compute [{}]",
				static_cast<ktk::enum_base_t>(
					eShaderType::kShaderType_Compute));
#endif

			return eShaderType::kShaderType_Compute;
		}
		else
		{
			KOTEK_MESSAGE_WARNING(
				"can't detect shader type because we can't handle "
				"with this prefix or non prefixed file: [{}]",
				reinterpret_cast<const char*>(path_to_file.c_str()));

			return eShaderType::kShaderType_Unknown;
		}
	}
	else
	{
		KOTEK_MESSAGE_WARNING("you passed an invalid path without "
							  "destination file!!! [{}]",
			reinterpret_cast<const char*>(path_to_file.c_str()));

		return eShaderType::kShaderType_Unknown;
	}

	return gl::eShaderType::kShaderType_Unknown;
}

ktkBufferModule ktkRenderShaderManager::Create_Buffer(
	ktk::size_t memory_in_bytes, GLenum buffer_object_type, GLenum usage
#ifdef KOTEK_DEBUG
	,
	const ktkRenderGraphBufferInfo& info
#endif
	) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(memory_in_bytes != 0,
		"you can't pass 0 as memory count for allocation!");

	if (this->m_is_reallocation_feature_supported == false)
	{
		KOTEK_ASSERT(memory_in_bytes <= this->m_current_memory,
			"can't allocate buffer from shader manager because you are out of "
			"memory!");

		this->m_current_memory -= memory_in_bytes;
	}
	else
	{
		// TODO: implement reallocation
	}

	ktkBufferModule result;

	GLuint handle_id{};
	glGenBuffers(1, &handle_id);
	KOTEK_GL_ASSERT();
	glBindBuffer(buffer_object_type, handle_id);
	KOTEK_GL_ASSERT();
	glBufferData(buffer_object_type, memory_in_bytes, nullptr, usage);
	KOTEK_GL_ASSERT();
	glBindBuffer(buffer_object_type, 0);
	KOTEK_GL_ASSERT();

	result.Set_Buffer(buffer_object_type, handle_id);
	result.Set_BindingPointIndex(info.Get_BindingPointIndex());
	result.Set_UniformBlockName(info.Get_UniformBlockName());
#ifdef KOTEK_DEBUG
	result.Set_MemoryAlign(info.Get_AlignOfMemory());
	result.Set_AlignedMemoryForAllocation(memory_in_bytes);
	result.Set_NotAlignedMemoryForAllocation(info.Get_Memory());

	KOTEK_MESSAGE("allocated buffer: {} Kb ({} Mb) memory left: {} Mb ({} Kb)",
		(static_cast<float>(memory_in_bytes) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Kilobytes)),
		(static_cast<float>(memory_in_bytes) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Megabytes)),
		(static_cast<float>(this->m_current_memory) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Megabytes)),
		(static_cast<float>(this->m_current_memory) /
			static_cast<float>(ktk::kMemoryConvertValueDenominator_Kilobytes)));
#endif

	return result;
}

void ktkRenderShaderManager::Destroy_Buffer(
	const ktkBufferModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	auto handle_id = instance.Get_Buffer();
	glDeleteBuffers(1, &handle_id);
	KOTEK_GL_ASSERT();
}

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
