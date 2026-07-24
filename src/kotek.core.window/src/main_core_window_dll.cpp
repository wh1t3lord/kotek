#include "../include/kotek_core_window.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>


KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Window(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [window]");
		p_manager->Get_Splash()->Set_Progress();
	}

	// the console window is a default-implementation service: the module
	// owns the instance and users obtain it through the ktkIWindowConsole
	// slot instead of constructing ktkWindowConsole directly. The actual
	// Initialize(...) happens later in the game layer once the window,
	// filesystem, input, logger and console services exist.
	ktkWindowConsole* p_console_instance = new ktkWindowConsole();
	p_manager->Set_WindowConsole(p_console_instance);

	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Window_GLFW, p_manager);

	return true;
}

bool SerializeModule_Core_Window(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(SERIALIZE, CORE, SerializeModule_Core_Window_GLFW, p_manager);

	return true;
}

bool DeserializeModule_Core_Window(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(DESERIALIZE, CORE, DeserializeModule_Core_Window_GLFW, p_manager);

	return true;
}

bool ShutdownModule_Core_Window(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Window_GLFW, p_manager);

	ktkIWindowConsole* p_console_interface =
		p_manager->Get_WindowConsole();

	if (p_console_interface)
	{
		ktkWindowConsole* p_console_instance =
			dynamic_cast<ktkWindowConsole*>(p_console_interface);

		delete p_console_instance;
		p_manager->Set_WindowConsole(nullptr);
	}

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK