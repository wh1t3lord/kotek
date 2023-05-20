#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
class ktkRenderBufferManager;
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
	ktkRenderShaderManager(Core::ktkMainManager* p_main_manager);
	~ktkRenderShaderManager(void);

	void Initialize(ktk::size_t value_in_bytes,
		bool is_support_reallocation_feature = false);
	void Shutdown(void);

	ktkShaderModule LoadShader(const ktk::filesystem::path& path,
		gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT;
	ktkShaderModule LoadShader(
		const ktk::filesystem::path& path) KOTEK_CPP_KEYWORD_NOEXCEPT;
	ktkShaderModule LoadShaderAsString(const ktk::ustring& code_as_string,
		gl::eShaderType type) KOTEK_CPP_KEYWORD_NOEXCEPT;

	void DestroyShader(
		const ktkShaderModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT;

	ktkBufferModule Create_Buffer(
		ktk::size_t memory_in_bytes, GLenum buffer_object_type, GLenum usage
#ifdef KOTEK_DEBUG
		,
		const ktkRenderGraphBufferInfo& info
#endif
		) KOTEK_CPP_KEYWORD_NOEXCEPT;
	void Destroy_Buffer(
		const ktkBufferModule& instance) KOTEK_CPP_KEYWORD_NOEXCEPT;

private:
	gl::eShaderType DetectType(
		const ktk::cstring& path_to_file) KOTEK_CPP_KEYWORD_NOEXCEPT;

private:
	bool m_is_reallocation_feature_supported;
	ktk::size_t m_total_memory;
	ktk::size_t m_current_memory;
	Core::ktkMainManager* m_p_main_manager;
	Core::ktkIFileSystem* m_p_filesystem;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
