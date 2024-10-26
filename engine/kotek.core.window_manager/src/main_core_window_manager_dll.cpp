#include "../include/kotek_core_window_manager.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_Window_Manager(ktkMainManager* p_manager)
{
	p_manager->Set_WindowManager(new ktkWindowManager());
	InitializeModule_Core_Window(p_manager);

	p_manager->Get_WindowManager()->Initialize();

	return true;
}

bool SerializeModule_Core_Window_Manager(ktkMainManager* p_manager)
{
	SerializeModule_Core_Window(p_manager);

	return true;
}

bool DeserializeModule_Core_Window_Manager(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Window(p_manager);

	return true;
}

bool ShutdownModule_Core_Window_Manager(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Window(p_manager);

	ktkWindowManager* p_window_manager =
		dynamic_cast<ktkWindowManager*>(p_manager->Get_WindowManager());

	KOTEK_ASSERT(p_window_manager, "bad cast to ktkWindowManager*");

	p_window_manager->Shutdown();
	delete p_window_manager;

	p_manager->Set_WindowManager(nullptr);

	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
