#include "../include/kotek_core_defines_static_os.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines_Static_OS(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [defines][static][os]");
		p_manager->Get_Splash()->Set_Progress();
	}

#ifdef KOTEK_USE_PLATFORM_WINDOWS
    InitializeModule_Core_Defines_Static_OS_Windows(p_manager);
#elif defined(KOTEK_USE_PLATFORM_LINUX)
    InitializeModule_Core_Defines_Static_OS_Linux(p_manager);
#endif

	return true;
}

bool ShutdownModule_Core_Defines_Static_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	ShutdownModule_Core_Defines_Static_OS_Windows(p_manager);
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	ShutdownModule_Core_Defines_Static_OS_Linux(p_manager);
#endif

	return true;
}

bool SerializeModule_Core_Defines_Static_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	SerializeModule_Core_Defines_Static_OS_Windows(p_manager);
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	SerializeModule_Core_Defines_Static_OS_Linux(p_manager);
#endif

	return true;
}

bool DeserializeModule_Core_Defines_Static_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	DeserializeModule_Core_Defines_Static_OS_Windows(p_manager);
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	DeserializeModule_Core_Defines_Static_OS_Linux(p_manager);
#endif

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
