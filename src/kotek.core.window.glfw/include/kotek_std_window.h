#pragma once

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

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// \~english exe-side input bridge for consumers that live in another
/// module (zircon's editor imgui pass in game.ktk): GLFW from vcpkg is a
/// STATIC library, so every module carries its own copy of GLFW's global
/// state and only THIS module's copy (linked into kotek.exe) is ever
/// initialized — a glfwSet*Callback issued from any other module silently
/// no-ops on that module's dead copy (_GLFW_REQUIRE_INIT fails). The
/// window therefore installs its own GLFW callbacks at creation (see
/// Install_EventChainCallbacks) and forwards every event into this chain
/// of plain function pointers; the consumer fills the struct with its
/// handlers (imgui's ImGui_ImplGlfw_*Callback functions match these
/// signatures exactly) and registers it through Set_EventChain. The
/// window module itself never includes consumer headers — plain function
/// pointers only.
struct ktkGlfwEventChain
{
	void (*p_cursor_pos)(GLFWwindow*, double, double){};
	void (*p_mouse_button)(GLFWwindow*, int, int, int){};
	void (*p_scroll)(GLFWwindow*, double, double){};
	void (*p_key)(GLFWwindow*, int, int, int, int){};
	void (*p_char)(GLFWwindow*, unsigned int){};
	void (*p_cursor_enter)(GLFWwindow*, int){};
	void (*p_window_focus)(GLFWwindow*, int){};
};

class ktkWindow : public ktkIWindow
{
public:
	ktkWindow(void);
	ktkWindow(const ktk::ustring& title_name);
	~ktkWindow(void);

	/// <summary>
	/// Be careful with that method, because it shutdowns Engine and
	/// Window!
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	void CloseWindow(void) noexcept;
	void ShowWindow(void) noexcept;
	void HideWindow(void) noexcept override;
	void Set_Fullscreen(bool status) noexcept override;

	void RegisterUserMainManager(
		Core::ktkMainManager* p_manager) noexcept override;

	int GetWidth(void) const noexcept override;
	int GetHeight(void) const noexcept override;

	/// @brief GLFWwindow* returns
	/// @param
	/// @return
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

public:
	/// \~english registers the consumer's event chain (nullptr clears it);
	/// the struct is copied into the window, the caller's instance may die.
	/// A concrete-class hook, NOT part of the ktkIWindow interface (the
	/// interface stays frozen) — same shape as
	/// ktkWindowWin32::Set_WndProcChain (task K17)
	void Set_EventChain(const ktkGlfwEventChain* p_chain) noexcept;

private:
	void ObtainInformationAboutDisplay(void);

	/// \~english installs the trampolines below on the freshly created
	/// window (called once from Initialize, after glfwCreateWindow)
	void Install_EventChainCallbacks(void) noexcept;

	/// \~english GLFW accepts only plain function pointers as callbacks;
	/// these trampolines recover the owning instance (the window user
	/// pointer parks the main manager, see RegisterUserMainManager) and
	/// forward into m_event_chain. They no-op until a chain is registered
	/// and never touch GLFW state of another module.
	static void Callback_CursorPos(
		GLFWwindow* p_window, double x, double y) noexcept;
	static void Callback_MouseButton(GLFWwindow* p_window, int button,
		int action, int mods) noexcept;
	static void Callback_Scroll(
		GLFWwindow* p_window, double x_offset, double y_offset) noexcept;
	static void Callback_Key(GLFWwindow* p_window, int key, int scancode,
		int action, int mods) noexcept;
	static void Callback_Char(
		GLFWwindow* p_window, unsigned int codepoint) noexcept;
	static void Callback_CursorEnter(
		GLFWwindow* p_window, int entered) noexcept;
	static void Callback_WindowFocus(
		GLFWwindow* p_window, int focused) noexcept;

	/// \~english maps a GLFWwindow back to its ktkWindow through the parked
	/// main manager; nullptr when the manager was never registered or the
	/// event's window is not the active one
	static ktkWindow* Get_InstanceFromWindow(GLFWwindow* p_window) noexcept;

private:
	int m_screen_size_width;
	int m_screen_size_height;
	GLFWwindow* m_p_window;
	void* m_p_os_data;
	ktkGlfwEventChain m_event_chain{};
	ktk::unordered_map<ktk::enum_base_t, ktk::cstring> m_titles;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
