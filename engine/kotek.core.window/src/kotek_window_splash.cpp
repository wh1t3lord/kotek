#include "../include/kotek_window_splash.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#include <CommCtrl.h>
	#include <Uxtheme.h>

	#pragma comment(lib, "comctl32.lib")
	#pragma comment(lib, "UxTheme.lib")
	#pragma comment(lib, "Shcore.lib")

struct ktkPrivateImpl
{
	HWND m_p_hwnd = NULL;
	HWND m_p_progressbar = NULL;

	bool m_is_show = false;
	bool m_is_failed_to_initialize = false;
};

LRESULT CALLBACK NativeWindowCallbackImplementation(
	HWND p_hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		break;
	}
	case WM_PAINT:
	{
		ktkWindowSplash* p_window = reinterpret_cast<ktkWindowSplash*>(
			GetWindowLongPtr(p_hwnd, GWLP_USERDATA));

		if (!p_window)
			break;

		int r = p_window->Get_TextColor()[0];
		int g = p_window->Get_TextColor()[1];
		int b = p_window->Get_TextColor()[2];

		RECT window_size;
		GetClientRect(p_hwnd, &window_size);

		int width = window_size.right;
		int height = window_size.bottom - (GetSystemMetrics(SM_CYVSCROLL) * 2);

		PAINTSTRUCT ps;
		HDC p_hdc = BeginPaint(p_hwnd, &ps);

		SetTextColor(p_hdc, RGB(r, g, b));
		SetBkMode(p_hdc, TRANSPARENT);
		TextOutA(p_hdc, 0, height, p_window->Get_Label(),
			strlen(p_window->Get_Label()));

		EndPaint(p_hwnd, &ps);
		ReleaseDC(p_hwnd, p_hdc);

		break;
	}
	case WM_ERASEBKGND:
	{
		HDC hdc = (HDC)(wparam);
		RECT rc;
		GetClientRect(p_hwnd, &rc);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(hdc, &rc, brush);
		DeleteObject(brush);

		break;
	}
	}

	return DefWindowProcA(p_hwnd, msg, wparam, lparam);
}
#else
	#error provide implementation
#endif

ktkWindowSplash::ktkWindowSplash() :
	m_is_show{}, m_width{}, m_height{}, m_max_progress{}, m_current_progress{},
	m_p_private_impl{}, m_text_width{}, m_text_height{},
	m_p_current_color_text{255, 255, 255}, m_p_label{}
{
	this->m_p_private_impl = new ktkPrivateImpl();
}

ktkWindowSplash::~ktkWindowSplash()
{
	if (this->m_p_private_impl)
	{
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);
		delete p_impl;
		this->m_p_private_impl = nullptr;
	}
}

int ktkWindowSplash::Get_Width(void) const noexcept
{
	return this->m_width;
}

int ktkWindowSplash::Get_Height(void) const noexcept
{
	return this->m_height;
}

void ktkWindowSplash::Show(void) noexcept
{
	m_is_show = true;

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_p_private_impl)
	{
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

		if (p_impl)
		{
			ShowWindow(p_impl->m_p_hwnd, SW_NORMAL);
		}
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Hide(void) noexcept
{
	m_is_show = false;

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_p_private_impl)
	{
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

		if (p_impl)
		{
			ShowWindow(p_impl->m_p_hwnd, SW_HIDE);
		}
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Create(int width, int height,
	unsigned char* p_raw_image_data, float* p_max_progress) noexcept
{
	this->m_width = width;
	this->m_height = height;

	if (this->m_width == -1 || this->m_height == -1)
	{
		this->Get_DisplaySize(&this->m_width, &this->m_height);
		this->m_width /= 2;
		this->m_height /= 2;
	}

	if (p_max_progress)
	{
		this->m_max_progress = *p_max_progress;
	}

	if (this->m_width > 0 && this->m_height > 0)
	{
		this->Create_Window(this->m_width, this->m_height);
	}
}

void ktkWindowSplash::Set_Text(
	const char* p_string, int* p_color_rgb_array) noexcept
{
	if (p_string)
	{
		memset(this->m_p_label, 0, sizeof(this->m_p_label));

		kun_kotek kun_ktk memory::memcpy(
			this->m_p_label, p_string, strlen(p_string));
	}

	if (p_color_rgb_array)
	{
		kun_kotek kun_ktk memory::memcpy(
			this->m_p_current_color_text, p_color_rgb_array, sizeof(int) * 3);
	}

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	if (p_impl)
	{
		RECT client_size;
		GetClientRect(p_impl->m_p_hwnd, &client_size);

		client_size.bottom -= GetSystemMetrics(SM_CYVSCROLL);

		InvalidateRect(p_impl->m_p_hwnd, &client_size, TRUE);
		UpdateWindow(p_impl->m_p_hwnd);
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Set_Progress(float progress) noexcept
{
	if (progress < 0.0f)
	{
		progress = this->m_max_progress;
	}

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	if (p_impl)
	{
		SendMessage(
			p_impl->m_p_progressbar, PBM_SETPOS, (UINT)this->m_max_progress, 0);
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Set_Progress(void) noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	if (p_impl)
	{
		if (this->m_current_progress < this->m_max_progress)
		{
			SendMessage(p_impl->m_p_progressbar, PBM_STEPIT, 0, 0);
			this->m_current_progress += 1.0f;

			char buffer[16]{};
			sprintf_s(buffer, "%f\n", this->m_current_progress);
			OutputDebugStringA(buffer);
		}
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Update() noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	MSG msg;

	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
#else
	#error provide implementation
#endif
}

bool ktkWindowSplash::Is_Initialized(void) const noexcept
{
	if (this->m_p_private_impl)
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

		if (p_impl)
		{
			return (p_impl->m_p_hwnd && p_impl->m_p_progressbar) || (p_impl->m_is_failed_to_initialize);
		}
#else
#endif
	}

	return true;
}

const int* ktkWindowSplash::Get_TextColor(void) const noexcept
{
	return this->m_p_current_color_text;
}

float ktkWindowSplash::Get_TextOffsetWidth(void) const noexcept
{
	return this->m_text_width;
}

float ktkWindowSplash::Get_TextOffsetHeight(void) const noexcept
{
	return this->m_text_height;
}

const char* ktkWindowSplash::Get_Label(void) const noexcept
{
	return this->m_p_label;
}

bool ktkWindowSplash::Is_Show() const noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	if (p_impl)
	{
		return p_impl->m_is_show || p_impl->m_is_failed_to_initialize;
	}
#else
	#error provide implementation
#endif

	return true;
}

void* ktkWindowSplash::Get_Impl() const noexcept
{
	return this->m_p_private_impl;
}

void ktkWindowSplash::Create_Window(int width, int height)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	this->Create_Windows(width, height);
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Create_Windows(int width, int height)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	double windows_version = -1.0;
	OSVERSIONINFOEXW osInfo;
	{
		typedef void(WINAPI * RtlGetVersion_FUNC)(OSVERSIONINFOEXW*);

		RtlGetVersion_FUNC RtlGetVersion;
		HMODULE p_dll = GetModuleHandleA("ntdll");

		*(FARPROC*)&RtlGetVersion = GetProcAddress(p_dll, "RtlGetVersion");

		if (NULL != RtlGetVersion)
		{
			osInfo.dwOSVersionInfoSize = sizeof(osInfo);
			RtlGetVersion(&osInfo);
			windows_version = (double)osInfo.dwMajorVersion;
		}
	}

	if (windows_version < 0.0)
	{
		this->Failed();
		return;
	}

	// Windows 10 1703 or Greater
	if (osInfo.dwMajorVersion >= 10 && osInfo.dwBuildNumber >= 15063)
	{
		SetProcessDpiAwarenessContext(
			DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	}
	// Windows 8.1 or Greater
	else if (osInfo.dwMajorVersion >= 6 && osInfo.dwBuildNumber >= 9600 &&
		osInfo.dwBuildNumber <= 14393)
	{
		SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	}
	// Windows Vista or Greater
	else if (osInfo.dwMajorVersion >= 6 && osInfo.dwBuildNumber >= 6000 &&
		osInfo.dwBuildNumber <= 9200)
	{
		SetProcessDPIAware();
	}

	const char p_class_name[] = "Splash window";

	WNDCLASSA wc = {};

	wc.lpfnWndProc = NativeWindowCallbackImplementation;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.lpszClassName = p_class_name;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassA(&wc);

	int x, y;
	this->Center_Window(width, height, x, y);

	RECT size_window = {x, y, width, height};
	AdjustWindowRectEx(&size_window, WS_POPUP | WS_VISIBLE, FALSE,
		WS_EX_TOPMOST | WS_EX_TOOLWINDOW);

	HWND p_hwnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
		p_class_name, NULL, WS_POPUP | WS_VISIBLE, x, y, width, height, NULL,
		NULL, GetModuleHandleA(NULL), NULL);
	if (!p_hwnd)
	{
		this->Failed();
		return;
	}

	SetWindowLongPtrA(p_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	KOTEK_ASSERT(p_hwnd, "failed to create splash window!");
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);
	if (p_hwnd && p_impl)
	{
		p_impl->m_p_hwnd = p_hwnd;

		if (this->m_max_progress > 0.0f)
		{
			InitCommonControls();

			RECT window_size;
			GetClientRect(p_hwnd, &window_size);

			int width = window_size.right;
			int height = window_size.bottom;

			int progress_bar_default_size_y = GetSystemMetrics(SM_CYVSCROLL);

			HWND p_hwnd_progress_bar = CreateWindowEx(0, PROGRESS_CLASS,
				(LPTSTR)NULL, WS_CHILD | WS_VISIBLE, window_size.left,
				window_size.bottom - progress_bar_default_size_y,
				window_size.right, progress_bar_default_size_y, p_hwnd, NULL,
				GetModuleHandleA(NULL), NULL);

			if (!p_hwnd_progress_bar)
			{
				this->Failed();
				return;
			}

			SetWindowTheme(p_hwnd_progress_bar, TEXT(""), TEXT(""));
			SendMessage(
				p_hwnd_progress_bar, PBM_SETBARCOLOR, 0, RGB(225, 15, 15));
			SendMessage(p_hwnd_progress_bar, PBM_SETBKCOLOR, 0, RGB(0, 0, 0));
			SendMessage(p_hwnd_progress_bar, PBM_SETSTEP, 1, 0);
			long style = GetWindowLong(p_hwnd_progress_bar, GWL_EXSTYLE);
			style &= ~WS_EX_STATICEDGE;
			SetWindowLong(p_hwnd_progress_bar, GWL_EXSTYLE, style);
			UpdateWindow(p_hwnd_progress_bar);

			SendMessage(p_hwnd_progress_bar, PBM_SETRANGE, 0,
				MAKELONG(0, int(this->m_max_progress)));

			p_impl->m_p_progressbar = p_hwnd_progress_bar;
		}

		p_impl->m_is_show = true;
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Create_Linux() {}

void ktkWindowSplash::Create_MacOS() {}

void ktkWindowSplash::Create_Android() {}

void ktkWindowSplash::Center_Window(int width, int height, int& x, int& y)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (this->m_p_private_impl)
	{
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

		if (p_impl)
		{
			int display_width{-1};
			int display_height{-1};

			this->Get_DisplaySize(&display_width, &display_height);

			//	SetWindowPos(p_impl->m_p_hwnd, HWND_TOPMOST,
			//		display_width / 2 - width / 2,
			//		display_height / 2 - height / 2, width, height,
			// SWP_HIDEWINDOW);
			x = display_width / 2 - width / 2;
			y = display_height / 2 - height / 2;
		}
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Get_DisplaySize(int* p_width, int* p_height)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (p_width && p_height)
	{
		DEVMODEA info;
		BOOL status = EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &info);

		if (!status)
		{
			*p_width = -1;
			*p_height = -1;
			return;
		}

		*p_width = info.dmPelsWidth;
		*p_height = info.dmPelsHeight;
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Failed(){
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	if (p_impl)
	{
		p_impl->m_is_failed_to_initialize = true;
	}
#else
	#error provide implementation
#endif
}

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
