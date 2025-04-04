#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkIWindow;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// @brief GUI implemenetation based on OS's GUI
class ktkWindowConsole
{
public:
	ktkWindowConsole();
	~ktkWindowConsole();

	/// @brief window in order to obtain parent's window handle, resource
	/// manager for creating file for reading (log file)
	/// @param p_window
	/// @param p_manager
	void Initialize(ktkIWindow* p_window, ktkIResourceManager* p_manager,
		ktkIInput* p_input, ktkILogger* p_logger, ktkIConsole* p_console,
		int imgui_mainmenubar_height,
		const ktk_filesystem_path& full_path_to_log_file);
	void Shutdown();
	void Update();

	void Show();
	void Hide();

private:
	void Impl_ShowOrHide(bool show);

private:
	bool m_show;
	bool m_is_issued_hide;
	bool m_is_issued_show;
	kun_ktk cfstream* m_p_log_reader;
	ktkIResourceManager* m_p_manager_resource;
	ktkIInput* m_p_input;
	ktkILogger* m_p_logger;
	ktkIConsole* m_p_console;
	void* m_p_private_impl;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK