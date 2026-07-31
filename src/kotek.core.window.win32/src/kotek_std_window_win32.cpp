#include "../include/kotek_std_window_win32.h"
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_PLATFORM_WINDOWS

namespace
{
	/// \~english the window class is a process-lifetime registration — it is
	/// created once and never unregistered (the OS reclaims it at exit, like
	/// every other module-lifetime static in this codebase)
	const char* g_window_class_name = "kotek_win32_window_class";
	bool g_window_class_registered = false;
} // namespace

ktkWindowWin32::ktkWindowWin32(void) :
	m_screen_size_width{}, m_screen_size_height{}, m_hwnd{nullptr},
	m_p_os_data{nullptr}, m_p_main_manager{nullptr}, m_is_need_to_close{false}, m_is_fullscreen{false}
{
	this->SetStringToTitle(
		static_cast<ktk::enum_base_t>(eWindowTitleType::kTitle_ApplicationName),
		"Kotek Engine");
}

ktkWindowWin32::ktkWindowWin32(const ktk::ustring& title_name) :
	m_screen_size_width{}, m_screen_size_height{}, m_hwnd{nullptr},
	m_p_os_data{nullptr}, m_p_main_manager{nullptr}, m_is_need_to_close{false}, m_is_fullscreen{false}
{
	this->SetStringToTitle(
		static_cast<ktk::enum_base_t>(eWindowTitleType::kTitle_ApplicationName),
		reinterpret_cast<const char*>(title_name.c_str()));
}

ktkWindowWin32::~ktkWindowWin32(void)
{
	if (this->m_p_os_data)
	{
		delete this->m_p_os_data;
	}
}

void ktkWindowWin32::CloseWindow(void) noexcept
{
	if (this->m_hwnd == nullptr)
		return;

	// the flag flips in the proc — same observable semantics as
	// glfwSetWindowShouldClose
	PostMessageA(this->m_hwnd, WM_CLOSE, 0, 0);
}

void ktkWindowWin32::ShowWindow(void) noexcept
{
	if (this->m_hwnd)
	{
		::ShowWindow(this->m_hwnd, SW_SHOW);
	}
}

void ktkWindowWin32::HideWindow(void) noexcept
{
	if (this->m_hwnd)
	{
		::ShowWindow(this->m_hwnd, SW_HIDE);
	}
}

void ktkWindowWin32::Set_Fullscreen(bool status) noexcept
{
	if (!this->m_hwnd)
	{
		KOTEK_MESSAGE_WARNING(
			"you can't switch fullscreen until you initialize the window");
		return;
	}

	if (status == this->m_is_fullscreen)
		return;

	static WINDOWPLACEMENT saved_placement{};

	if (status)
	{
		// borderless popup over the primary monitor (the win32 equivalent
		// of glfwSetWindowMonitor on the primary monitor)
		saved_placement.length = sizeof(saved_placement);
		GetWindowPlacement(this->m_hwnd, &saved_placement);

		const int width = GetSystemMetrics(SM_CXSCREEN);
		const int height = GetSystemMetrics(SM_CYSCREEN);

		SetWindowLongPtrA(this->m_hwnd, GWL_STYLE,
			WS_POPUP | WS_VISIBLE);
		SetWindowPos(this->m_hwnd, HWND_TOP, 0, 0, width, height,
			SWP_FRAMECHANGED | SWP_SHOWWINDOW);

		this->m_is_fullscreen = true;
	}
	else
	{
		SetWindowLongPtrA(this->m_hwnd, GWL_STYLE,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE);

		if (saved_placement.length == sizeof(saved_placement))
		{
			SetWindowPlacement(this->m_hwnd, &saved_placement);
		}
		else
		{
			SetWindowPos(this->m_hwnd, HWND_NOTOPMOST, 64, 64,
				this->m_screen_size_width, this->m_screen_size_height,
				SWP_FRAMECHANGED | SWP_SHOWWINDOW);
		}

		this->m_is_fullscreen = false;
	}
}

int ktkWindowWin32::GetWidth(void) const noexcept
{
	if (this->m_hwnd == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"you can't call this until you initialize window");
		return 0;
	}

	RECT client_rect{};
	GetClientRect(this->m_hwnd, &client_rect);

	return static_cast<int>(client_rect.right - client_rect.left);
}

int ktkWindowWin32::GetHeight(void) const noexcept
{
	if (this->m_hwnd == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"you can't call this until you initialize window");
		return 0;
	}

	RECT client_rect{};
	GetClientRect(this->m_hwnd, &client_rect);

	return static_cast<int>(client_rect.bottom - client_rect.top);
}

void ktkWindowWin32::RegisterUserMainManager(
	kun_core ktkMainManager* p_manager) noexcept
{
	KOTEK_ASSERT(p_manager, "you can't pass an invalid manager");
	KOTEK_ASSERT(this->m_hwnd, "you can't have an invalid window");

	this->m_p_main_manager = p_manager;
}

void* ktkWindowWin32::GetHandle(void) const noexcept
{
	return this->m_hwnd;
}

void* ktkWindowWin32::Get_OSData(void) noexcept
{
	return this->m_p_os_data;
}

void ktkWindowWin32::Initialize(kun_core eEngineSupportedRenderer version,
	kun_core eEngineFeatureRendererVendor vendor)
{
	bool is_no_api = false;

	if (version >= kun_core eEngineSupportedRenderer::kOpenGL_1_0 &&
		version <= kun_core eEngineSupportedRenderer::kOpenGL_Latest)
	{
		// the GL/GLES branches were removed with the GL backends (task K11):
		// bgfx is the raster backend and it owns its context
		KOTEK_ASSERT(false,
			"the OpenGL backends were removed (2026-07-22): use bgfx (raster) "
			"or NRI (dx12/vk + ray tracing)");
		return;
	}
	else if (version >= kun_core eEngineSupportedRenderer::kOpenGLES_1 &&
		version <= kun_core eEngineSupportedRenderer::kOpenGLES_Latest)
	{
		is_no_api = ((vendor & kun_core eEngineFeatureRendererVendor::kBGFX) ==
			kun_core eEngineFeatureRendererVendor::kBGFX);

		KOTEK_ASSERT(is_no_api,
			"the OpenGL ES backends were removed (2026-07-22): use bgfx "
			"(raster) or NRI (dx12/vk + ray tracing)");

		if (!is_no_api)
			return;
	}
	else if (version >= kun_core eEngineSupportedRenderer::kDirectX_7 &&
		version <= kun_core eEngineSupportedRenderer::kDirectX_Latest)
	{
		is_no_api = true;
	}
	else if (version >= kun_core eEngineSupportedRenderer::kVulkan_1_0 &&
		version <= kun_core eEngineSupportedRenderer::kVulkan_Latest)
	{
		is_no_api = true;
	}
	else
	{
		KOTEK_ASSERT(false,
			"you must pass a valid renderer version for window "
			"initialization!");
		return;
	}

	this->ObtainInformationAboutDisplay();
	this->Create_OsWindow(this->GetTitle().c_str());

	if (!this->m_hwnd)
	{
		KOTEK_ASSERT(false, "can't create the Win32 window");
		return;
	}

	this->m_p_os_data = new ktkWin32OSData();
	ktkWin32OSData* p_casted_impl =
		static_cast<ktkWin32OSData*>(this->m_p_os_data);
	p_casted_impl->hWnd = this->m_hwnd;

	KOTEK_ASSERT(p_casted_impl->hWnd, "must exist!");

	p_casted_impl->hInstance = GetModuleHandleA(NULL);

	KOTEK_ASSERT(p_casted_impl->hInstance, "must be defined!");
}

void ktkWindowWin32::Shutdown(void)
{
	if (this->m_hwnd)
	{
		DestroyWindow(this->m_hwnd);
		this->m_hwnd = nullptr;
		this->m_is_need_to_close = false;
	}
}

void ktkWindowWin32::MakeContextCurrent(void) noexcept
{
	// no-op by design: there is no GL context on this backend — bgfx/NRI
	// own the device and the swap chain (see the NO_API path in Initialize)
}

void ktkWindowWin32::PollEvents(void)
{
	MSG message{};
	while (PeekMessageA(&message, this->m_hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessageA(&message);
	}

	// a quit posted outside the window (console command, WM_QUIT from the
	// OS) must close the engine too
	if (message.message == WM_QUIT)
	{
		this->m_is_need_to_close = true;
	}
}

bool ktkWindowWin32::Is_NeedToClose(void)
{
	return this->m_is_need_to_close;
}

void ktkWindowWin32::SetStringToTitle(
	ktk::enum_base_t id, const char* p_utf8_or_char_string) noexcept
{
	KOTEK_ASSERT(p_utf8_or_char_string,
		"you can't pass an invalid pointer of string here");

	this->m_titles[id] = p_utf8_or_char_string;

	if (this->m_hwnd)
	{
		SetWindowTextA(this->m_hwnd, this->GetTitle().c_str());
	}
}

void ktkWindowWin32::RemoveStringFromTitle(ktk::enum_base_t id) noexcept
{
	if (this->m_titles.find(id) != this->m_titles.end())
	{
		this->m_titles.erase(id);
	}
}

ktk::cstring ktkWindowWin32::GetTitle(void) const noexcept
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

void ktkWindowWin32::Set_InputType(ktk::enum_base_t type) noexcept
{
	kun_core eInputType input = static_cast<kun_core eInputType>(type);

	switch (input)
	{
	case kun_core eInputType::kInputType_Cursor:
	{
		if (this->m_hwnd)
		{
			ClipCursor(nullptr);
			while (ShowCursor(TRUE) < 0)
				;
		}

		break;
	}
	case kun_core eInputType::kInputType_DisabledCursor:
	{
		if (this->m_hwnd)
		{
			RECT client_rect{};
			GetClientRect(this->m_hwnd, &client_rect);
			POINT top_left{client_rect.left, client_rect.top};
			POINT bottom_right{client_rect.right, client_rect.bottom};
			ClientToScreen(this->m_hwnd, &top_left);
			ClientToScreen(this->m_hwnd, &bottom_right);
			RECT clip_rect{top_left.x, top_left.y, bottom_right.x,
				bottom_right.y};
			ClipCursor(&clip_rect);
			while (ShowCursor(FALSE) >= 0)
				;
		}

		break;
	}
	case kun_core eInputType::kInputType_HiddenCursor:
	{
		if (this->m_hwnd)
		{
			while (ShowCursor(FALSE) >= 0)
				;
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

void ktkWindowWin32::ObtainInformationAboutDisplay(void)
{
	this->m_screen_size_width = GetSystemMetrics(SM_CXSCREEN);
	this->m_screen_size_height = GetSystemMetrics(SM_CYSCREEN);

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("display width: {}", this->m_screen_size_width);
	KOTEK_MESSAGE("display height: {}", this->m_screen_size_height);
#endif
}

void ktkWindowWin32::Create_OsWindow(const char* p_title) noexcept
{
	if (g_window_class_registered == false)
	{
		WNDCLASSEXA window_class{};
		window_class.cbSize = sizeof(window_class);
		window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		window_class.lpfnWndProc = &ktkWindowWin32::WindowProc_Win32;
		window_class.hInstance = GetModuleHandleA(NULL);
		window_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
		window_class.hbrBackground =
			reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		window_class.lpszClassName = g_window_class_name;

		if (RegisterClassExA(&window_class) == 0)
		{
			KOTEK_ASSERT(false,
				"failed to register the Win32 window class, error {}",
				GetLastError());
			return;
		}

		g_window_class_registered = true;
	}

	this->m_hwnd = CreateWindowExA(0, g_window_class_name, p_title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		this->m_screen_size_width, this->m_screen_size_height, nullptr,
		nullptr, GetModuleHandleA(NULL), this);

	KOTEK_ASSERT(this->m_hwnd,
		"CreateWindowExA failed, error {}", GetLastError());
}

LRESULT CALLBACK ktkWindowWin32::WindowProc_Win32(
	HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	ktkWindowWin32* p_window = nullptr;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCTA* p_create =
			reinterpret_cast<CREATESTRUCTA*>(l_param);
		p_window = static_cast<ktkWindowWin32*>(p_create->lpCreateParams);
		SetWindowLongPtrA(hwnd, GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(p_window));
	}
	else
	{
		p_window = reinterpret_cast<ktkWindowWin32*>(
			GetWindowLongPtrA(hwnd, GWLP_USERDATA));
	}

	if (p_window == nullptr)
	{
		return DefWindowProcA(hwnd, msg, w_param, l_param);
	}

	switch (msg)
	{
	case WM_CLOSE:
	{
		p_window->m_is_need_to_close = true;
		DestroyWindow(hwnd);
		return 0;
	}
	case WM_DESTROY:
	{
		p_window->m_is_need_to_close = true;
		return 0;
	}
	default:
	{
		return DefWindowProcA(hwnd, msg, w_param, l_param);
	}
	}
}

#endif // KOTEK_USE_PLATFORM_WINDOWS

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
