#pragma once

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}

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
			constexpr const char* kBackBufferName = "KOTEK_BACKBUFFER_GL_NAME";

			class ktkRenderGraphSimplifiedResourceManager
			{
			public:
				ktkRenderGraphSimplifiedResourceManager(
					Core::ktkMainManager& main_manager);
				~ktkRenderGraphSimplifiedResourceManager(void);

				void Initialize(gl::eRenderGraphBuilderType type_of_framebuffer,
					gl::eRenderGraphBuilderPipelineRenderingType
						type_videocard_pipeline);
				void Shutdown(void);

			private:
				ktkRenderDevice* m_p_render_device;
				ktkRenderResourceManager* m_p_render_resource_manager;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek