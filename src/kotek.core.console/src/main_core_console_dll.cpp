#include "../include/kotek_core_console.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Console(ktkMainManager* p_manager)
{

	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [console]");
		p_manager->Get_Splash()->Set_Progress();
	}

	// the console is a default-implementation service: the module owns the
	// instance and users obtain it through the ktkIConsole slot instead of
	// constructing ktkConsole directly. The user's translation callback is
	// passed later via ktkIConsole::Initialize by the game layer.
	ktkConsole* p_instance = new ktkConsole();
	p_manager->Set_Console(p_instance);

	return true;
}

bool SerializeModule_Core_Console(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Console(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Console(ktkMainManager* p_manager)
{
	ktkIConsole* p_interface = p_manager->Get_Console();

	if (p_interface)
	{
		ktkConsole* p_instance =
			dynamic_cast<ktkConsole*>(p_interface);

		p_interface->Shutdown();

		delete p_instance;
		p_manager->Set_Console(nullptr);
	}

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
