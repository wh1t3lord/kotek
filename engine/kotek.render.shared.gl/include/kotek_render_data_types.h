#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			enum class eShaderType;
		}
	} // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkShaderModule
			{
			public:
				ktkShaderModule(void);
				~ktkShaderModule(void);

				void Set_Shader(
					gl::eShaderType type, GLuint handle_id) noexcept;

				GLuint Get_Shader(void) const noexcept;

				gl::eShaderType Get_ShaderType(void) const noexcept;

			private:
				/// @brief this is the handle (result) of glCreateShader
				/// operation
				GLuint m_shader_handle;

				/// @brief enum for determining what is the type of shader
				gl::eShaderType m_shader_type;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek
