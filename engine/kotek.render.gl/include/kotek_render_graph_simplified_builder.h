#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkIRenderResourceManager;
class ktkIRenderGraphResourceManager;
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphSimplified;
	class ktkRenderGraphSimplifiedNode;
	class ktkRenderGraphSimplifiedRenderPass;
	class ktkRenderGraphSimplifiedResourceManager;
	class ktkRenderResourceManager;
	enum class eRenderGraphBuilderType;
	enum class eRenderGraphBuilderPipelineRenderingType;
} // namespace gl

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphSimplifiedBuilder
	{
	public:
		ktkRenderGraphSimplifiedBuilder(Core::ktkMainManager* p_main_manager);
		ktkRenderGraphSimplifiedBuilder(void) = delete;
		~ktkRenderGraphSimplifiedBuilder(void);

		ktkRenderGraphSimplifiedBuilder(
			const ktkRenderGraphSimplifiedBuilder&) = delete;
		ktkRenderGraphSimplifiedBuilder& operator=(
			const ktkRenderGraphSimplifiedBuilder&) = delete;

		ktkRenderGraphSimplifiedBuilder(
			ktkRenderGraphSimplifiedBuilder&&) = delete;
		ktkRenderGraphSimplifiedBuilder& operator=(
			ktkRenderGraphSimplifiedBuilder&&) = delete;

		void Initialize(
			Core::ktkIRenderGraphResourceManager* p_resource_manager,
			const ktk::cstring& backbuffer_name,
			const gl::eRenderGraphBuilderType& render_graph_type_id,
			const gl::eRenderGraphBuilderPipelineRenderingType&
				rendering_pipeline_type);

		ktkRenderGraphSimplified Compile(void);

		bool Register_RenderPass(const ktk::cstring& render_pass_name,
			ktkRenderGraphSimplifiedRenderPass* p_pass) noexcept;

		const ktk::cstring& Get_BackBufferName(void) const noexcept;

		gl::eRenderGraphBuilderType Get_RenderGraphBuilderType(
			void) const noexcept;

		gl::eRenderGraphBuilderPipelineRenderingType
		Get_RenderGraphPipelineRenderingType(void) const noexcept;

	private:
		ktk::unordered_map<ktk::ustring,
			gl::ktkRenderGraphSimplifiedStorageInput>
		Compile_Inputs(void) noexcept;
		ktk::unordered_map<ktk::ustring,
			gl::ktkRenderGraphSimplifiedStorageOutput>
		Compile_Outputs(void) noexcept;

		// just collects all necessary stuff about whole creation
		// but after we create it in Create_Resources method
		void Compile_BuffersAndImagesForCreation(
			const ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphSimplifiedStorageInput>& storage_inputs,
			const ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphSimplifiedStorageOutput>& storage_outputs,
			ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphResourceInfo<gl::ktkRenderGraphTextureInfo>>&
				images_to_create,
			ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphResourceInfo<gl::ktkRenderGraphBufferInfo>>&
				buffers_to_create) noexcept;

		ktk::vector<ktkRenderGraphSimplifiedNode> Analyze(
			const ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphSimplifiedStorageInput>& storage_inputs,
			const ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphSimplifiedStorageOutput>& storage_outputs);

	private:
		void Create_Resources(
			const ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphSimplifiedStorageInput>& all_inputs,
			const ktk::unordered_map<ktk::ustring,
				gl::ktkRenderGraphResourceInfo<gl::ktkRenderGraphBufferInfo>>&
				buffers_to_create) noexcept;
		void Create_BackBuffer(void) noexcept;
		void Create_Shaders(const ktk::unordered_map<ktk::ustring,
			gl::ktkRenderGraphSimplifiedStorageInput>& all_inputs) noexcept;
		void Create_Buffers(const const ktk::unordered_map<ktk::ustring,
			gl::ktkRenderGraphResourceInfo<gl::ktkRenderGraphBufferInfo>>&
				buffers_to_create) noexcept;

	private:
		gl::eRenderGraphBuilderType m_render_graph_type;
		gl::eRenderGraphBuilderPipelineRenderingType m_rendering_pipeline_type;
		Core::ktkMainManager* m_p_main_manager;
		ktkRenderResourceManager* m_p_render_resource_manager;
		ktkRenderGraphSimplifiedResourceManager*
			m_p_render_graph_simplified_resource_manager;
		ktk::vector<ktkRenderGraphSimplifiedRenderPass*> m_passes;
		ktk::vector<ktkRenderGraphSimplifiedRenderPass*>
			m_failed_passes_for_adding;
		ktk::cstring m_backbuffer_name;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
