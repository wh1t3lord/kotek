#pragma once

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

			private:
				ktkRenderDevice* m_p_render_device;
				Core::ktkResourceManager* m_p_manager_resource;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek