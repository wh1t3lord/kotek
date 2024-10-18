#include "../include/kotek_ui_game_ui_manager.h"

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

#ifdef KOTEK_RMLUI_LIBRARY
	#include <RmlUi/Core.h>
	#include <RmlUi/Core/Context.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkGameUI_RMLUI::ktkGameUI_RMLUI(void) {}

ktkGameUI_RMLUI::~ktkGameUI_RMLUI(void)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
#endif
}

void ktkGameUI_RMLUI::Initialize(Core::ktkIEngineConfig* p_config,
	void* p_os_window_handle, int width, int height) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	KOTEK_ASSERT(
		p_config, "you must pass a valid instance of engine config here");

	if (p_config)
	{
		auto feature = p_config->GetEngineFeatureRenderer();

		switch (feature)
		{
		case Core::eEngineFeatureRenderer::
			kEngine_Feature_Renderer_OpenGL_SpecifiedByUser:
		{
			if ((p_config->GetRendererVersionEnum() >=
						Core::eEngineSupportedRenderer::kOpenGL_3_0 &&
					p_config->GetRendererVersionEnum() <=
						Core::eEngineSupportedRenderer::kOpenGL_Latest))
			{
				break;
			}
			else
			{
				KOTEK_ASSERT(false, "not implemented");
			}

			break;
		}
		case Core::eEngineFeatureRenderer::
			kEngine_Feature_Renderer_OpenGLES_SpecifiedByUser:

		{
			if ((p_config->GetRendererVersionEnum() >=
						Core::eEngineSupportedRenderer::kOpenGLES_3_0 &&
					p_config->GetRendererVersionEnum() <=
						Core::eEngineSupportedRenderer::kOpenGLES_Latest))
			{
				break;
			}
			else
			{
				KOTEK_ASSERT(false, "not implemented");
			}
			break;
		}
		case Core::eEngineFeatureRenderer::
			kEngine_Feature_Renderer_OpenGL_Latest:
		{
			break;
		}
		default:
		{
			KOTEK_ASSERT(false, "not implemented");
		}
		}
	}

#endif
}

void ktkGameUI_RMLUI::Shutdown(void) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
#endif
}

void ktkGameUI_RMLUI::Render(void) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
#endif
}

void ktkGameUI_RMLUI::Update(void) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
#endif
}

bool ktkGameUI_RMLUI::LoadDocument(const char* p_path_to_file)
{
	bool result{};

	if (!p_path_to_file)
	{
		KOTEK_MESSAGE_WARNING("you need to pass a valid string!");
		return result;
	}

	return result;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
