#pragma once

/// \file kotek_std_window_win32.h
/// \~english own no-dependency Win32 window backend (task K17): the same
/// ktkIWindow contract as the GLFW sibling, over raw Win32
/// (CreateWindowEx/WndProc). Phase 1 covers window lifecycle + presentation
/// (bgfx/NRI consume the HWND through ktkWin32OSData exactly like they do
/// from the GLFW path); input stays on the GLFW backend until the
/// eInputPlatformBackend win32 sibling lands (phase 2, registered in K17).

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.api/include/kotek_api.h>

#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

enum class eEngineFeature : kun_ktk uint32_t;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkWindowWin32 : public ktkIWindow
{
public:
	ktkWindowWin32(void);
	ktkWindowWin32(const ktk::ustring& title_name);
	~ktkWindowWin32(void);

	/// <summary>
	/// Be careful with that method, because it shutdowns Engine and
	/// Window!
	/// </summary>
	void CloseWindow(void) noexcept;
	void ShowWindow(void) noexcept;
	void HideWindow(void) noexcept override;
	void Set_Fullscreen(bool status) noexcept override;

	void RegisterUserMainManager(
		Core::ktkMainManager* p_manager) noexcept override;

	int GetWidth(void) const noexcept override;
	int GetHeight(void) const noexcept override;

	/// @brief HWND returns
	void* GetHandle(void) const noexcept override;

	void* Get_OSData(void) noexcept override;

	void Initialize(kun_core eEngineSupportedRenderer version,
		kun_core eEngineFeatureRendererVendor vendor) override;

	void Shutdown(void) override;

	void MakeContextCurrent(void) noexcept override;
	void PollEvents(void) override;
	bool Is_NeedToClose(void) override;

	void SetStringToTitle(ktk::enum_base_t id,
		const char* p_utf8_or_char_string) noexcept override;
	void RemoveStringFromTitle(ktk::enum_base_t id) noexcept override;
	ktk::cstring GetTitle(void) const noexcept override;
	void Set_InputType(ktk::enum_base_t type) noexcept override;

private:
	void ObtainInformationAboutDisplay(void);
	void Create_OsWindow(const char* p_title) noexcept;

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	static LRESULT CALLBACK WindowProc_Win32(
		HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

	/// \~english task K17 phase 2: forwards a keyboard/mouse event into the
	/// input system (WPARAM/LPARAM come from the proc; controller_type
	/// picks the translation path inside kotek.core.input)
	void Forward_EventToInput(UINT msg, WPARAM w_param, LPARAM l_param,
		bool is_mouse) noexcept;

	/// \~english current glfw-shaped modifier bits from the live key state
	/// (SHIFT=1, CONTROL=2, ALT=4, SUPER=8)
	int Get_CurrentMods(void) const noexcept;
#endif

public:
	/// \~english task K17 phase 2: a second handler invoked from the proc
	/// AFTER the window's own handling — kotek.ui.imgui installs
	/// ImGui_ImplWin32_WndProcHandler here at init (a concrete-class hook,
	/// NOT part of the ktkIWindow interface: the interface stays frozen)
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	using wndproc_chain_t = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);
	void Set_WndProcChain(wndproc_chain_t p_chain) noexcept
	{
		this->m_p_wndproc_chain = p_chain;
	}
#endif

private:
	int m_screen_size_width;
	int m_screen_size_height;
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	HWND m_hwnd;
#endif
	void* m_p_os_data;
	// GWLP_USERDATA carries `this` for the proc (the GLFW path parks the
	// manager in the window user pointer instead); the manager itself lives
	// here — nothing in the proc needs it in phase 1
	kun_core ktkMainManager* m_p_main_manager;
	bool m_is_need_to_close;
	bool m_is_fullscreen;
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	/// \~english task Z18/K24 batch 1: was a function-local static in
	/// Set_Fullscreen, silently shared by ALL window instances (a latent
	/// multi-window bug) — the windowed-mode placement is per-window state
	WINDOWPLACEMENT m_saved_placement{};
	/// \~english task Z18/K24 batch 1: was the file-scope
	/// g_window_class_registered. RegisterClassEx is process-global, so this
	/// member only records that THIS instance already attempted registration;
	/// another instance's attempt fails with ERROR_CLASS_ALREADY_EXISTS,
	/// which Create_OsWindow treats as success. Single-window behavior is
	/// unchanged: the class is registered once and never unregistered (the
	/// OS reclaims it at process exit)
	bool m_is_window_class_registered{false};
	wndproc_chain_t m_p_wndproc_chain{};
#endif
	ktk::unordered_map<ktk::enum_base_t, ktk::cstring> m_titles;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
