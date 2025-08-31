#include "../include/kotek_render_shader_manager.h"
#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>
#include "../include/kotek_render_buffer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

ktkRenderShaderManager::ktkRenderShaderManager(
	Core::ktkMainManager* p_main_manager) :
	m_is_reallocation_feature_supported{}, m_total_memory{}, m_current_memory{},
	m_p_main_manager{p_main_manager}
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

void ktkRenderShaderManager::Shutdown(void)
{
#ifdef KOTEK_DEBUG
	bool deleted_all_shaders = true;
	for (const auto& [shader_handle_id, delete_status] :
		this->m_user_called_destroy_shaders)
	{
		if (delete_status == false)
		{
			deleted_all_shaders = false;
			KOTEK_ASSERT(delete_status,
				"forgot to call Destroy_Shader from shader manager! Shader "
				"handle: {}",
				shader_handle_id);
		}
	}

	KOTEK_ASSERT(deleted_all_shaders,
		"you forget to issue Destroy_Shader calling in your renderer "
		"implementation! Not all shader resources are destroyed!!!");

	bool deleted_all_buffers = true;
	for (const auto& [buffer_handle_id, delete_status] :
		this->m_user_called_destroy_buffers)
	{
		if (delete_status == false)
		{
			deleted_all_buffers = false;
			KOTEK_ASSERT(delete_status,
				"forgot to call Destroy_Buffer from shader manager! Buffer "
				"handle: {}",
				buffer_handle_id);
		}
	}

	KOTEK_ASSERT(deleted_all_buffers,
		"you forget to issue Destroy_Buffer calling in your renderer "
		"implementation! Not all shader's buffer resources are destroyed!!!");

	bool deleted_all_programs = true;
	for (const auto& [program_handle_id, delete_status] :
		this->m_user_called_destroy_programs)
	{
		if (delete_status == false)
		{
			KOTEK_ASSERT(delete_status,
				"forgot to call Destroy_Program from shader manager! Program "
				"handle: {}",
				program_handle_id);
		}
	}

	KOTEK_ASSERT(deleted_all_programs,
		"you forget to issue Destroy_Program calling in your renderer "
		"implementation! Not all programs resources are destroyed!!!");
#endif
}

ktkShaderModule ktkRenderShaderManager::Create_Shader(
	const ktk_filesystem_path& absolute_path,
	gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	kun_ktk ustring content;

	bool status = this->m_p_filesystem->Read_File(absolute_path, content);

	KOTEK_ASSERT(status, "failed to read file!");

	KOTEK_ASSERT(content.empty(),
		"failed to read file: {} or file's content is empty!", absolute_path);

	return this->Create_ShaderAsString(content, type);
}

ktkShaderModule ktkRenderShaderManager::Create_Shader(
	const ktk_filesystem_path& relative_to_glsl_folder_or_absolute_path)
	KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(relative_to_glsl_folder_or_absolute_path.empty() == false,
		"you can't pass an empty path to file");
	KOTEK_ASSERT(relative_to_glsl_folder_or_absolute_path.has_extension(),
		"you must pass filename with extension at least");

	ktkShaderModule result;

	auto real_path = relative_to_glsl_folder_or_absolute_path;
	if (!this->m_p_filesystem->IsValidPath(
			relative_to_glsl_folder_or_absolute_path))
	{
		// so you passed a name with extension

		// TODO: implement changing subfolder to any other custom, but does it
		// make any sense?
		auto path_to_folder = this->m_p_filesystem->GetFolderByEnum(
			Core::eFolderIndex::kFolderIndex_DataGame_Shaders_GLSL);

		path_to_folder /= real_path;

		if (!this->m_p_filesystem->IsValidPath(path_to_folder))
		{
			KOTEK_ASSERT(false, "path is not valid at all!");
			KOTEK_MESSAGE_ERROR("failed to load file by path: {} the file "
								"doesn't present on disk!",
				path_to_folder);
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

	result = this->Create_Shader(real_path, type);

	return result;
}

ktkShaderModule ktkRenderShaderManager::Create_Shader(
	kun_ktk static_cstring_base& static_string_view,
	const ktk_filesystem_path& absolute_path,
	gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	char* p_temporary_reference = static_string_view.begin();
	size_t size_of_buffer = static_string_view.max_size();
	size_t prev_size = size_of_buffer;
	auto status = this->m_p_filesystem->Read_File(
		absolute_path, p_temporary_reference, size_of_buffer);

#ifdef KOTEK_DEBUG
	if (size_of_buffer > prev_size)
	{
		KOTEK_MESSAGE_WARNING("can't read file with stack buffer size: {} "
							  "required size for reading: {}. Update your "
							  "stack buffer size up to {} please.",
			prev_size, size_of_buffer, size_of_buffer);
	}
#endif

	if (size_of_buffer < prev_size)
		static_string_view[size_of_buffer] = '\0';

	KOTEK_ASSERT(status, "failed to read shader by path: {}", absolute_path);

	return this->Create_ShaderAsString(p_temporary_reference, type);
}

ktkShaderModule ktkRenderShaderManager::Create_Shader(
	kun_ktk static_cstring_base& static_string_view,
	const ktk_filesystem_path& relative_to_glsl_folder_or_absolute_path)
	KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(static_string_view.data(), "must be a valid data!");
	KOTEK_ASSERT(static_string_view.max_size(), "size must be non-zero!");

	ktkShaderModule result;

	auto real_path = relative_to_glsl_folder_or_absolute_path;
	if (!this->m_p_filesystem->IsValidPath(
			relative_to_glsl_folder_or_absolute_path))
	{
		auto path_to_folder = this->m_p_filesystem->GetFolderByEnum(
			kun_core eFolderIndex::kFolderIndex_DataGame_Shaders_GLSL);

		path_to_folder /= real_path;

		if (!this->m_p_filesystem->IsValidPath(path_to_folder))
		{
			KOTEK_ASSERT(false,
				"path is not valid at all! tried to construct as relative to "
				"absolute, but there's no file {}",
				path_to_folder);
			KOTEK_MESSAGE_ERROR("failed to load shader file by path: {} path "
								"doesn't present on disk",
				path_to_folder);
		}
		else
		{
			real_path = path_to_folder;
		}
	}

	const auto& utf8_path = real_path.u8string();

	auto type =
		this->DetectType(reinterpret_cast<const char*>(utf8_path.c_str()));

	KOTEK_ASSERT(type != eShaderType::kShaderType_Unknown,
		"failed to detect the type of shader by path {}!",
		reinterpret_cast<const char*>(utf8_path.c_str()));

	result = this->Create_Shader(static_string_view, real_path, type);

	return result;
}

ktkShaderModule ktkRenderShaderManager::Create_ShaderAsString(
	const kun_ktk cstring_view& code_as_string,
	gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(
		code_as_string.empty() == false, "you can't pass an empty string here");

	KOTEK_ASSERT(type != gl::eShaderType::kShaderType_Unknown,
		"you can't pass an unknown shader, you have to determine "
		"what is the shader's type (Vertex, Fragment and etc)");

	ktkShaderModule result;

	const char* p_str = reinterpret_cast<const char*>(code_as_string.data());

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

#ifdef KOTEK_DEBUG
	this->m_user_called_destroy_shaders[shader_handle] = false;
#endif

	return result;
}

GLuint ktkRenderShaderManager::Create_Program(
	const ktkShaderModule& shader_vertex,
	const ktkShaderModule& shader_pixel) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	GLuint program = glCreateProgram();
	KOTEK_GL_ASSERT();

	glAttachShader(program, shader_vertex.Get_Shader());
	KOTEK_GL_ASSERT();

	glAttachShader(program, shader_pixel.Get_Shader());
	KOTEK_GL_ASSERT();

	glLinkProgram(program);
	KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		char info[512];
		glGetProgramInfoLog(program, 512, nullptr, info);
		KOTEK_GL_ASSERT();

		KOTEK_MESSAGE_ERROR("failed to create program: {}", info);
	}

	this->m_user_called_destroy_programs[program] = false;
#endif

	return program;
}

void ktkRenderShaderManager::Destroy_Program(
	GLuint program) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	glDeleteProgram(program);
	KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
	if (this->m_user_called_destroy_programs.find(program) !=
		this->m_user_called_destroy_programs.end())
	{
		this->m_user_called_destroy_programs[program] = true;
	}
#endif
}

void ktkRenderShaderManager::Destroy_Shader(
	const ktkShaderModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	if (instance.Get_ShaderType() != gl::eShaderType::kShaderType_Unknown)
	{
		glDeleteShader(instance.Get_Shader());
		KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
		if (this->m_user_called_destroy_shaders.find(instance.Get_Shader()) !=
			this->m_user_called_destroy_shaders.end())
		{
			this->m_user_called_destroy_shaders[instance.Get_Shader()] = true;
		}
#endif
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
	kun_ktk size_t memory_in_bytes, GLenum buffer_object_type, GLenum usage,
	GLuint binding_point_in_shader
#ifdef KOTEK_DEBUG
	,
	const char* p_uniform_block_name_in_shader
#endif

	) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_ASSERT(memory_in_bytes != 0,
		"you can't pass 0 as memory count for allocation!");

#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(p_uniform_block_name_in_shader,
		"don't pass an empty name in debug please!");
#endif

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
	result.Set_BindingPointIndex(binding_point_in_shader);

#ifdef KOTEK_DEBUG
	result.Set_UniformBlockName(p_uniform_block_name_in_shader);
	KOTEK_MESSAGE("allocated buffer: {} Kb ({} Mb) memory left: {} Mb ({} Kb)",
		(static_cast<float>(memory_in_bytes) /
			static_cast<float>(
				kun_ktk kMemoryConvertValueDenominator_Kilobytes)),
		(static_cast<float>(memory_in_bytes) /
			static_cast<float>(
				kun_ktk kMemoryConvertValueDenominator_Megabytes)),
		(static_cast<float>(this->m_current_memory) /
			static_cast<float>(
				kun_ktk kMemoryConvertValueDenominator_Megabytes)),
		(static_cast<float>(this->m_current_memory) /
			static_cast<float>(
				kun_ktk kMemoryConvertValueDenominator_Kilobytes)));

	this->m_user_called_destroy_buffers[handle_id] = false;
#endif

	return result;
}

void ktkRenderShaderManager::Destroy_Buffer(
	const ktkBufferModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	auto handle_id = instance.Get_Buffer();
	glDeleteBuffers(1, &handle_id);
	KOTEK_GL_ASSERT();

#ifdef KOTEK_DEBUG
	if (this->m_user_called_destroy_buffers.find(handle_id) !=
		this->m_user_called_destroy_buffers.end())
	{
		this->m_user_called_destroy_buffers[handle_id] = true;
	}
#endif
}

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
