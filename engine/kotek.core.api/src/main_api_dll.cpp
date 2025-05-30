#include "../include/kotek_api.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_API(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [api]");
		p_manager->Get_Splash()->Set_Progress();
	}

	return true;
}

bool SerializeModule_Core_API(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_API(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_API(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK