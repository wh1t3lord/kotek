#include "../include/kotek_std_window.h"
#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.input/include/kotek_input.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkWindow::ktkWindow(ktkMainManager* p_manager) :
	m_screen_size_width{}, m_screen_size_height{}, m_p_window{nullptr},
	m_p_os_data{nullptr}, m_p_main_manager{p_manager}
{
	this->SetStringToTitle(
		static_cast<ktk::enum_base_t>(eWindowTitleType::kTitle_ApplicationName),
		"Kotek Engine");
}

ktkWindow::ktkWindow(const ktk::ustring& title_name) :
	m_screen_size_width{}, m_screen_size_height{}, m_p_window{nullptr},
	m_p_os_data{nullptr}, m_p_main_manager{nullptr}
{
	this->SetStringToTitle(
		static_cast<ktk::enum_base_t>(eWindowTitleType::kTitle_ApplicationName),
		reinterpret_cast<const char*>(title_name.c_str()));
}

ktkWindow::~ktkWindow(void) 
{
	if (this->m_p_os_data)
	{
		delete this->m_p_os_data;
	}
}

void ktkWindow::CloseWindow(void) noexcept
{
	if (this->m_p_window == nullptr)
		return;

	glfwSetWindowShouldClose(this->m_p_window, GLFW_TRUE);
}

void ktkWindow::ShowWindow(void) noexcept
{
	glfwShowWindow(this->m_p_window);
}

void ktkWindow::HideWindow(void) noexcept
{
	glfwHideWindow(this->m_p_window);
}

void ktkWindow::Set_Fullscreen(bool status) noexcept
{
	if (!this->m_p_window)
	{
		KOTEK_MESSAGE_WARNING(
			"you can't switch fullscreen until you initialize the window");
		return;
	}

	if (status)
	{
		GLFWmonitor* p_monitor = glfwGetPrimaryMonitor();

		if (!p_monitor)
		{
			KOTEK_MESSAGE_WARNING(
				"no primary monitor, staying windowed");
			return;
		}

		const GLFWvidmode* p_mode = glfwGetVideoMode(p_monitor);

		glfwSetWindowMonitor(
			this->m_p_window, p_monitor, 0, 0,
			p_mode ? p_mode->width : this->m_screen_size_width,
			p_mode ? p_mode->height : this->m_screen_size_height,
			p_mode ? p_mode->refreshRate : GLFW_DONT_CARE
		);
	}
	else
	{
		glfwSetWindowMonitor(
			this->m_p_window, nullptr, 64, 64,
			this->m_screen_size_width, this->m_screen_size_height,
			GLFW_DONT_CARE
		);
	}
}

int ktkWindow::GetWidth(void) const noexcept
{
	if (this->m_p_window == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"you can't call this until you initialize window");
		return 0;
	}

	int result_width;
	int dummy_height;

	glfwGetWindowSize(this->m_p_window, &result_width, &dummy_height);

	return result_width;
}

int ktkWindow::GetHeight(void) const noexcept
{
	if (this->m_p_window == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"you can't call this until you initialize window");
		return 0;
	}

	int result_height;

	int dummy_width;

	glfwGetWindowSize(this->m_p_window, &dummy_width, &result_height);

	return result_height;
}

void ktkWindow::RegisterUserMainManager(
	kun_core ktkMainManager* p_manager) noexcept
{
	KOTEK_ASSERT(p_manager, "you can't pass an invalid manager");
	KOTEK_ASSERT(this->m_p_window, "you can't have an invalid window");

	glfwSetWindowUserPointer(this->m_p_window, p_manager);
	glfwSetMonitorUserPointer(glfwGetPrimaryMonitor(), p_manager);
}

void* ktkWindow::GetHandle(void) const noexcept
{
	return this->m_p_window;
}

void* ktkWindow::Get_OSData(void) noexcept
{
	return this->m_p_os_data;
}

// exe-side input feeding (task K26): these callbacks run against THIS
// module's GLFW copy — the only initialized one in the process (see the
// class comment in kotek_std_window.h). They feed the main manager's
// input manager unconditionally (editor and game boots alike); the guard
// is "the input manager exists AND was initialized for GLFW3", otherwise
// Update_Controller would assert on the backend mismatch (zircon's
// initialize_input runs after the window exists, so early events can
// arrive before it). Scroll is not forwarded: eInputControllerMouseData
// has no scroll fields today.

ktkMainManager* window_callback_get_manager(GLFWwindow* p_window)
{
	ktkMainManager* p_manager = static_cast<ktkMainManager*>(
		glfwGetWindowUserPointer(p_window));

	if (!p_manager)
		return nullptr;

	ktkIInput* p_input = p_manager->Get_Input();

	if (!p_input)
		return nullptr;

	if (p_input->Get_PlatformBackend() !=
		eInputPlatformBackend::kPlatformBackend_GLFW3)
		return nullptr;

	return p_manager;
}

void window_callback_key(
	GLFWwindow* p_window, int glfw_key, int scancode, int glfw_action,
	int glfw_mods)
{
	ktkMainManager* p_manager = window_callback_get_manager(p_window);

	if (!p_manager)
		return;

	// GLFW_KEY_UNKNOWN (-1) is sent for keys without a token — the input
	// translation tables are indexed by the raw key, a negative index is
	// out of bounds (user input is not a programmer error, so no assert)
	if (glfw_key < 0)
		return;

	ktkInputPlatformBackendArgs_GLFW3 args;
	args.key = glfw_key;
	args.action = glfw_action;
	args.scancode = scancode;
	args.mods = glfw_mods;
	args.controller = eInputControllerType::kControllerKeyboard;

	p_manager->Get_Input()->Update_Controller(&args);
}

void window_callback_mouse_button(
	GLFWwindow* p_window, int button, int action, int mods)
{
	ktkMainManager* p_manager = window_callback_get_manager(p_window);

	if (!p_manager)
		return;

	ktkInputPlatformBackendArgs_GLFW3 args;
	args.key = button;
	args.action = action;
	args.scancode = -1;
	args.mods = mods;
	args.controller = eInputControllerType::kControllerMouse;

	p_manager->Get_Input()->Update_Controller(&args);
}

void window_callback_cursor_pos(GLFWwindow* p_window, double xpos, double ypos)
{
	ktkMainManager* p_manager = window_callback_get_manager(p_window);

	if (!p_manager)
		return;

	ktkIInput* p_input = p_manager->Get_Input();

	p_input->Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMousePreviousCoordinateXInPixels,
		p_input->Get_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateXInPixels));
	p_input->Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMousePreviousCoordinateYInPixels,
		p_input->Get_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateYInPixels));

	p_input->Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMouseCoordinateXInPixels, xpos);
	p_input->Set_ControllerData(eInputControllerType::kControllerMouse,
		eInputControllerMouseData::kMouseCoordinateYInPixels, ypos);

	float width = static_cast<float>(
		p_manager->Get_WindowManager()->ActiveWindow_GetWidth());
	float height = static_cast<float>(
		p_manager->Get_WindowManager()->ActiveWindow_GetHeight());

	// a minimized window reports 0x0 — skip the normalized pair then
	// (window state is not a programmer error, so no assert)
	bool is_valid = true;
	if (width == 0.0f)
	{
		is_valid = false;
	}

	if (height == 0.0f)
	{
		is_valid = false;
	}

	if (is_valid)
	{
		p_input->Set_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateXNormalized,
			xpos / width);
		p_input->Set_ControllerData(eInputControllerType::kControllerMouse,
			eInputControllerMouseData::kMouseCoordinateYNormalized,
			ypos / height);
	}

	p_input->Set_ControllerUpdate(eInputControllerType::kControllerMouse);
}

void ktkWindow::Initialize(kun_core eEngineSupportedRenderer version, kun_core eEngineFeatureRendererVendor vendor)
{
	if (version >= kun_core eEngineSupportedRenderer::kOpenGL_1_0 &&
		version <= kun_core eEngineSupportedRenderer::kOpenGL_Latest)
	{
		if (!glfwInit())
		{
			KOTEK_ASSERT(false, "can't initialize GLFW");
			return;
		}

		KOTEK_ASSERT(version != kun_core eEngineSupportedRenderer::kUnknown,
			"you must pass a valid version of OpenGL what you want to "
			"initialize "
			"for");

		switch (version)
		{
		case kun_core eEngineSupportedRenderer::kOpenGL_1_0:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_1_1:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_1_2:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_1_3:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_1_4:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_1_5:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_2_0:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_2_1:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_3_0:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_3_1:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_3_2:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_3_3:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_0:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_1:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_2:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_3:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_4:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_5:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			break;
		}
		case kun_core eEngineSupportedRenderer::kOpenGL_4_6:
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			break;
		}
		default:
		{
			// TODO: create preprocessor for defininng major and minor version
			// through preprocessor and configurable from cmake for user
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			break;
		}
		}

		// TODO: make changable core or compat profile choosing, again you need
		// to create configurable macro for this
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->ObtainInformationAboutDisplay();

		this->m_p_window = glfwCreateWindow(this->m_screen_size_width,
			this->m_screen_size_height, this->GetTitle().c_str(), nullptr,
			nullptr);

		if (!this->m_p_window)
		{
			glfwTerminate();
			KOTEK_ASSERT(false, "can't create GLFW window");
			return;
		}
	}
	else if (version >= kun_core eEngineSupportedRenderer::kOpenGLES_1 &&
		version <= kun_core eEngineSupportedRenderer::kOpenGLES_Latest)
	{
		if (!glfwInit())
		{
			KOTEK_ASSERT(false, "can't initialize GLFW");
			return;
		}

		KOTEK_ASSERT(version != kun_core eEngineSupportedRenderer::kUnknown,
			"you must pass a valid version of OpenGL what you want to "
			"initialize "
			"for");

		bool isNOAPI =
			((vendor & kun_core eEngineFeatureRendererVendor::kBGFX) ==
				kun_core eEngineFeatureRendererVendor::kBGFX);

		if (isNOAPI)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}
		else
		{
			switch (version)
			{
			case kun_core eEngineSupportedRenderer::kOpenGLES_1:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
				break;
			}
			case kun_core eEngineSupportedRenderer::kOpenGLES_2:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
				break;
			}
			case kun_core eEngineSupportedRenderer::kOpenGLES_3_0:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
				break;
			}
			case kun_core eEngineSupportedRenderer::kOpenGLES_3_1:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
				break;
			}
			case kun_core eEngineSupportedRenderer::kOpenGLES_3_2:
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
				break;
			}
			default:
			{
				// TODO: create preprocessor for defininng major and minor
				// version through preprocessor and configurable from cmake for
				// user
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
				break;
			}
			}

			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
		}



		this->ObtainInformationAboutDisplay();

		this->m_p_window = glfwCreateWindow(this->m_screen_size_width,
			this->m_screen_size_height, this->GetTitle().c_str(), nullptr,
			nullptr);

		if (!this->m_p_window)
		{
			const char* p_test{};
			glfwGetError(&p_test);
			KOTEK_ASSERT(false,
				"can't create GLFW window, reason: {} (probably your forgot to "
				"put libEGL.dll into folder)",
				p_test);
			glfwTerminate();
			return;
		}
	}
	else if (version >= kun_core eEngineSupportedRenderer::kDirectX_7 &&
		version <= kun_core eEngineSupportedRenderer::kDirectX_Latest)
	{
		if (!glfwInit())
		{
			KOTEK_ASSERT(false, "can't initialize GLFW");
			return;
		}

		KOTEK_ASSERT(version != kun_core eEngineSupportedRenderer::kUnknown,
			"you must pass a valid version of DirectX what you want to "
			"initialize "
			"for");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		this->ObtainInformationAboutDisplay();

		this->m_p_window = glfwCreateWindow(this->m_screen_size_width,
			this->m_screen_size_height, "Kotek Engine", nullptr, nullptr);

		if (!this->m_p_window)
		{
			glfwTerminate();
			KOTEK_ASSERT(false, "can't create GLFW window");
			return;
		}
	}
	else if (version <= kun_core eEngineSupportedRenderer::kVulkan_1_0 &&
		version <= kun_core eEngineSupportedRenderer::kVulkan_Latest)
	{
		if (!glfwInit())
		{
			KOTEK_ASSERT(false, "can't initialize GLFW");
			return;
		}

		KOTEK_ASSERT(version != kun_core eEngineSupportedRenderer::kUnknown,
			"you must pass a valid version of DirectX what you want to "
			"initialize "
			"for");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		this->ObtainInformationAboutDisplay();

		this->m_p_window = glfwCreateWindow(this->m_screen_size_width,
			this->m_screen_size_height, "Kotek Engine", nullptr, nullptr);

		if (!this->m_p_window)
		{
			glfwTerminate();
			KOTEK_ASSERT(false, "can't create GLFW window");
			return;
		}
	}

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	this->m_p_os_data = new ktkWin32OSData();
	ktkWin32OSData* p_casted_impl =
		static_cast<ktkWin32OSData*>(this->m_p_os_data);
	p_casted_impl->hWnd = glfwGetWin32Window(this->m_p_window);

	KOTEK_ASSERT(p_casted_impl->hWnd, "must exist!");

	p_casted_impl->hInstance = GetModuleHandleA(NULL);

	KOTEK_ASSERT(p_casted_impl->hInstance, "must be defined!");
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif

	if (this->m_p_window && this->m_p_main_manager)
	{
		// task K26: install the input callbacks on THIS module's GLFW
		// copy — the only initialized one in the process — and hand the
		// main manager to them through the window user pointer.
		// Unconditional: editor and game boots both need input. The
		// imgui backend installs its own callbacks later
		// (ImGui_InitForOther with install_callbacks=true) and chains
		// into these as PrevUserCallback*, so the ordering is safe.
		glfwSetWindowUserPointer(this->m_p_window, this->m_p_main_manager);
		glfwSetKeyCallback(this->m_p_window, &window_callback_key);
		glfwSetMouseButtonCallback(
			this->m_p_window, &window_callback_mouse_button);
		glfwSetCursorPosCallback(
			this->m_p_window, &window_callback_cursor_pos);
	}
}

void ktkWindow::Shutdown(void)
{
	if (this->m_p_window)
	{
		this->CloseWindow();
		glfwDestroyWindow(this->m_p_window);
		glfwTerminate();
		this->m_p_window = nullptr;
	}
}

void ktkWindow::MakeContextCurrent(void) noexcept
{
	if (this->m_p_window)
	{
		glfwMakeContextCurrent(this->m_p_window);

#ifdef KOTEK_DEBUG
		const char* description_error{};
		if (glfwGetError(&description_error))
		{
			KOTEK_MESSAGE("{}", description_error);
		}
#endif
	}
}

void ktkWindow::PollEvents(void)
{
	glfwPollEvents();

#ifdef KOTEK_DEBUG
	const char* description_error{};
	if (glfwGetError(&description_error))
	{
		KOTEK_MESSAGE("{}", description_error);
	}
#endif
}

bool ktkWindow::Is_NeedToClose(void)
{
	return glfwWindowShouldClose(this->m_p_window);
}

void ktkWindow::SetStringToTitle(
	ktk::enum_base_t id, const char* p_utf8_or_char_string) noexcept
{
	KOTEK_ASSERT(p_utf8_or_char_string,
		"you can't pass an invalid pointer of string here");

	this->m_titles[id] = p_utf8_or_char_string;

	if (this->m_p_window)
	{
		glfwSetWindowTitle(this->m_p_window, this->GetTitle().c_str());
	}
}

void ktkWindow::RemoveStringFromTitle(ktk::enum_base_t id) noexcept
{
	if (this->m_titles.find(id) != this->m_titles.end())
	{
		this->m_titles.erase(id);
	}
}

ktk::cstring ktkWindow::GetTitle(void) const noexcept
{
	ktk::cstring result;

	for (const auto& [id, string] : this->m_titles)
	{
		result += string;
		result += " ";
	}

	result.pop_back();

	return result;
}

void ktkWindow::Set_InputType(ktk::enum_base_t type) noexcept
{
	Kotek::kun_core eInputType input = static_cast<Kotek::kun_core eInputType>(type);

	switch (input)
	{
	case kun_core eInputType::kInputType_Cursor:
	{
		if (this->m_p_window)
		{
			glfwSetInputMode(this->m_p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		break;
	}
	case kun_core eInputType::kInputType_DisabledCursor:
	{
		if (this->m_p_window)
		{
			glfwSetInputMode(
				this->m_p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		break;
	}
	case kun_core eInputType::kInputType_HiddenCursor:
	{
		if (this->m_p_window)
		{
			glfwSetInputMode(this->m_p_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		break;
	}
	default:
	{
		KOTEK_ASSERT(false,
			"you pass wrong type or can't find the value of enum: {}", type);
	}
	}
}

void ktkWindow::ObtainInformationAboutDisplay(void)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	if (!mode)
	{
		const char* message;
		glfwGetError(&message);
		KOTEK_ASSERT(false, "{}", message);
		return;
	}

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("display width: {}", mode->width);
	KOTEK_MESSAGE("display height: {}", mode->height);
#endif

	this->m_screen_size_height = mode->height;
	this->m_screen_size_width = mode->width;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
