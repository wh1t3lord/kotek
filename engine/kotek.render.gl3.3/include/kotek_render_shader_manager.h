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
			enum class shader_type_t : ktk::enum_base_t
			{
				kShaderType_Vertex,
				// @ fragment
				kShaderType_Pixel,
				kShaderType_Geometry,
				kShaderType_Compute,
				kShaderType_Mesh,
				kShaderType_Task,
				kShaderType_TessellationControl,
				kShaderType_TessellationEvaluation,
				kShaderType_RTX_Generation,
				kShaderType_RTX_Intersection,
				kShaderType_RTX_AnyHit,
				kShaderType_RTX_ClosesHit,
				kShaderType_RTX_Miss,
				kShaderType_RTX_Callable,

				kShaderType_Unknown = -1
			};

			enum class shader_loading_data_type_t : ktk::enum_base_t
			{
				kShaderLoadingDataType_FilePathString,
				kShaderLoadingDataType_SourceCodeTextString,
				kShaderLoadingDataType_ByteArrayFile,
				kShaderLoadingDataType_ByteArrayCompiledSPIRV,
				kShaderLoadingDataType_NotInitialized
			};

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

			class shader_module_t
			{
			public:
				shader_module_t(void);
				~shader_module_t(void);

				void SetShader(shader_type_t type, GLuint handle_id) noexcept;

				GLuint GetShader(shader_type_t type) const noexcept;

				const ktk::unordered_map<shader_type_t, GLuint>& GetShaders(
					void) const noexcept;

				void SetProgram(GLuint handle_id) noexcept;
				GLuint GetProgram(void) const noexcept;

			private:
				ktk::unordered_map<shader_type_t, GLuint> m_shader_handles;
				GLuint m_program;
			};

			class ktkRenderShaderManager
			{
			public:
				ktkRenderShaderManager(Core::ktkMainManager* p_main_manager);
				~ktkRenderShaderManager(void);

				void Initialize(void);
				void Shutdown(void);

				shader_module_t LoadShader(
					const ktk::filesystem::path& path, shader_type_t type) noexcept;
				shader_module_t LoadShader(const ktk::filesystem::path& path) noexcept;
				shader_module_t LoadShaderAsString(
					const ktk::string& code_as_string,
					shader_type_t type) noexcept;

				void DestroyShader(const shader_module_t& instance) noexcept;

			private:
				Core::ktkMainManager* m_p_main_manager;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek
