#include "../include/kotek_window_splash.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_PLATFORM_WINDOWS

struct ktkPrivateImpl
{
	HWND m_p_hwnd = NULL;
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
	case WM_ERASEBKGND:
	{
		HDC hdc = (HDC)(wparam);
		RECT rc;
		GetClientRect(p_hwnd, &rc);
		HBRUSH brush = CreateSolidBrush(RGB(15, 25, 50));  
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
	m_p_private_impl{}
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

	if (this->m_width > 0 && this->m_height > 0)
	{
		this->Create_Window(this->m_width, this->m_height);
	}
}

void ktkWindowSplash::Add_Text(float normalized_width, float normalized_height,
	const char* p_string) noexcept
{
}

void ktkWindowSplash::Set_Progress(
	float progress, const char* p_string) noexcept
{
}

void ktkWindowSplash::Update() noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
#else
	#error provide implementation
#endif
}

bool ktkWindowSplash::Is_Initialized(void) const noexcept
{
	if (this->m_p_private_impl)
	{
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

		if (p_impl)
		{
			return p_impl->m_p_hwnd;
		}
	}

	return false;
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
	const char p_class_name[] = "Splash window";

	WNDCLASSA wc = {};

	wc.lpfnWndProc = NativeWindowCallbackImplementation;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.lpszClassName = p_class_name;

	RegisterClassA(&wc);

	HWND p_hwnd = CreateWindowExA(0, p_class_name, "",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandleA(NULL), NULL);

	KOTEK_ASSERT(p_hwnd, "failed to create splash window!");

	if (p_hwnd)
	{
		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

		if (p_impl)
		{
			p_impl->m_p_hwnd = p_hwnd;
		}

		ShowWindow(p_hwnd, SW_SHOWNORMAL);

		LONG lStyle = GetWindowLong(p_hwnd, GWL_STYLE);
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX |
			WS_MAXIMIZEBOX | WS_SYSMENU);
		SetWindowLong(p_hwnd, GWL_STYLE, lStyle);

		LONG lExStyle = GetWindowLong(p_hwnd, GWL_EXSTYLE);
		lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE |
			WS_EX_STATICEDGE | WS_EX_APPWINDOW);
		lExStyle |= WS_EX_TOOLWINDOW;
		SetWindowLong(p_hwnd, GWL_EXSTYLE, lExStyle);

		this->Center_Window(width, height);
		SetWindowPos(p_hwnd, HWND_TOPMOST, 0, 0, 0, 0,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
	}
#else
	#error provide implementation
#endif
}

void ktkWindowSplash::Create_Linux() {}

void ktkWindowSplash::Create_MacOS() {}

void ktkWindowSplash::Create_Android() {}

void ktkWindowSplash::Center_Window(int width, int height)
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

			SetWindowPos(p_impl->m_p_hwnd, NULL, display_width / 2 - width / 2,
				display_height / 2 - height / 2, width, height, SWP_SHOWWINDOW);
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

KOTEK_END_NAMESPACE_CORE KOTEK_END_NAMESPACE_KOTEK
