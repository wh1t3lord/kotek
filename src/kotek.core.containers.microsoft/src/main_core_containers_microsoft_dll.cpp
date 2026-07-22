#include "../include/kotek_core_containers_microsoft.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_Microsoft(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text(
			"[core]: init [containers][microsoft]");
		p_manager->Get_Splash()->Set_Progress();
	}

	KOTEK_INVOKE_MODULE_INIT(InitializeModule_Core_Containers_Microsoft_WRL_ComPtr, p_manager);

	return true;
}

bool SerializeModule_Core_Containers_Microsoft(ktkMainManager* p_manager)
{
	SerializeModule_Core_Containers_Microsoft_WRL_ComPtr(p_manager);

	return true;
}

bool DeserializeModule_Core_Containers_Microsoft(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Containers_Microsoft_WRL_ComPtr(p_manager);

	return true;
}

bool ShutdownModule_Core_Containers_Microsoft(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE_SHUTDOWN(ShutdownModule_Core_Containers_Microsoft_WRL_ComPtr, p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK