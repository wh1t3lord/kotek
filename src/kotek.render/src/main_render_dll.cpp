#include "../include/kotek_render.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

#ifdef KOTEK_USE_RENDER_BGFX
	#include <kotek.render.bgfx/include/kotek_render_bgfx.h>
#endif

#ifdef KOTEK_USE_RENDER_NRI
	#include <kotek.render.nri/include/kotek_render_nri.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render(Core::ktkMainManager* main_manager)
{
	// TODO: сделать выбор рендера

	KOTEK_INVOKE_MODULE(INIT, RENDER, InitializeModule_Render_Shared, main_manager);

	auto* p_engine_config = main_manager->Get_EngineConfig();

	// TODO: provide an overriding for every instance what implemented here
	KOTEK_ASSERT(p_engine_config,
		"you must initialize ktkFrameworkConfig instance or override it by your "
		"own implementation");

	KOTEK_ASSERT(p_engine_config->IsUserSpecifiedValidRenderer(),
		"User didn't specify renderer correctly!");

	bool status{};

	if (p_engine_config->IsUserSpecifiedRendererDirectXInCommandLine())
	{
		auto version_dx = p_engine_config->GetRendererVersionFromCommandLine();
		KOTEK_MESSAGE("you pass command for initializing {}",
			Kotek::Core::helper::Translate_EngineSupportedRenderer(version_dx));

		// the DirectX slot is where the NRI backend lives (D3D12 today,
		// task K11; version sanity stays on the user — any dx version maps
		// to the one NRI-D3D12 backend in phase 1)
#ifdef KOTEK_USE_RENDER_NRI
		status = KOTEK_INVOKE_MODULE(INIT, RENDER,
			InitializeModule_Render_NRI, main_manager);
#else
		KOTEK_ASSERT(false, "the NRI backend is disabled (KOTEK_NRI)");
#endif
	}
	else if (p_engine_config->IsUserSpecifiedRendererOpenGLInCommandLine() ||
		p_engine_config->IsUserSpecifiedRendererVulkanInCommandLine())
	{
		KOTEK_ASSERT(false,
			"OpenGL/Vulkan backends were removed (2026-07-22): use bgfx "
			"(raster) or NRI (dx12/vk + ray tracing, planned)");
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

		if (is_gl || is_vk)
		{
			KOTEK_ASSERT(false,
				"OpenGL/Vulkan backends were removed (2026-07-22): bgfx is the "
				"raster backend, NRI (dx12/vk + ray tracing) is planned");
		}
		else if (is_dx)
		{
			// the DirectX slot is where the NRI backend lives (D3D12
			// today, task K11; a later NRI-Vulkan slot is added the same
			// way — phase 1 keeps the structure, not the VK build)
#ifdef KOTEK_USE_RENDER_NRI
			status = KOTEK_INVOKE_MODULE(INIT, RENDER,
				InitializeModule_Render_NRI, main_manager);
#else
			KOTEK_ASSERT(false, "the NRI backend is disabled (KOTEK_NRI)");
#endif
		}
		else if (is_gles)
		{
			bool isBGFX = p_engine_config->IsFeatureEnabled(
				kun_core eEngineFeatureRendererVendor::kBGFX);

			if (isBGFX)
			{
				status = KOTEK_INVOKE_MODULE(INIT, RENDER,
					InitializeModule_Render_BGFX, main_manager);
			}
			else
			{
				KOTEK_ASSERT(false,
					"only BGFX is supported as a vendor for OpenGL ES "
					"(ANGLE was removed 2026-07-22)");
			}
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
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_Software:
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_Vulkan_SpecifiedByUser:
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_OpenGL_SpecifiedByUser:
			case Core::eEngineFeatureRenderer::
				kEngine_Feature_Renderer_DirectX_SpecifiedByUser:
			{
				// software/vk/gl backends were removed (2026-07-22); directx
				// waits for the NRI backend
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
		"you must initialize ktkFrameworkConfig instance or override it by your "
		"own implementation");

	KOTEK_ASSERT(p_engine_config->IsUserSpecifiedValidRenderer(),
		"User didn't specify renderer correctly!");

	bool status{};

	if (p_engine_config->IsUserSpecifiedRendererDirectXInCommandLine())
	{
		// the DirectX slot is where the NRI backend lives (task K11)
#ifdef KOTEK_USE_RENDER_NRI
		status = KOTEK_INVOKE_MODULE(SHUTDOWN, RENDER,
			ShutdownModule_Render_NRI, main_manager);
#else
		KOTEK_ASSERT(false, "the NRI backend is disabled (KOTEK_NRI)");
#endif
	}
	else if (p_engine_config->IsUserSpecifiedRendererOpenGLInCommandLine() ||
		p_engine_config->IsUserSpecifiedRendererVulkanInCommandLine())
	{
		KOTEK_ASSERT(false,
			"OpenGL/Vulkan backends were removed (2026-07-22): use bgfx "
			"(raster) or NRI (dx12/vk + ray tracing, planned)");
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

		if (is_gl || is_vk)
		{
			KOTEK_ASSERT(false,
				"OpenGL/Vulkan backends were removed (2026-07-22): use bgfx "
				"(raster) or NRI (dx12/vk + ray tracing, planned)");
		}
		else if (is_dx)
		{
			// the DirectX slot is where the NRI backend lives (task K11)
#ifdef KOTEK_USE_RENDER_NRI
			status = KOTEK_INVOKE_MODULE(SHUTDOWN, RENDER,
				ShutdownModule_Render_NRI, main_manager);
#else
			KOTEK_ASSERT(false, "the NRI backend is disabled (KOTEK_NRI)");
#endif
		}
		else if (is_gles)
		{
			bool isBGFX = p_engine_config->IsFeatureEnabled(
				kun_core eEngineFeatureRendererVendor::kBGFX);

			if (isBGFX)
			{
				status = KOTEK_INVOKE_MODULE(SHUTDOWN, RENDER, ShutdownModule_Render_BGFX, main_manager);
			}
			else
			{
				KOTEK_ASSERT(false,
					"only BGFX is supported as a vendor for OpenGL ES "
					"(ANGLE was removed 2026-07-22)");
			}
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
