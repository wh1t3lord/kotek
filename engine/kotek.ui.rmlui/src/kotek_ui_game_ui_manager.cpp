#include "../include/kotek_ui_game_ui_manager.h"

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

#ifdef KOTEK_RMLUI_LIBRARY
	#include <RmlUi/Core.h>
	#include <RmlUi/Core/Context.h>
	#include "../include/kotek_ui_rmlui_render_interface_gl3.h"

	#include "../include/kotek_ui_rmlui_system_interface_glfw.h"
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkGameUI_RMLUI::ktkGameUI_RMLUI(void) :
	m_p_render_interface{}, m_p_system_interface{}, m_p_context{}
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

	ktkRenderInterface_GL3* p_gl3 =
		dynamic_cast<ktkRenderInterface_GL3*>(this->m_p_render_interface);

	if (p_gl3)
	{
		p_gl3->SetViewport(width, height);
	}

	// TODO: add for other renderers

	Rml::SetRenderInterface(this->m_p_render_interface);

	this->m_p_context =
		Rml::CreateContext("main", Rml::Vector2i(width, height));

	KOTEK_ASSERT(this->m_p_context,
		"can't create context for RMLUI something is wrong, probably library "
		"doesn't support your system...");

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	this->Initialize_GLFW(p_os_window_handle);
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
#ifdef KOTEK_USE_RMLUI_LIBRARY

#endif
}

void ktkGameUI_RMLUI::Render(void) noexcept {
#ifdef KOTEK_USE_RMLUI_LIBRARY

#endif
}

Rml::RenderInterface* ktkGameUI_RMLUI::Get_RenderInterface(void)
{
	return this->m_p_render_interface;
}

Rml::SystemInterface* ktkGameUI_RMLUI::Get_SystemInterface(void)
{
	return this->m_p_system_interface;
}

Rml::Context* ktkGameUI_RMLUI::Get_Context(void)
{
	return this->m_p_context;
}

void ktkGameUI_RMLUI::Initialize_GLFW(void* p_os_window_handle)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	ktkSystemInterface_GLFW* p_system_interface = new ktkSystemInterface_GLFW();
	p_system_interface->SetWindow(static_cast<GLFWwindow*>(p_os_window_handle));

	glfwSetInputMode(static_cast<GLFWwindow*>(p_os_window_handle),
		GLFW_LOCK_KEY_MODS, GLFW_TRUE);

	Rml::Context* p_context = this->m_p_context;
	glfwSetWindowUserPointer(
		static_cast<GLFWwindow*>(p_os_window_handle), this);

	glfwSetKeyCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, int glfw_key, int /*scancode*/, int glfw_action,
			int glfw_mods)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			ktkSystemInterface_GLFW* p_system_interface =
				static_cast<ktkSystemInterface_GLFW*>(
					p_casted->Get_SystemInterface());
			auto* p_context = p_casted->Get_Context();

			// Store the active modifiers for later because GLFW doesn't provide
		    // them in the callbacks to the mouse input events.
			p_system_interface->Set_GLFWActiveModifies(glfw_mods);

			// Override the default key event callback to add global shortcuts
		    // for the samples.
			KeyDownCallback key_down_callback =
				p_system_interface->Get_KeyDownCallback();

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
				glfwGetWindowContentScale(
					static_cast<GLFWwindow*>(window), &dp_ratio, nullptr);

				// See if we have any global shortcuts that take priority over
			    // the context.
				if (key_down_callback &&
					!key_down_callback(
						p_context, key, key_modifier, dp_ratio, true))
					break;
				// Otherwise, hand the event over to the context by calling the
			    // input handler as normal.
				if (!RmlGLFW::ProcessKeyCallback(
						p_context, glfw_key, glfw_action, glfw_mods))
					break;
				// The key was not consumed by the context either, try keyboard
			    // shortcuts of lower priority.
				if (key_down_callback &&
					!key_down_callback(
						p_context, key, key_modifier, dp_ratio, false))
					break;
			}
			break;
			case GLFW_RELEASE:
				RmlGLFW::ProcessKeyCallback(
					p_context, glfw_key, glfw_action, glfw_mods);
				break;
			}
		});

	glfwSetCharCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, unsigned int codepoint)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			RmlGLFW::ProcessCharCallback(p_casted->Get_Context(), codepoint);
		});

	glfwSetCursorEnterCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, int entered)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			RmlGLFW::ProcessCursorEnterCallback(
				p_casted->Get_Context(), entered);
		});

	// Mouse input
	glfwSetCursorPosCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, double xpos, double ypos)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			ktkSystemInterface_GLFW* p_system_interface =
				static_cast<ktkSystemInterface_GLFW*>(
					p_casted->Get_SystemInterface());

			RmlGLFW::ProcessCursorPosCallback(p_casted->Get_Context(), xpos,
				ypos, p_system_interface->Get_GLFWActiveModifiers());
		});

	glfwSetMouseButtonCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, int button, int action, int mods)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			ktkSystemInterface_GLFW* p_system_interface =
				static_cast<ktkSystemInterface_GLFW*>(
					p_casted->Get_SystemInterface());

			p_system_interface->Set_GLFWActiveModifies(mods);
			RmlGLFW::ProcessMouseButtonCallback(
				p_casted->Get_Context(), button, action, mods);
		});

	glfwSetScrollCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, double /*xoffset*/, double yoffset)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			ktkSystemInterface_GLFW* p_system_interface =
				static_cast<ktkSystemInterface_GLFW*>(
					p_casted->Get_SystemInterface());

			RmlGLFW::ProcessScrollCallback(p_casted->Get_Context(), yoffset,
				p_system_interface->Get_GLFWActiveModifiers());
		});

	// Window events
	glfwSetFramebufferSizeCallback(static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, int width, int height)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			ktkRenderInterface_GL3* p_gl3 =
				dynamic_cast<ktkRenderInterface_GL3*>(
					p_casted->Get_RenderInterface());

			if (p_gl3)
			{
				p_gl3->SetViewport(width, height);
			}

			RmlGLFW::ProcessFramebufferSizeCallback(
				p_casted->Get_Context(), width, height);
		});

	glfwSetWindowContentScaleCallback(
		static_cast<GLFWwindow*>(p_os_window_handle),
		[](GLFWwindow* window, float xscale, float /*yscale*/)
		{
			Core::ktkMainManager* p_manager =
				static_cast<Core::ktkMainManager*>(
					glfwGetWindowUserPointer(static_cast<GLFWwindow*>(window)));

			if (!p_manager)
				return;

			if (!p_manager->Get_GameUIEngine())
				return;

			ktkGameUI_RMLUI* p_casted =
				dynamic_cast<ktkGameUI_RMLUI*>(p_manager->Get_GameUIEngine());

			if (!p_casted)
				return;

			RmlGLFW::ProcessContentScaleCallback(
				p_casted->Get_Context(), xscale);
		});

	this->m_p_system_interface = p_system_interface;

	Rml::SetSystemInterface(this->m_p_system_interface);
#endif
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
