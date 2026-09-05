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

/// \~english exe-side input bridge (task K26): GLFW from vcpkg is a STATIC
/// library, so every module in the process owns a private copy of GLFW's
/// global state and only THIS module's copy (kotek.exe side) is initialized
/// and owns the real window — any glfwSet*Callback issued from another
/// module (game.ktk) writes into that module's never-initialized copy and
/// is silently dead (the same disease as the imgui backend had). The
/// window therefore installs its own input callbacks at Initialize and
/// forwards events into the main manager's input manager
/// (Get_Input()->Update_Controller / Set_ControllerData); the manager
/// pointer arrives at construction from the module entry and reaches the
/// C callbacks through glfwSetWindowUserPointer. ImGui chaining is
/// untouched: the imgui backend installs ITS callbacks later
/// (ImGui_InitForOther with install_callbacks=true) and chains into these
/// as PrevUserCallback*.
class ktkWindow : public ktkIWindow
{
public:
	ktkWindow(ktkMainManager* p_manager);
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

private:
	void ObtainInformationAboutDisplay(void);

private:
	int m_screen_size_width;
	int m_screen_size_height;
	GLFWwindow* m_p_window;
	void* m_p_os_data;
	ktkMainManager* m_p_main_manager;
	ktk::unordered_map<ktk::enum_base_t, ktk::cstring> m_titles;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
