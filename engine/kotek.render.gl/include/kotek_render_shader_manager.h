#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	constexpr const char* _kShaderPrefix_Vertex = "vert";
	constexpr const char* _kShaderPrefix_Fragment = "frag";
	constexpr const char* _kShaderPrefix_Compute = "comp";
	constexpr const char* _kShaderPrefix_Task = "task";
	constexpr const char* _kShaderPrefix_Mesh = "mesh";
	constexpr const char* _kShaderPrefix_Geometry = "geom";
	constexpr const char* _kShaderPrefix_TessellationEvaluation = "tese";
	constexpr const char* _kShaderPrefix_TessellationControl = "tesc";

	class ktkRenderShaderManager
	{
	public:
		ktkRenderShaderManager(Core::ktkMainManager* p_main_manager);
		~ktkRenderShaderManager(void);

		void Initialize(void);
		void Shutdown(void);

		ktkShaderModule LoadShader(
			const ktk::filesystem::path& path, gl::eShaderType type) noexcept;
		ktkShaderModule LoadShader(const ktk::filesystem::path& path) noexcept;
		ktkShaderModule LoadShaderAsString(
			const ktk::string& code_as_string, gl::eShaderType type) noexcept;

		void DestroyShader(const ktkShaderModule& instance) noexcept;

	private:
		gl::eShaderType DetectType(const ktk::cstring& path_to_file) noexcept;

	private:
		Core::ktkMainManager* m_p_main_manager;
		Core::ktkIFileSystem* m_p_filesystem;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
