#pragma once

#include "kotek_render_shader_manager.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
		class ktkResourceManager;
	} // namespace Core

	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderDevice;
			class ktkRenderResourceManager;
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			constexpr const char* kRenderGraphBackBufferName =
				"KOTEK_BACKBUFFER_GL3_3_NAME";

			// TODO: рендер граф использует рендер ресурс манагер, но он не
			// имеет никакой логики по созданию ресурсов, создание ресурсов
			// лежит в рендер ресурс манагере!!!
			// TODO: исправить этот класс для Vulkan
			class ktkRenderGraphSimplifiedResourceManager
				: public Core::ktkIRenderGraphResourceManager
			{
			public:
				ktkRenderGraphSimplifiedResourceManager(
					Core::ktkMainManager* p_main_manager);
				~ktkRenderGraphSimplifiedResourceManager(void);

				void Initialize(gl::eRenderGraphBuilderType type_of_framebuffer,
					gl::eRenderGraphBuilderPipelineRenderingType
						type_videocard_pipeline) override;
				void Shutdown(void);

				void Create_Shaders(
					const gl::ktkRenderGraphSimplifiedStorageInput&
						storage_of_render_pass_input);

			private:
				void Create_Shaders(const ktk::unordered_map<ktk::string,
					ktk::unordered_map<gl::eShaderType,
						gl::ktkRenderGraphShaderTextInfo>>&
						shaders_for_current_render_pass);

				shader_module_t Create_Shader(gl::eShaderType shader_type,
					const gl::ktkRenderGraphShaderTextInfo& info_creation);

				void Destroy_Shaders(void);

			private:
				ktkRenderDevice* m_p_render_device;
				ktkRenderResourceManager* m_p_render_resource_manager;
				Core::ktkResourceManager* m_p_manager_resource;
				ktk::unordered_map<ktk::string,
					ktk::unordered_map<gl::eShaderType, shader_module_t>>
					m_render_passes_and_its_shaders;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek