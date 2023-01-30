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

void ktkGameUI_RMLUI::Initialize(Core::ktkIEngineConfig* p_config,
	void* p_os_window_handle, int width, int height) noexcept
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

	ktkRenderInterface_GL3* p_gl3 = dynamic_cast<ktkRenderInterface_GL3*>(this->m_p_render_interface);

	if (p_gl3)
	{
		p_gl3->SetViewport(width, height);
	}

	// TODO: add for other renderers

	Rml::SetRenderInterface(this->m_p_render_interface);

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	ktkSystemInterface_GLFW* p_system_interface = new ktkSystemInterface_GLFW();
	p_system_interface->SetWindow(static_cast<GLFWwindow*>(p_os_window_handle));

	glfwSetInputMode(static_cast<GLFWwindow*>(p_os_window_handle),
		GLFW_LOCK_KEY_MODS, GLFW_TRUE);


	glfwSetKeyCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* /*window*/, int glfw_key, int /*scancode*/,
			int glfw_action, int glfw_mods)
		{
			if (!data->context)
				return;

			// Store the active modifiers for later because GLFW doesn't provide
		    // them in the callbacks to the mouse input events.
			data->glfw_active_modifiers = glfw_mods;

			// Override the default key event callback to add global shortcuts
		    // for the samples.
			Rml::Context* context = data->context;
			KeyDownCallback key_down_callback = data->key_down_callback;

			switch (glfw_action)
			{
			case GLFW_PRESS:
			case GLFW_REPEAT:
			{
				const Rml::Input::KeyIdentifier key =
					RmlGLFW::ConvertKey(glfw_key);
				const int key_modifier =
					RmlGLFW::ConvertKeyModifiers(glfw_mods);
				float dp_ratio = 1.f;
				glfwGetWindowContentScale(data->window, &dp_ratio, nullptr);

				// See if we have any global shortcuts that take priority over
			    // the context.
				if (key_down_callback &&
					!key_down_callback(
						context, key, key_modifier, dp_ratio, true))
					break;
				// Otherwise, hand the event over to the context by calling the
			    // input handler as normal.
				if (!RmlGLFW::ProcessKeyCallback(
						context, glfw_key, glfw_action, glfw_mods))
					break;
				// The key was not consumed by the context either, try keyboard
			    // shortcuts of lower priority.
				if (key_down_callback &&
					!key_down_callback(
						context, key, key_modifier, dp_ratio, false))
					break;
			}
			break;
			case GLFW_RELEASE:
				RmlGLFW::ProcessKeyCallback(
					context, glfw_key, glfw_action, glfw_mods);
				break;
			}
		});



	this->m_p_system_interface = p_system_interface;

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

void ktkGameUI_RMLUI::UpdateInput(void* p_any, void* p_any2) noexcept {}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
