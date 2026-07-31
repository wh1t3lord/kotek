#include "../include/kotek_core_window_win32.h"
#include "../include/kotek_std_window_win32.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Window_WIN32(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [window][win32]");
		p_manager->Get_Splash()->Set_Progress();
	}

#ifdef KOTEK_USE_WINDOW_LIBRARY_WIN32
	if (p_manager)
	{
		ktkIWindowManager* p_manager_window = p_manager->Get_WindowManager();
		if (p_manager_window)
		{
			p_manager_window->Set_ActiveWindow(new ktkWindowWin32());
		}
	}
#endif

	return true;
}

bool ShutdownModule_Core_Window_WIN32(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_WIN32
#endif

	return true;
}

bool SerializeModule_Core_Window_WIN32(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_WIN32

#endif
	return true;
}

bool DeserializeModule_Core_Window_WIN32(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_WINDOW_LIBRARY_WIN32

#endif
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
