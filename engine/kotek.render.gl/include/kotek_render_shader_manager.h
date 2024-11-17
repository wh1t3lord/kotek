#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
class ktkRenderBuffer;
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_Vertex = "vert";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_Fragment = "frag";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_Compute = "comp";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_Task = "task";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_Mesh = "mesh";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_Geometry = "geom";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_TessellationEvaluation =
	"tese";
KOTEK_CPP_KEYWORD_CONSTEXPR const char* _kShaderPrefix_TessellationControl =
	"tesc";

class ktkRenderShaderManager
{
public:
	ktkRenderShaderManager(kun_core ktkMainManager* p_main_manager);
	~ktkRenderShaderManager(void);

	void Initialize(ktk::size_t value_in_bytes,
		bool is_support_reallocation_feature = false);
	void Shutdown(void);

	ktkShaderModule Create_Shader(const ktk_filesystem_path& absolute_path,
		gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT;
	ktkShaderModule Create_Shader(
		const ktk_filesystem_path& relative_to_glsl_folder_or_absolute_path)
		KOTEK_CPP_KEYWORD_NOEXCEPT;
	ktkShaderModule Create_Shader(
		kun_ktk static_cstring_base& static_string_view,
		const ktk_filesystem_path& path,
		gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT;
	ktkShaderModule Create_Shader(
		kun_ktk static_cstring_base& static_string_view,
		const ktk_filesystem_path& relative_to_glsl_folder_or_absolute_path)
		KOTEK_CPP_KEYWORD_NOEXCEPT;
	ktkShaderModule Create_ShaderAsString(
		const kun_ktk cstring_view& code_as_string,
		gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT;

	void Destroy_Shader(
		const ktkShaderModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT;

	ktkBufferModule Create_Buffer(kun_ktk size_t memory_in_bytes,
		GLenum buffer_object_type, GLenum usage, GLuint binding_point_in_shader
#ifdef KOTEK_DEBUG
		,
		const char* p_uniform_block_name_in_shader
#endif
		) KOTEK_CPP_KEYWORD_NOEXCEPT;
	void Destroy_Buffer(
		const ktkBufferModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT;

private:
	gl::eShaderType DetectType(
		const ktk::cstring& path_to_file) KOTEK_CPP_KEYWORD_NOEXCEPT;

private:
	bool m_is_reallocation_feature_supported;
	kun_ktk size_t m_total_memory;
	kun_ktk size_t m_current_memory;
	kun_core ktkMainManager* m_p_main_manager;
	kun_core ktkIFileSystem* m_p_filesystem;

#ifdef KOTEK_DEBUG
	// todo: provide switching between static (stack/embedded) implementation
	// and dynamic
	kun_ktk unordered_map<GLuint, bool> m_user_called_destroy_shaders;
	kun_ktk unordered_map<GLuint, bool> m_user_called_destroy_buffers;
#endif
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
