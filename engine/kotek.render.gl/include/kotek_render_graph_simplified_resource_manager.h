#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
class ktkResourceManager;
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL
class ktkRenderDevice;
class ktkRenderResourceManager;
KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

/// \~english @brief This constant for defining backbuffer name
KOTEK_CPP_KEYWORD_CONSTEXPR const char* kRenderGraphBackBufferName =
	"KOTEK_BACKBUFFER_GL_NAME";

class ktkRenderGraphSimplifiedResourceManager
	: public Core::ktkIRenderGraphResourceManager
{
public:
	ktkRenderGraphSimplifiedResourceManager(
		Core::ktkMainManager* p_main_manager);
	~ktkRenderGraphSimplifiedResourceManager(void);

	void Initialize(gl::eRenderGraphBuilderType type_of_framebuffer,
		gl::eRenderGraphBuilderPipelineRenderingType type_videocard_pipeline)
		override;
	void Shutdown(void);

	void Create_Shaders(const gl::ktkRenderGraphSimplifiedStorageInput&
			storage_of_render_pass_input);

	void Create_Buffer(
		const gl::ktkRenderGraphResourceInfo<gl::ktkRenderGraphBufferInfo>&
			info_create);

	/// \~english @brief It returns the whole storage of all render
	/// passes or those names that defines as a key in unordered_map
	/// m_render_passes_and_its_programs. It uses for building
	/// Kotek::Render::gl::ktkRenderGraphSimplifiedNode instance.
	/// @param void, as input it doesn't take anything
	/// @return const ktk::unordered_map<ktk::ustring, GLuint>* const
	/// it means that pointer and the map can't be changed at all.
	/// It uses only for reading.
	const ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring, GLuint>>*
	Get_Storage_Programs(void) const KOTEK_CPP_KEYWORD_NOEXCEPT;

	/// \~english @brief It returns the storage of buffers for required
	/// render pass by its name. The return data uses for building
	/// gl::ktkRenderGraphSimplifiedNode instance.
	/// @param render_pass_name string that represents valid and registered
	/// render pass name in simplified render graph
	/// @return ktk::unordered_map that key is buffer name ktk::cstring and
	/// value is information about buffer gl::ktkBufferModule.
	const ktk::unordered_map<ktk::cstring, ktkBufferModule>*
	Get_Storage_Buffers_By_RenderPassName(
		const ktk::ustring& render_pass_name) const KOTEK_CPP_KEYWORD_NOEXCEPT;

	const ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::cstring, ktkBufferModule>>*
	Get_Storage_Buffers(void) const KOTEK_CPP_KEYWORD_NOEXCEPT;

private:
	void Create_Shaders(const ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring,
			ktk::unordered_map<gl::eShaderType,
				gl::ktkRenderGraphShaderTextInfo>>>&
			shaders_for_current_render_pass);

	ktkShaderModule Create_Shader(gl::eShaderType shader_type,
		const gl::ktkRenderGraphShaderTextInfo& info_creation);

	void Destroy_Shaders(void);
	void Destroy_Buffers(void);

	void Create_Programs(void);

private:
	ktkRenderDevice* m_p_render_device;
	ktkRenderResourceManager* m_p_render_resource_manager;
	Core::ktkIResourceManager* m_p_manager_resource;
	Core::ktkMainManager* m_p_main_manager;

	// shaders
	// <render_pass_name, <shader_name, <shader_type, shader_module>>
	ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::ustring,
			ktk::unordered_map<gl::eShaderType, ktkShaderModule>>>
		m_render_passes_and_its_shaders;

	// <render_pass_name, <shader_name, program_id>>
	ktk::unordered_map<ktk::ustring, ktk::unordered_map<ktk::ustring, GLuint>>
		m_render_passes_and_its_programs;
	// shaders

	// buffers
	ktk::unordered_map<ktk::ustring,
		ktk::unordered_map<ktk::cstring, ktkBufferModule>>
		m_render_passes_and_their_buffers;
	// buffers

	// textures

	// textures
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK