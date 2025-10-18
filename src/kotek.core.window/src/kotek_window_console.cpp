#include "../include/kotek_window_console.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_PLATFORM_WINDOWS

constexpr const char* _kConsoleWindowFontName = "Consolas";
constexpr unsigned int _kConsoleEditBoxLimitTextSize = 128;

constexpr COLORREF _kConsoleBackgroundEncodedColor =
	RGB(123, 104, 238);
constexpr COLORREF _kConsoleEditboxBackgroundEndcodedColor =
	RGB(110, 91, 225);
constexpr COLORREF _kConsoleTextEncodedColor =
	RGB(255, 250, 250);
constexpr int _kConsoleHeight = 384;
constexpr int _kEditHeight = 20;

struct ktkPrivateImpl
{
	bool edit_box_send_command;
	COLORREF color_text;
	COLORREF color_background;
	ktkFileHandleType log_file_reader = kInvalidFileHandleType;
	ktkIFileSystem* p_fs;
	kun_core ktkWindowConsole* p_owner;
	HWND p_handle;
	HWND p_handle_console;
	HWND p_handle_edit_box;
	HFONT p_handle_edit_box_font;
	WNDPROC p_old_edit_box_callback;
	HBRUSH p_handle_brush_console_background;
	kun_ktk size_t file_total_size;
	kun_ktk size_t file_current_offset;
	char p_edit_box_content[_kConsoleEditBoxLimitTextSize];
	char p_view_buffer
		[KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE];
};

LRESULT CALLBACK ConsoleWndProc(
	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
)
{
	ktkPrivateImpl* p_impl = reinterpret_cast<ktkPrivateImpl*>(
		GetWindowLongPtr(hWnd, GWLP_USERDATA)
	);

	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		RECT rc;
		GetClientRect(hWnd, &rc);

		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmMem =
			CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		SelectObject(hdcMem, hbmMem);

		FillRect(
			hdcMem,
			&rc,
			p_impl->p_handle_brush_console_background
		);

		HFONT hOldFont = (HFONT
		)SelectObject(hdcMem, p_impl->p_handle_edit_box_font);

		SetTextColor(hdcMem, p_impl->color_text);
		SetBkMode(hdcMem, TRANSPARENT);

		if (p_impl)
		{
			if (p_impl->p_fs)
			{
				if (p_impl->log_file_reader !=
				    kInvalidFileHandleType)
				{
					RECT textArea = rc;
					textArea.left += 2;
					textArea.top += 2;
					textArea.right -= 2;

					DrawTextA(
						hdcMem,
						p_impl->p_view_buffer,
						-1,
						&textArea,
						DT_WORDBREAK | DT_EXPANDTABS | DT_NOCLIP
					);
				}
			}
		}

		BitBlt(
			hdc,
			0,
			0,
			rc.right,
			rc.bottom,
			hdcMem,
			0,
			0,
			SRCCOPY
		);

		SelectObject(hdcMem, hOldFont);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);

		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetFocus(GetParent(hWnd));
		break;
	}
	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		int scroll = -delta / WHEEL_DELTA * 128;

		if (scroll < 0)
		{
			if (fabs(scroll) > p_impl->file_current_offset)
			{
				p_impl->file_current_offset = 0;
			}
			else
			{
				p_impl->file_current_offset = std::clamp<
					kun_ktk size_t>(
					p_impl->file_current_offset + scroll,
					0,
					std::max<kun_ktk size_t>(
						0,
						p_impl->file_total_size -
							KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE
					)
				);
			}
		}
		else
		{
			auto diff_end = p_impl->file_total_size -
				KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE;
			p_impl->file_current_offset =
				std::clamp<kun_ktk size_t>(
					p_impl->file_current_offset + scroll,
					0,
					std::max<kun_ktk size_t>(0, diff_end)
				);
		}

		if (p_impl)
		{
			if (p_impl->p_fs)
			{
				if (p_impl->log_file_reader !=
				    kInvalidFileHandleType)
				{
					/* todo: re-write using actual filesystem
					and handle of streaming file if
					(p_impl->log_file_reader->eof())
					{
					    p_impl->log_file_reader->clear();
					}

					p_impl->log_file_reader->seekg(
					    p_impl->file_current_offset,
					std::ios_base::beg);
					p_impl->log_file_reader->read(p_impl->p_view_buffer,
					    KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE);
					p_impl
					    ->p_view_buffer[p_impl->log_file_reader->gcount()]
					=
					    '\0';*/
				}
			}
		}

		InvalidateRect(hWnd, NULL, TRUE);

		break;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetTextColor(hdc, _kConsoleTextEncodedColor);
		SetBkColor(
			hdc, _kConsoleEditboxBackgroundEndcodedColor
		);
		return (LRESULT
		)p_impl->p_handle_brush_console_background;
	}
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			KOTEK_ASSERT(
				p_impl->p_owner, "must be initialized!"
			);

			if (p_impl)
			{
				if (p_impl->p_owner)
				{
					p_impl->p_owner->Hide();
				}
			}

			return 0;
		}
		else if (wParam == VK_OEM_3)
		{
			KOTEK_ASSERT(
				p_impl->p_owner, "must be initialized!"
			);

			if (p_impl)
			{
				if (p_impl->p_owner)
				{
					p_impl->p_owner->Hide();
				}
			}

			return 0;
		}

		break;
	}
	case WM_CHAR:
	{
		// prevents beep annoying sound
		if (wParam == VK_RETURN)
		{
			return 0;
		}
		else if (wParam == VK_TAB)
		{
			return 0;
		}
		else if (wParam == VK_ESCAPE)
		{
			return 0;
		}

		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK
EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ktkPrivateImpl* p_impl = reinterpret_cast<ktkPrivateImpl*>(
		GetWindowLongPtr(hWnd, GWLP_USERDATA)
	);

	KOTEK_ASSERT(p_impl, "must be valid!");

	switch (uMsg)
	{
	case WM_KEYDOWN:
	{
		if (wParam == VK_RETURN)
		{
			if (p_impl)
			{
				GetWindowTextA(
					hWnd,
					p_impl->p_edit_box_content,
					_kConsoleEditBoxLimitTextSize
				);

				p_impl->edit_box_send_command = true;
			}

			SetWindowTextA(hWnd, "");

			return 0;
		}
		else if (wParam == VK_TAB)
		{
			SetFocus(GetParent(GetParent(hWnd)));
			return 0;
		}
		else if (wParam == VK_ESCAPE)
		{
			SetFocus(GetParent(hWnd));
			return 0;
		}

		break;
	}
	case WM_CHAR:
	{
		// prevents beep annoying sound
		if (wParam == VK_RETURN)
		{
			return 0;
		}
		else if (wParam == VK_TAB)
		{
			return 0;
		}
		else if (wParam == VK_ESCAPE)
		{
			return 0;
		}

		break;
	}
	}

	WNDPROC p_proc = DefWindowProc;

	if (p_impl)
	{
		if (p_impl->p_old_edit_box_callback)
			p_proc = p_impl->p_old_edit_box_callback;
	}

	return CallWindowProc(p_proc, hWnd, uMsg, wParam, lParam);
}

#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif

ktkWindowConsole::ktkWindowConsole() :
	m_show{}, m_is_issued_hide{}, m_is_issued_show{},
	m_log_file{}, m_p_fs{}, m_p_input{}, m_p_logger{},
	m_p_console{}, m_p_private_impl{}
{
}

ktkWindowConsole::~ktkWindowConsole()
{
	if (this->m_p_private_impl)
	{
		delete this->m_p_private_impl;
		this->m_p_private_impl = nullptr;
	}
}

void ktkWindowConsole::Initialize(
	ktkIWindow* p_window,
	ktkIFileSystem* p_fs,
	ktkIInput* p_input,
	ktkILogger* p_logger,
	ktkIConsole* p_console,
	int imgui_heightmainmenubar,
	const ktk_filesystem_path& full_path_to_log_file
)
{
	KOTEK_ASSERT(p_window, "must be valid");
	KOTEK_ASSERT(p_window->Get_OSData(), "must be valid");
	KOTEK_ASSERT(p_fs, "must be valid");
	KOTEK_ASSERT(p_input, "must be valid!");
	KOTEK_ASSERT(p_logger, "must be valid!");
	KOTEK_ASSERT(p_console, "must be valid!");
	KOTEK_ASSERT(
		!full_path_to_log_file.empty(), "can't be empty!"
	);

	this->m_p_fs = p_fs;
	this->m_p_input = p_input;
	this->m_p_logger = p_logger;
	this->m_p_console = p_console;

	if (p_window)
	{
		this->m_p_private_impl = new ktkPrivateImpl();

		ktkPrivateImpl* p_impl =
			static_cast<ktkPrivateImpl*>(this->m_p_private_impl
		    );

#ifdef KOTEK_USE_PLATFORM_WINDOWS
		ktkWin32OSData* p_main_window_data =
			static_cast<ktkWin32OSData*>(p_window->Get_OSData()
		    );

		KOTEK_ASSERT(
			p_main_window_data->hWnd, "must be initialized!"
		);
		KOTEK_ASSERT(
			p_main_window_data->hInstance,
			"must be initialized!"
		);

		p_impl->p_handle = p_main_window_data->hWnd;
		p_impl->p_view_buffer[0] = '\0';
		p_impl->p_handle_console = NULL;
		p_impl->p_handle_edit_box = NULL;
		p_impl->p_handle_edit_box_font = NULL;
		p_impl->p_handle_brush_console_background = NULL;
		p_impl->color_text = RGB(255, 250, 250);
		p_impl->p_fs = NULL;
		p_impl->p_owner = NULL;
		p_impl->log_file_reader = 0;
		p_impl->file_current_offset = 0;
		p_impl->file_total_size = 0;
		p_impl->edit_box_send_command = false;
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif

		if (p_fs)
		{
			this->m_p_logger->Flush_All();

			p_impl->p_fs = p_fs;
			p_impl->p_owner = this;

			KOTEK_ASSERT(false, "implement");
			/* todo: re-write using actual filesystem and
			   streaming handle to file
			            ktkResourceFileStreamRequest request;

			            request.path_to_file =
			   full_path_to_log_file; request.operation_type =
			   eResourceRequestOperationType::kLoad;
			            request.resource_type =
			   eResourceRequestResourceType::kText;

			            p_impl->log_file_reader =
			   p_manager->Open_FileStream(request);

			            bool is_open =
			   p_impl->log_file_reader->is_open();
			            KOTEK_ASSERT(is_open,
			                "failed to open file, check your OS,
			   your file disk, your file " "and the folder
			   properties (previliges)");

			            if (is_open)
			            {

			                p_impl->log_file_reader->seekg(0,
			   std::ios_base::end);

			                p_impl->file_total_size =
			   p_impl->log_file_reader->tellg();

			                if (p_impl->file_total_size >
			                    KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE)
			                {
			                    p_impl->file_current_offset =
			   std::max<kun_ktk size_t>(0,
			                        p_impl->file_total_size -
			                            KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE);
			                }
			                else
			                {
			                    p_impl->file_current_offset = 0;
			                }



			                p_impl->log_file_reader->seekg(
			                    p_impl->file_current_offset,
			   std::ios_base::beg);


			                p_impl->log_file_reader->read(p_impl->p_view_buffer,
			                    KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE);
			                p_impl->p_view_buffer[p_impl->log_file_reader->gcount()]
			   =
			                    '\0';
			            }*/

			if (p_window)
			{
				if (p_window->Get_OSData())
				{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
					p_impl->p_handle_brush_console_background =
						CreateSolidBrush(
							_kConsoleBackgroundEncodedColor
						);

					KOTEK_ASSERT(
						p_impl
							->p_handle_brush_console_background,
						"failed to create brush! (console "
					    "background)"
					);

					p_impl->p_handle_console = CreateWindowA(
						"STATIC",
						NULL,
						WS_CHILD | WS_BORDER | SS_NOTIFY,
						0,
						0,
						0,
						0,
						p_impl->p_handle,
						NULL,
						p_main_window_data->hInstance,
						NULL
					);

					KOTEK_ASSERT(
						p_impl->p_handle_console,
						"failed to create console subwindow! "
					    "GetLastError={}",
						GetLastError()
					);

					if (!p_impl->p_handle_console)
						return;

					p_impl->p_handle_edit_box = CreateWindowA(
						"EDIT",
						NULL,
						WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
						0,
						0,
						0,
						0,
						p_impl->p_handle_console,
						NULL,
						p_main_window_data->hInstance,
						NULL
					);

					KOTEK_ASSERT(
						p_impl->p_handle_edit_box,
						"failed to create edit box subwindow! "
					    "GetLastError={}",
						GetLastError()
					);

					if (p_impl)
					{
						if (p_impl->p_handle_edit_box)
						{
							SendMessageA(
								p_impl->p_handle_edit_box,
								EM_SETLIMITTEXT,
								_kConsoleEditBoxLimitTextSize -
									1,
								0
							);

							SetWindowLongPtr(
								p_impl->p_handle_edit_box,
								GWLP_USERDATA,
								(LONG_PTR)p_impl
							);

							p_impl->p_old_edit_box_callback =
								(WNDPROC)SetWindowLongPtr(
									p_impl->p_handle_edit_box,
									GWLP_WNDPROC,
									(LONG_PTR)EditWndProc
								);
						}

						if (p_impl->p_handle_console)
						{
							SetWindowLongPtr(
								p_impl->p_handle_console,
								GWLP_USERDATA,
								(LONG_PTR)p_impl
							);
							SetWindowLongPtr(
								p_impl->p_handle_console,
								GWLP_WNDPROC,
								(LONG_PTR)ConsoleWndProc
							);
						}
					}

					p_impl->p_handle_edit_box_font =
						CreateFontA(
							16,
							0,
							0,
							0,
							FW_NORMAL,
							FALSE,
							FALSE,
							FALSE,
							DEFAULT_CHARSET,
							OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS,
							CLEARTYPE_QUALITY,
							FIXED_PITCH | FF_MODERN,
							_kConsoleWindowFontName
						);

					KOTEK_ASSERT(
						p_impl->p_handle_edit_box_font,
						"failedto create font handle, "
					    "specified font for "
						"creation: [{}]",
						_kConsoleWindowFontName
					);

					if (p_impl)
					{
						if (p_impl->p_handle_edit_box &&
						    p_impl->p_handle_edit_box_font)
						{
							SendMessageA(
								p_impl->p_handle_edit_box,
								WM_SETFONT,
								(WPARAM
							    )p_impl->p_handle_edit_box_font,
								TRUE
							);
						}
					}

					RECT rt_main_window;
					if (GetWindowRect(
							p_impl->p_handle, &rt_main_window
						))
					{
						if (p_impl->p_handle_console &&
						    p_impl->p_handle_edit_box)
						{
							int width = rt_main_window.right -
								rt_main_window.left;
							SetWindowPos(
								p_impl->p_handle_console,
								NULL,
								0,
								imgui_heightmainmenubar,
								width,
								_kConsoleHeight,
								SWP_NOZORDER
							);
							SetWindowPos(
								p_impl->p_handle_edit_box,
								NULL,
								0,
								_kConsoleHeight - _kEditHeight,
								width,
								_kEditHeight,
								SWP_NOZORDER
							);
						}
					}

					this->m_show =
						!!!(p_impl->p_handle_console);
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif
				}
			}
		}
	}
}

void ktkWindowConsole::Shutdown()
{
	if (this->m_p_fs)
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		if (this->m_p_private_impl)
		{
			ktkPrivateImpl* p_impl =
				static_cast<ktkPrivateImpl*>(
					this->m_p_private_impl
				);

			if (p_impl)
			{
				BOOL nStatus =
					DestroyWindow(p_impl->p_handle_console);
				KOTEK_ASSERT(
					nStatus,
					"failed to close window! GetLastError()={}",
					GetLastError()
				);

				//	nStatus =
				//DestroyWindow(p_impl->p_handle_edit_box);
				//	KOTEK_ASSERT(nStatus,
				//		"failed to close window!
				//GetLastError()={}", 		GetLastError());
			}
		}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif

		// this->m_p_manager_resource->Close_Loader(this->m_file_reader_id);
/* todo: re-write using actual filesystem
		this->m_p_fs->Close_FileStream(
			this->m_log_file
		);*/
	}
}

void ktkWindowConsole::Update()
{
	if (this->m_p_private_impl)
	{
		if (this->m_p_input)
		{
			if (this->m_p_input->Is_KeyPressed(
					kun_core eInputControllerType::
						kControllerKeyboard,
					kun_core eInputAllKeys::kCK_KEY_GRAVE_ACCENT
				))
			{
				this->m_show = !this->m_show;

				this->Impl_ShowOrHide(this->m_show);
			}
		}

		if (this->m_is_issued_show)
		{
			KOTEK_ASSERT(
				!this->m_is_issued_hide,
				"can't be, it means code logic is broken!"
			);

			this->Impl_ShowOrHide(true);
			this->m_is_issued_show = false;
		}

		if (this->m_is_issued_hide)
		{
			KOTEK_ASSERT(
				!this->m_is_issued_show,
				"can't be, it means code logic is broken!"
			);

			this->Impl_ShowOrHide(false);
			this->m_is_issued_hide = false;
		}

		if (this->m_show)
		{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
			ktkPrivateImpl* p_impl =
				static_cast<ktkPrivateImpl*>(
					this->m_p_private_impl
				);

			if (p_impl->edit_box_send_command)
			{
				if (this->m_p_console)
				{
					this->m_p_console->Push_Command(
						p_impl->p_edit_box_content
					);
				}

				p_impl->edit_box_send_command = false;
			}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif
		}
	}
}

void ktkWindowConsole::Show()
{
	this->m_is_issued_hide = false;
	this->m_show = true;
	this->m_is_issued_show = true;
}

void ktkWindowConsole::Hide()
{
	this->m_is_issued_show = false;
	this->m_show = false;
	this->m_is_issued_hide = true;
}

void ktkWindowConsole::Impl_ShowOrHide(bool show)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ktkPrivateImpl* p_impl =
		static_cast<ktkPrivateImpl*>(this->m_p_private_impl);

	if (show)
	{
		KOTEK_ASSERT(
			p_impl->p_handle_console, "must be initialized!"
		);
		KOTEK_ASSERT(
			p_impl->p_handle_edit_box, "must be initialized!"
		);

		KOTEK_ASSERT(p_impl->p_fs, "must be initialized!");

		if (p_impl->p_fs)
		{
			KOTEK_ASSERT(
				this->m_p_logger, "must be initialized!"
			);

			if (this->m_p_logger)
			{
				this->m_p_logger->Flush_All();
			}

/* todo: re-write using actual filesystem and handle 
			if (p_impl->log_file_reader->eof())
			{
				p_impl->log_file_reader->clear();
			}

			p_impl->log_file_reader->seekg(
				0, std::ios_base::end
			);
			p_impl->file_total_size =
				p_impl->log_file_reader->tellg();
			p_impl->file_current_offset =
				p_impl->file_total_size -
				KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE;

			p_impl->log_file_reader->seekg(
				p_impl->file_current_offset, std::ios_base::beg
			);

			p_impl->log_file_reader->read(
				p_impl->p_view_buffer,
				KOTEK_USE_WINDOW_CONSOLE_STRING_VIEW_SIZE
			);
			p_impl->p_view_buffer[p_impl->log_file_reader
			                          ->gcount()] = '\0';*/
		}

		ShowWindow(p_impl->p_handle_console, SW_SHOW);
		ShowWindow(p_impl->p_handle_edit_box, SW_SHOW);

		SetFocus(p_impl->p_handle_edit_box);

		InvalidateRect(p_impl->p_handle_console, NULL, TRUE);
		InvalidateRect(p_impl->p_handle_edit_box, NULL, TRUE);
	}
	else
	{
		KOTEK_ASSERT(
			p_impl->p_handle_console, "must be initialized!"
		);
		KOTEK_ASSERT(
			p_impl->p_handle_edit_box, "must be initialized!"
		);

		ShowWindow(p_impl->p_handle_console, SW_HIDE);
		ShowWindow(p_impl->p_handle_edit_box, SW_HIDE);
	}
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error not implemented
#else
	#error unknown platform
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK