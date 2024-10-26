#include "../include/kotek_core_window_glfw.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
	if (p_manager)
	{
		ktkIWindowManager* p_manager_window = p_manager->Get_WindowManager();
		if (p_manager_window)
		{
			p_manager_window->Set_ActiveWindow(new ktkWindow());
		}
	}
#endif

	return true;
}

bool ShutdownModule_Core_Window_GLFW(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
#endif

	return true;
}

bool SerializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW

#endif
	return true;
}

bool DeserializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW

#endif
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
