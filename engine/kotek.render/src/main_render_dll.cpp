#include "../include/kotek_render.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

#include <kotek.render.model/include/kotek_render_model.h>

#ifdef KOTEK_USE_RENDER_OPENGL
	#include <kotek.render.gl/include/kotek_render_gl.h>
#endif

// TODO: preprocessor for enabling gles and for other renderers add pls
#include <kotek.render.angle.gles23/include/kotek_render_angle_gles23.h>

#ifdef KOTEK_USE_RENDER_VULKAN
	#include <kotek.render.vk/include/kotek_render_vk.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render(Core::ktkMainManager* main_manager)
{
	// TODO: сделать выбор рендера

	InitializeModule_Render_Shared(main_manager);

	auto* p_engine_config = main_manager->Get_EngineConfig();

	// TODO: provide an overriding for every instance what implemented here
	KOTEK_ASSERT(p_engine_config,
		"you must initialize ktkEngineConfig instance or override it by your "
		"own implementation");

	KOTEK_ASSERT(p_engine_config->IsUserSpecifiedValidRenderer(),
		"User didn't specify renderer correctly!");

	bool status{};

	if (p_engine_config->IsUserSpecifiedRendererDirectXInCommandLine())
	{
		auto version_dx = p_engine_config->GetRendererVersionFromCommandLine();
		KOTEK_MESSAGE("you pass command for initializing {}",
			Kotek::Core::helper::Translate_EngineSupportedRenderer(version_dx));

		switch (version_dx)
		{
		default:
		{
			KOTEK_MESSAGE("Uknown version of DirectX you pass trying to "
						  "initialize OpenGL");
		}
		}
		// TODO: add directx
	}
	else if (p_engine_config->IsUserSpecifiedRendererOpenGLInCommandLine())
	{
		KOTEK_MESSAGE(
			"you pass command line to application for initializing {}",
			Kotek::Core::helper::Translate_EngineSupportedRenderer(
				p_engine_config->GetRendererVersionEnum()));
		status = InitializeModule_Render_GL(
			main_manager, p_engine_config->GetRendererVersionEnum());
	}
	else if (p_engine_config->IsUserSpecifiedRendererVulkanInCommandLine())
	{
#ifdef KOTEK_USE_RENDER_VULKAN
		KOTEK_MESSAGE(
			"you pass command line to application for initializing {}",
			Kotek::Core::helper::Translate_EngineSupportedVulkanVersion(
				p_engine_config->GetVulkanVersionFromCommandLine()));
		status = InitializeModule_Render_VK(
			main_manager, p_engine_config->GetVulkanVersionFromCommandLine());
#endif
	}
	else
	{
		// TODO: finish for all renderers
		bool is_gl =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGL_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGL_SpecifiedByUser);

		bool is_vk =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_Vulkan_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_Vulkan_SpecifiedByUser);

		bool is_dx =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_SpecifiedByUser);

		bool is_gles =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGLES_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser);

		if (is_gl)
		{
			status = InitializeModule_Render_GL(
				main_manager, p_engine_config->GetRendererVersionEnum());
		}
		else if (is_vk)
		{
#ifdef KOTEK_USE_RENDER_VULKAN
			status = InitializeModule_Render_VK(
				main_manager, p_engine_config->GetVulkanVersionForLoading());
#endif
		}
		else if (is_dx)
		{
			KOTEK_ASSERT(false, "not implemented");
		}
		else if (is_gles)
		{
			status = InitializeModule_Render_ANGLE_GLES23(
				main_manager, p_engine_config->GetRendererVersionEnum());
		}
		else
		{
			KOTEK_ASSERT(false, "todo: finish other renderers like angle etc");
		}
	}

	if (!status)
	{
		const auto& enum_renderers = p_engine_config->GetFallbackRendereres();

		for (auto renderer : enum_renderers)
		{
			bool is_inited{};

			switch (renderer)
			{
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser:
			{
				KOTEK_ASSERT(false, "not implemented");
				break;
			}
			case Core::eEngineFeatureRenderer::kEngine_Feature_Renderer_Software:
			{
				break;
			}
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_Vulkan_SpecifiedByUser:
			{
#ifdef KOTEK_USE_RENDER_VULKAN
				const auto& enum_vk_versions =
					p_engine_config->GetFallbackRendererVersions();

				for (auto version : enum_vk_versions)
				{
					is_inited =
						InitializeModule_Render_VK(main_manager, version);

					if (is_inited)
						break;
				}
#endif

				break;
			}
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_OpenGL_SpecifiedByUser:
			{
				const auto& enum_gl_versions =
					p_engine_config->GetFallbackRendererVersions();

				for (auto version : enum_gl_versions)
				{
					is_inited =
						InitializeModule_Render_GL(main_manager, version);

					if (is_inited)
						break;
				}

				break;
			}
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_DirectX_SpecifiedByUser:
			{
				const auto& enum_dx_versions =
					p_engine_config->GetFallbackRendererVersions();

				for (auto version : enum_dx_versions)
				{
					KOTEK_ASSERT(false, "not implemented");
				}

				break;
			}
			default:
			{
				KOTEK_ASSERT(false, "not implemented");
			}

				if (is_inited)
					break;
			}
		}
	}

	KOTEK_ASSERT(status, "can't initialize module render {}. See log",
		p_engine_config->GetRenderName());

	KOTEK_MESSAGE(
		"render module {} is initialized", p_engine_config->GetRenderName());

	return status;
}

bool ShutdownModule_Render(Core::ktkMainManager* main_manager)
{
	auto* p_engine_config = main_manager->Get_EngineConfig();

	// TODO: provide an overriding for every instance what implemented here
	KOTEK_ASSERT(p_engine_config,
		"you must initialize ktkEngineConfig instance or override it by your "
		"own implementation");

	KOTEK_ASSERT(p_engine_config->IsUserSpecifiedValidRenderer(),
		"User didn't specify renderer correctly!");

	bool status{};

	if (p_engine_config->IsUserSpecifiedRendererDirectXInCommandLine())
	{
		// TODO: add DirectX here
	}
	else if (p_engine_config->IsUserSpecifiedRendererOpenGLInCommandLine())
	{
		status = ShutdownModule_Render_GL(main_manager);
	}
	else if (p_engine_config->IsUserSpecifiedRendererVulkanInCommandLine())
	{
#ifdef KOTEK_USE_RENDER_VULKAN
		status = ShutdownModule_Render_VK(main_manager);
#endif
	}
	else
	{
		// TODO: finish for all renderers
		bool is_gl =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGL_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGL_SpecifiedByUser);

		bool is_vk =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_Vulkan_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_Vulkan_SpecifiedByUser);

		bool is_dx =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_DirectX_SpecifiedByUser);

		bool is_gles =
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGLES_Latest) ||
			p_engine_config->IsFeatureEnabled(Core::eEngineFeatureRenderer::
					kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser);

		if (is_gl)
		{
			status = ShutdownModule_Render_GL(main_manager);
		}
		else if (is_vk)
		{
#ifdef KOTEK_USE_RENDER_VULKAN
			status = ShutdownModule_Render_VK(main_manager);
#endif
		}
		else if (is_dx)
		{
			KOTEK_ASSERT(false, "not implemented");
		}
		else if (is_gles)
		{
			status = ShutdownModule_Render_ANGLE_GLES23(main_manager);
		}
		else
		{
			KOTEK_ASSERT(false, "todo: finish other renderers like angle etc");
		}
	}

	KOTEK_ASSERT(status, "failed to shutdown render {} module",
		p_engine_config->GetRenderName());

	return status;
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
