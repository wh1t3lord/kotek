#include "../include/kotek_render_graph_simplified_resource_manager.h"
#include "../include/kotek_render_device.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_shader_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderGraphSimplifiedResourceManager::
				ktkRenderGraphSimplifiedResourceManager(
					Core::ktkMainManager* p_main_manager) :
				m_p_render_device{static_cast<ktkRenderDevice*>(
					p_main_manager->getRenderDevice())},
				m_p_manager_resource{static_cast<Core::ktkResourceManager*>(
					p_main_manager->GetResourceManager())}
			{
				KOTEK_ASSERT(this->m_p_manager_resource,
					"you must initialize resource manager before using this "
					"class (ctor). Something is wrong if you didn't make "
					"overriding the default implementation class of "
					"ktkIRenderShaderManager");

				this->m_p_render_resource_manager =
					dynamic_cast<ktkRenderResourceManager*>(
						this->m_p_manager_resource
							->Get_RenderResourceManager());

				KOTEK_ASSERT(this->m_p_render_resource_manager,
					"you must initialize render resource manager, something is "
					"wrong!");

				KOTEK_ASSERT(
					this->m_p_render_resource_manager->Get_ManagerShader(),
					"you must initialize shader manager!");

				KOTEK_ASSERT(
					this->m_p_render_resource_manager->Get_ManagerTexture(),
					"you must initialize texture manager");
			}

			ktkRenderGraphSimplifiedResourceManager::
				~ktkRenderGraphSimplifiedResourceManager(void)
			{
			}

			void ktkRenderGraphSimplifiedResourceManager::Initialize(
				gl::eRenderGraphBuilderType type_of_framebuffer,
				gl::eRenderGraphBuilderPipelineRenderingType
					type_videocard_pipeline)
			{
				KOTEK_ASSERT(this->m_p_render_device,
					"you must initialize ktkRenderDevice");
				KOTEK_ASSERT(this->m_p_manager_resource,
					"you must initialize ktkResourceManager");

				if (type_of_framebuffer ==
					gl::eRenderGraphBuilderType::kRenderBuilderFor_Forward_Only)
				{
				}
				else
				{
					KOTEK_ASSERT(false, "not implemented!");
				}
			}

			void ktkRenderGraphSimplifiedResourceManager::Shutdown(void)
			{
				this->Destroy_Shaders();
			}

			void ktkRenderGraphSimplifiedResourceManager::Create_Shaders(
				const gl::ktkRenderGraphSimplifiedStorageInput&
					storage_of_render_pass_input)
			{
				if (storage_of_render_pass_input.Get_Shaders().empty())
				{
					KOTEK_MESSAGE_WARNING(
						"you can't create a render pass without shaders!");
					return;
				}

				this->Create_Shaders(
					storage_of_render_pass_input.Get_Shaders());
				this->Create_Programs();
			}

			void ktkRenderGraphSimplifiedResourceManager::Create_Shaders(
				const ktk::unordered_map<ktk::string,
					ktk::unordered_map<gl::eShaderType,
						gl::ktkRenderGraphShaderTextInfo>>&
					shaders_for_current_render_pass)
			{
				for (const auto& [pipeline_name,
						 map_shader_type_info_creation] :
					shaders_for_current_render_pass)
				{
					KOTEK_ASSERT(this->m_render_passes_and_its_shaders.find(
									 pipeline_name) ==
							this->m_render_passes_and_its_shaders.end(),
						"found duplicate the pipeline name: [{}]",
						pipeline_name);

					for (const auto& [shader_type, info_shader_creation] :
						map_shader_type_info_creation)
					{
						this->m_render_passes_and_its_shaders[pipeline_name]
															 [shader_type] =
							this->Create_Shader(
								shader_type, info_shader_creation);
					}
				}
			}

			ktkShaderModule
			ktkRenderGraphSimplifiedResourceManager::Create_Shader(
				gl::eShaderType shader_type,
				const gl::ktkRenderGraphShaderTextInfo& info_creation)
			{
				ktkShaderModule result;

				ktkRenderShaderManager* p_manager =
					this->m_p_render_resource_manager->Get_ManagerShader();

				switch (info_creation.Get_Type())
				{
				case gl::eShaderLoadingDataType::
					kShaderLoadingDataType_ByteArrayCompiledSPIRV:
				{
					KOTEK_ASSERT(
						false, "doesn't support for this opengl version");
					break;
				}
				case gl::eShaderLoadingDataType::
					kShaderLoadingDataType_ByteArrayFile:
				{
					// TODO: implement
					KOTEK_ASSERT(false, "implement");
					break;
				}
				case gl::eShaderLoadingDataType::
					kShaderLoadingDataType_FilePathString:
				{
					result = p_manager->LoadShader(
						std::get<Kotek::ktk::string>(info_creation.Get_Data())
							.get_as_is());
					break;
				}
				case gl::eShaderLoadingDataType::
					kShaderLoadingDataType_NotInitialized:
				{
					KOTEK_ASSERT(false, "can't be check your data!");
					break;
				}
				case gl::eShaderLoadingDataType::
					kShaderLoadingDataType_SourceCode_TextString:
				{
					result = p_manager->LoadShaderAsString(
						std::get<Kotek::ktk::string>(info_creation.Get_Data()),
						shader_type);
					break;
				}
				default:
				{
					KOTEK_ASSERT(false, "unknown state of gl::eShaderType");
					break;
				}
				}

				return result;
			}

			void ktkRenderGraphSimplifiedResourceManager::Destroy_Shaders(void)
			{
				ktkRenderShaderManager* p_manager =
					this->m_p_render_resource_manager->Get_ManagerShader();

				KOTEK_ASSERT(p_manager,
					"you can't have an empty shader manager instance here");

				for (const auto& [render_pass_name,
						 map_shader_type_shader_module] :
					this->m_render_passes_and_its_shaders)
				{
#ifdef KOTEK_DEBUG
					KOTEK_MESSAGE(
						"[GL] deleting shader handles for render pass: [{}]",
						render_pass_name);
#endif

					for (const auto& [shader_type, shader_module] :
						map_shader_type_shader_module)
					{
#ifdef KOTEK_DEBUG
						KOTEK_MESSAGE("[GL] deleting shader: [{}]",
							gl::helper::Translate_ShaderType(shader_type));
#endif

						p_manager->DestroyShader(shader_module);
					}
				}
			}

			void ktkRenderGraphSimplifiedResourceManager::Create_Programs(void)
			{
				for (const auto& [render_pass_name,
						 map_shader_type_shader_module] :
					this->m_render_passes_and_its_shaders)
				{
					if (map_shader_type_shader_module.empty() == false)
					{
						auto program = glCreateProgram();

						for (const auto& [shader_type, shader_module] :
							map_shader_type_shader_module)
						{
#ifdef KOTEK_DEBUG
							KOTEK_MESSAGE("attached shader type to "
										  "render_pass_name[{}]: [{}]",
								render_pass_name,
								gl::helper::Translate_ShaderType(shader_type));
#endif

							glAttachShader(program, shader_module.Get_Shader());
						}

						glLinkProgram(program);

#ifdef KOTEK_DEBUG
						int status{};
						char buffer[512];
						glGetProgramiv(program, GL_LINK_STATUS, &status);

						if (status == GL_FALSE)
						{
							glGetProgramInfoLog(
								program, sizeof(buffer), nullptr, buffer);

							KOTEK_ASSERT(false, "failed to link: {}",
								ktk::string(buffer));
						}
#endif
					}
				}
			}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek