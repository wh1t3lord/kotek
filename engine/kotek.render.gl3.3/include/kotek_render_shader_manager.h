#pragma once

#include <shaderc/shaderc.hpp>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			constexpr const ktk::tchar* _kShaderPrefix_Vertex =
				KOTEK_TEXT("vert");
			constexpr const ktk::tchar* _kShaderPrefix_Fragment =
				KOTEK_TEXT("frag");
			constexpr const ktk::tchar* _kShaderPrefix_Compute =
				KOTEK_TEXT("comp");
			constexpr const ktk::tchar* _kShaderPrefix_Task =
				KOTEK_TEXT("task");
			constexpr const ktk::tchar* _kShaderPrefix_Mesh =
				KOTEK_TEXT("mesh");
			constexpr const ktk::tchar* _kShaderPrefix_Geometry =
				KOTEK_TEXT("geom");
			constexpr const ktk::tchar* _kShaderPrefix_TessellationEvaluation =
				KOTEK_TEXT("tese");
			constexpr const ktk::tchar* _kShaderPrefix_TessellationControl =
				KOTEK_TEXT("tesc");

			class ktkRenderShaderManager
			{
			public:
				ktkRenderShaderManager(Core::ktkMainManager* p_main_manager);
				~ktkRenderShaderManager(void);

				void Initialize(void);
				void Shutdown(void);

				ktkShaderModule LoadShader(const ktk::filesystem::path& path,
					gl::eShaderType type) noexcept;
				ktkShaderModule LoadShader(
					const ktk::filesystem::path& path) noexcept;
				ktkShaderModule LoadShaderAsString(
					const ktk::string& code_as_string,
					gl::eShaderType type) noexcept;

				void DestroyShader(const ktkShaderModule& instance) noexcept;

			private:
				Core::ktkMainManager* m_p_main_manager;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek
