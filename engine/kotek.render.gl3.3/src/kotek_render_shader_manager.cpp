#include "../include/kotek_render_shader_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderShaderManager::ktkRenderShaderManager(
				Core::ktkMainManager* p_main_manager) :
				m_p_main_manager(p_main_manager)
			{
				KOTEK_ASSERT(p_main_manager, "must be valid");
			}

			ktkRenderShaderManager::~ktkRenderShaderManager(void) {}

			void ktkRenderShaderManager::Initialize(void) {}

			void ktkRenderShaderManager::Shutdown(void) {}

			ktkShaderModule ktkRenderShaderManager::LoadShader(
				const ktk::filesystem::path& path,
				gl::eShaderType type) noexcept
			{
				return ktkShaderModule();
			}

			ktkShaderModule ktkRenderShaderManager::LoadShader(
				const ktk::filesystem::path& path) noexcept
			{
				return ktkShaderModule();
			}

			ktkShaderModule ktkRenderShaderManager::LoadShaderAsString(
				const ktk::string& code_as_string,
				gl::eShaderType type) noexcept
			{
				KOTEK_ASSERT(code_as_string.empty() == false,
					"you can't pass an empty string here");

				KOTEK_ASSERT(type != gl::eShaderType::kShaderType_Unknown,
					"you can't pass an unknown shader, you have to determine "
					"what is the shader's type (Vertex, Fragment and etc)");

				ktkShaderModule result;

				ktk::string_legacy converted = code_as_string.get_as_legacy();
				const char* p_str = converted.c_str();

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
					glGetShaderInfoLog(
						shader_handle, sizeof(buffer), nullptr, buffer);

					KOTEK_ASSERT(false, "{}", ktk::string(buffer));
				}
#endif

				result.Set_Shader(type, shader_handle);

				return result;
			}

			void ktkRenderShaderManager::DestroyShader(
				const ktkShaderModule& instance) noexcept
			{
				if (instance.Get_ShaderType() !=
					gl::eShaderType::kShaderType_Unknown)
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
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek