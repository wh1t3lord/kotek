#include "../include/kotek_core_window.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>


KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Window(ktkMainManager* p_manager)
{
	InitializeModule_Core_Window_GLFW(p_manager);

	if (p_manager)
	{
		ktkIWindowManager* p_manager_window = p_manager->Get_WindowManager();
		if (p_manager_window)
		{
			p_manager_window->Set_ActiveWindowSplash(
				new ktkWindowSplash());
		}
	}

	return true;
}

bool SerializeModule_Core_Window(ktkMainManager* p_manager)
{
	SerializeModule_Core_Window_GLFW(p_manager);

	return true;
}

bool DeserializeModule_Core_Window(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Window_GLFW(p_manager);

	return true;
}

bool ShutdownModule_Core_Window(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Window_GLFW(p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK