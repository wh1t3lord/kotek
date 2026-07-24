#include "../include/kotek_core_defines.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [defines]");
		p_manager->Get_Splash()->Set_Progress();
	}

	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Defines_Static, p_manager);
	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Defines_Dependent, p_manager);

	return true;
}

bool ShutdownModule_Core_Defines(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Defines_Static, p_manager);
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Defines_Dependent, p_manager);

	return true;
}

bool SerializeModule_Core_Defines(ktkMainManager* p_manager)
{
	SerializeModule_Core_Defines_Static(p_manager);
	SerializeModule_Core_Defines_Dependent(p_manager);

	return true;
}

bool DeserializeModule_Core_Defines(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Defines_Static(p_manager);
	DeserializeModule_Core_Defines_Dependent(p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK