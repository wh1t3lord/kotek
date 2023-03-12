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
			if ((p_config->GetRendererVersionEnum() >=
						Core::eEngineSupportedRenderer::kOpenGL_3_0 &&
					p_config->GetRendererVersionEnum() <=
						Core::eEngineSupportedRenderer::kOpenGL_Latest))
			{
				this->m_p_render_interface = new ktkRenderInterface_GL3(p_config->GetRendererVersionEnum());
				break;
			}
			else
			{
				KOTEK_ASSERT(false, "not implemented");
			}

			break;
		}
		case Core::eEngineFeatureRenderer::
		kEngine_Render_Renderer_OpenGLES_SpecifiedByUser:
				
		{
			if ((p_config->GetRendererVersionEnum() >=
						Core::eEngineSupportedRenderer::kOpenGLES_3_0 &&
					p_config->GetRendererVersionEnum() <=
						Core::eEngineSupportedRenderer::kOpenGLES_Latest))
			{
				this->m_p_render_interface = new ktkRenderInterface_GL3(p_config->GetRendererVersionEnum());
				break;
			}
			else
			{
				KOTEK_ASSERT(false, "not implemented");
			}
			break;
		}
		case Core::eEngineFeatureRenderer::
			kEngine_Render_Renderer_OpenGL_Latest:
		{
			this->m_p_render_interface = new ktkRenderInterface_GL3(p_config->GetRendererVersionEnum());
			break;
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

	// TODO: think about it well
	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	this->Initialize_GLFW(p_os_window_handle);
	#elif KOTEK_USE_WINDOW_LIBRARY_SDL

	#endif

	bool status = Rml::Initialise();
	KOTEK_ASSERT(status, "Can't initialize RmlUI library!");

	this->m_p_context =
		Rml::CreateContext("main", Rml::Vector2i(width, height));

	KOTEK_ASSERT(this->m_p_context,
		"can't create context for RMLUI something is wrong, probably library "
		"doesn't support your system...");

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

void ktkGameUI_RMLUI::Render(void) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	ktkRenderInterface_GL3* p_render_interface =
		static_cast<ktkRenderInterface_GL3*>(this->m_p_render_interface);

	p_render_interface->BeginFrame();
	p_render_interface->Clear();

	this->m_p_context->Render();

	p_render_interface->EndFrame();
#endif
}

void ktkGameUI_RMLUI::Update(void) noexcept
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	if (this->m_p_context)
	{
		this->m_p_context->Update();
	}
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

	if (!this->m_p_context)
	{
		KOTEK_MESSAGE_WARNING("context wasn't initialized");
		return result;
	}

	result = !!(this->m_p_context->LoadDocument(p_path_to_file));

	return result;
}

Rml::RenderInterface* ktkGameUI_RMLUI::Get_RenderInterface(void)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	return this->m_p_render_interface;
#else
	return nullptr;
#endif
}

Rml::SystemInterface* ktkGameUI_RMLUI::Get_SystemInterface(void)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	return this->m_p_system_interface;
#else
	return nullptr;
#endif
}

Rml::Context* ktkGameUI_RMLUI::Get_Context(void)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	return this->m_p_context;
#else
	return nullptr;
#endif
}

void ktkGameUI_RMLUI::Initialize_GLFW(void* p_os_window_handle)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	ktkSystemInterface_GLFW* p_system_interface = new ktkSystemInterface_GLFW();
	p_system_interface->SetWindow(static_cast<GLFWwindow*>(p_os_window_handle));

	glfwSetInputMode(static_cast<GLFWwindow*>(p_os_window_handle),
		GLFW_LOCK_KEY_MODS, GLFW_TRUE);

	this->m_p_system_interface = p_system_interface;

	Rml::SetSystemInterface(this->m_p_system_interface);
#endif
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
