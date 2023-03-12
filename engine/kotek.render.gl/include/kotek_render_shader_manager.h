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
	// TODO: use shader-lang
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
		Core::ktkMainManager* m_p_main_manager;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
