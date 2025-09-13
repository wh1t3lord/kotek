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
KOTEK_BEGIN_NAMESPACE_RENDER_BGFX

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

	void Initialize(kun_ktk size_t value_in_bytes,
		bool is_support_reallocation_feature = false);
	void Shutdown(void);

private:
	bool m_is_reallocation_feature_supported;
	kun_ktk size_t m_total_memory;
	kun_ktk size_t m_current_memory;
	kun_core ktkMainManager* m_p_main_manager;
	kun_core ktkIFileSystem* m_p_filesystem;

#ifdef KOTEK_DEBUG
	// todo: provide switching between static (stack/embedded)
	// implementation and dynamic
	kun_ktk unordered_map<GLuint, bool> m_user_called_destroy_shaders;
	kun_ktk unordered_map<GLuint, bool> m_user_called_destroy_buffers;
	kun_ktk unordered_map<GLuint, bool> m_user_called_destroy_programs;
#endif
};

KOTEK_END_NAMESPACE_RENDER_BGFX
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
