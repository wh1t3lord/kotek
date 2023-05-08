#include "../include/kotek_render_graph_simplified_resource_manager.h"
#include "../include/kotek_render_device.h"
#include "../include/kotek_render_resource_manager.h"
#include "../include/kotek_render_shader_manager.h"

#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderGraphSimplifiedResourceManager::
		ktkRenderGraphSimplifiedResourceManager(
			Core::ktkMainManager* p_main_manager) :
		m_p_render_device{
			static_cast<ktkRenderDevice*>(p_main_manager->getRenderDevice())},
		m_p_manager_resource{}, m_p_main_manager{p_main_manager}
	{
		KOTEK_ASSERT(p_main_manager->GetRenderResourceManager(),
			"you must initialize resource manager before using this "
			"class (ctor). Something is wrong if you didn't make "
			"overriding the default implementation class of "
			"ktkIRenderShaderManager");

		this->m_p_render_resource_manager =
			dynamic_cast<ktkRenderResourceManager*>(
				p_main_manager->GetRenderResourceManager());

		KOTEK_ASSERT(this->m_p_render_resource_manager,
			"you must initialize render resource manager, something is "
			"wrong!");

		KOTEK_ASSERT(this->m_p_render_resource_manager->Get_ManagerShader(),
			"you must initialize shader manager!");

		KOTEK_ASSERT(this->m_p_render_resource_manager->Get_ManagerTexture(),
			"you must initialize texture manager");
	}

	ktkRenderGraphSimplifiedResourceManager::
		~ktkRenderGraphSimplifiedResourceManager(void)
	{
	}

	void ktkRenderGraphSimplifiedResourceManager::Initialize(
		gl::eRenderGraphBuilderType type_of_framebuffer,
		gl::eRenderGraphBuilderPipelineRenderingType type_videocard_pipeline)
	{
		KOTEK_ASSERT(
			this->m_p_render_device, "you must initialize ktkRenderDevice");
		KOTEK_ASSERT(this->m_p_main_manager->GetResourceManager(),
			"you must initialize ktkResourceManager");

		this->m_p_manager_resource =
			this->m_p_main_manager->GetResourceManager();

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
		this->Destroy_Buffers();
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

		this->Create_Shaders(storage_of_render_pass_input.Get_Shaders());
		this->Create_Programs();
	}

	void ktkRenderGraphSimplifiedResourceManager::Create_Buffer(
		const gl::ktkRenderGraphResourceInfo<gl::ktkRenderGraphBufferInfo>&
			info_create)
	{
		KOTEK_ASSERT(this->m_p_manager_resource, "must be initilized");
		KOTEK_ASSERT(
			this->m_p_render_resource_manager, "must be valid and initialized");

		KOTEK_ASSERT(info_create.Get_RenderPassName().empty() == false,
			"it must have a valid render pass name");
		KOTEK_ASSERT(info_create.Get_ResourceName().empty() == false,
			"it must have a valid name");

		const auto& info_buffer = info_create.Get_Info();

		KOTEK_ASSERT(info_buffer.Get_Memory() != 0,
			"something is wrong you forgot to initialize memory or passed 0 to "
			"it");
		KOTEK_ASSERT(info_buffer.Get_AlignOfMemory() != 0,
			"you have to initialize align memory value! It equals to 0, you "
			"forgot to do that or you passed 0");
		KOTEK_ASSERT(info_buffer.Get_UniformBlockName().empty() == false,
			"you can't pass an empty string of uniform block name, because you "
			"create buffer for shader and that buffer describes data of "
			"shader, so think about it...");

		ktk::size_t memory_for_allocation_in_bytes =
			ktk::align_down<ktk::size_t>(
				info_buffer.Get_Memory(), info_buffer.Get_AlignOfMemory());

		auto& map_buffer_name_and_buffer_module =
			this->m_render_passes_and_their_buffers[info_create
														.Get_RenderPassName()];

		KOTEK_ASSERT(map_buffer_name_and_buffer_module.find(
						 info_buffer.Get_BufferName()) ==
				map_buffer_name_and_buffer_module.end(),
			"something is wrong and you have collision in names!");

		map_buffer_name_and_buffer_module[info_buffer.Get_BufferName()] =
			this->m_p_render_resource_manager->Get_ManagerShader()
				->Create_Buffer(memory_for_allocation_in_bytes,
					info_buffer.Get_BufferObject(), info_buffer.Get_Usage());

#ifdef KOTEK_DEBUG
		KOTEK_MESSAGE("create buffer [{}] with size {} Kb ({} Mb) for render "
					  "pass [{}] in shader [{}]",
			info_buffer.Get_BufferName(),
			memory_for_allocation_in_bytes /
				(ktk::kMemoryConvertValueDenominator_Kilobytes),
			memory_for_allocation_in_bytes /
				(ktk::kMemoryConvertValueDenominator_Megabytes),
			reinterpret_cast<const char*>(
				info_create.Get_RenderPassName().c_str()),
			reinterpret_cast<const char*>(
				info_buffer.Get_ShaderName().c_str()));
#endif
	}

	const ktk::unordered_map<ktk::string, GLuint>*
	ktkRenderGraphSimplifiedResourceManager::Get_Storage_Programs(
		void) const noexcept
	{
		return &this->m_render_passes_and_its_programs;
	}

	const ktk::unordered_map<ktk::cstring, ktkBufferModule>*
	ktkRenderGraphSimplifiedResourceManager::Get_Storage_Buffers(
		const ktk::string& render_pass_name) const noexcept
	{
		KOTEK_ASSERT(render_pass_name.empty() == false,
			"you can't pass an empty render pass name, because we can't find "
			"information about that pass");

		const ktk::unordered_map<ktk::cstring, ktkBufferModule>* p_result{};

		if (render_pass_name.empty())
			return p_result;

		if (this->m_render_passes_and_their_buffers.empty())
			return p_result;

		if (this->m_render_passes_and_their_buffers.find(render_pass_name) ==
			this->m_render_passes_and_their_buffers.end())
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE_WARNING(
				"render_pass_name [{}] doesn't exist for buffers",
				render_pass_name);
#endif
			return p_result;
		}

		p_result =
			&this->m_render_passes_and_their_buffers.at(render_pass_name);

		return p_result;
	}

	void ktkRenderGraphSimplifiedResourceManager::Create_Shaders(
		const ktk::unordered_map<ktk::string,
			ktk::unordered_map<gl::eShaderType,
				gl::ktkRenderGraphShaderTextInfo>>&
			shaders_for_current_render_pass)
	{
		for (const auto& [pipeline_name, map_shader_type_info_creation] :
			shaders_for_current_render_pass)
		{
			KOTEK_ASSERT(
				this->m_render_passes_and_its_shaders.find(pipeline_name) ==
					this->m_render_passes_and_its_shaders.end(),
				"found duplicate the pipeline name: [{}]",
				reinterpret_cast<const char*>(pipeline_name.c_str()));

			for (const auto& [shader_type, info_shader_creation] :
				map_shader_type_info_creation)
			{
				this->m_render_passes_and_its_shaders[pipeline_name]
													 [shader_type] =
					this->Create_Shader(shader_type, info_shader_creation);
			}
		}
	}

	ktkShaderModule ktkRenderGraphSimplifiedResourceManager::Create_Shader(
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
			KOTEK_ASSERT(false, "doesn't support for this opengl version");
			break;
		}
		case gl::eShaderLoadingDataType::kShaderLoadingDataType_ByteArrayFile:
		{
			// TODO: implement
			KOTEK_ASSERT(false, "implement");
			break;
		}
		case gl::eShaderLoadingDataType::kShaderLoadingDataType_FilePathString:
		{
			result = p_manager->LoadShader(
				std::get<Kotek::ktk::string>(info_creation.Get_Data()));
			break;
		}
		case gl::eShaderLoadingDataType::kShaderLoadingDataType_NotInitialized:
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

		KOTEK_ASSERT(
			p_manager, "you can't have an empty shader manager instance here");

		for (const auto& [render_pass_name, map_shader_type_shader_module] :
			this->m_render_passes_and_its_shaders)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("[GL] deleting shader handles for render pass: [{}]",
				reinterpret_cast<const char*>(render_pass_name.c_str()));
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

		for (const auto& [render_pass_name, program_handle_id] :
			this->m_render_passes_and_its_programs)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("[GL] deleting program handles for render pass: [{}]",
				reinterpret_cast<const char*>(render_pass_name.c_str()));
#endif

			glDeleteProgram(program_handle_id);
		}
	}

	void ktkRenderGraphSimplifiedResourceManager::Destroy_Buffers(void)
	{
		KOTEK_ASSERT(
			this->m_p_manager_resource, "you must initialize resource manager");
		KOTEK_ASSERT(this->m_p_render_resource_manager,
			"you must intiialzie render resource manager");

		for (const auto& [render_pass_name, map_buffer_name_and_buffer_module] :
			this->m_render_passes_and_their_buffers)
		{
			for (const auto& [buffer_name, buffer_module] :
				map_buffer_name_and_buffer_module)
			{
				this->m_p_render_resource_manager->Get_ManagerShader()
					->Destroy_Buffer(buffer_module);

#ifdef KOTEK_DEBUG
				KOTEK_MESSAGE("destroy buffer [{}] in render pass [{}]",
					buffer_name, render_pass_name);
#endif
			}
		}
	}

	void ktkRenderGraphSimplifiedResourceManager::Create_Programs(void)
	{
		for (const auto& [render_pass_name, map_shader_type_shader_module] :
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
						reinterpret_cast<const char*>(render_pass_name.c_str()),
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

					KOTEK_ASSERT(false, "failed to link: {}", buffer);
				}
#endif

				this->m_render_passes_and_its_programs[render_pass_name] =
					program;
			}
		}
	}
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
