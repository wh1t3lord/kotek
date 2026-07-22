#include "../include/kotek_core_os.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_OS(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [os]");
		p_manager->Get_Splash()->Set_Progress();
	}

#ifdef KOTEK_PLATFORM_WINDOWS
	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_OS_Win32, p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_OS_Linux, p_manager);
#else
    #error Unknown platform
#endif

	return true;
}
bool SerializeModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	KOTEK_INVOKE_MODULE(SERIALIZE, CORE, SerializeModule_Core_OS_Win32, p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	KOTEK_INVOKE_MODULE(SERIALIZE, CORE, SerializeModule_Core_OS_Linux, p_manager);
#else
    #error Unknown platform
#endif
	return true;
}

bool DeserializeModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	KOTEK_INVOKE_MODULE(DESERIALIZE, CORE, DeserializeModule_Core_OS_Win32, p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	KOTEK_INVOKE_MODULE(DESERIALIZE, CORE, DeserializeModule_Core_OS_Linux, p_manager);
#else
    #error Unknown platform
#endif

	return true;
}

bool ShutdownModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_OS_Win32, p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_OS_Linux, p_manager);
#else
    #error Unknown platform
#endif

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
