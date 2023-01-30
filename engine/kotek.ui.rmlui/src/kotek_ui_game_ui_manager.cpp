#include "../include/kotek_ui_game_ui_manager.h"

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

#ifdef KOTEK_RMLUI_LIBRARY
	#include <RmlUi/Core.h>

	#include "../include/kotek_ui_rmlui_render_interface_gl3.h"

	#include "../include/kotek_ui_rmlui_system_interface_glfw.h"
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkGameUI_RMLUI::ktkGameUI_RMLUI(void) :
	m_p_render_interface{}, m_p_system_interface{}
{
}

ktkGameUI_RMLUI::~ktkGameUI_RMLUI(void)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	if (this->m_p_render_interface)
	{
		delete this->m_p_render_interface;
		this->m_p_render_interface = nullptr;
	}

	if (this->m_p_system_interface)
	{
		delete this->m_p_system_interface;
		this->m_p_system_interface = nullptr;
	}
#endif
}

void ktkGameUI_RMLUI::Initialize(Core::ktkIEngineConfig* p_config) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	bool status = Rml::Initialise();

	KOTEK_ASSERT(status, "Can't initialize RmlUI library!");

	KOTEK_ASSERT(
		p_config, "you must pass a valid instance of engine config here");

	if (p_config)
	{
		auto feature = p_config->GetEngineFeatureRenderer();

		switch (feature)
		{
		case Core::eEngineFeatureRenderer::
			kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
		{
			if (p_config->GetOpenGLVersionForLoading() >=
				Core::eEngineSupportedOpenGLVersion::kOpenGL_3_0)
			{
				this->m_p_render_interface = new ktkRenderInterface_GL3();
			}
			else
			{
				KOTEK_ASSERT(false, "not implemented");
			}
		}
		case Core::eEngineFeatureRenderer::
			kEngine_Render_Renderer_OpenGL_Latest:
		{
			this->m_p_render_interface = new ktkRenderInterface_GL3();
		}
		default:
		{
			KOTEK_ASSERT(false, "not implemented");
		}
		}
	}

	KOTEK_ASSERT(this->m_p_render_interface,
		"failed to initialize renderer internface because there's no "
		"implemented solution for your request!");

	Rml::SetRenderInterface(this->m_p_render_interface);

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	this->m_p_system_interface = new ktkSystemInterface_GLFW();

	Rml::SetSystemInterface(this->m_p_system_interface);
	#elif KOTEK_USE_WINDOW_LIBRARY_SDL

	#endif

#endif
}

void ktkGameUI_RMLUI::Shutdown(void) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	Rml::Shutdown();

	if (this->m_p_system_interface)
	{
		delete this->m_p_system_interface;
		this->m_p_system_interface = nullptr;
	}

	if (this->m_p_render_interface)
	{
		delete this->m_p_render_interface;
		this->m_p_render_interface = nullptr;
	}
#endif
}

void ktkGameUI_RMLUI::UpdateInput(void* p_any, void* p_any2) noexcept 
{
	
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
