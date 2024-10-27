#include "../include/kotek_core_constants.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>


KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Constants(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [constants]");
		p_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_Core_Constants_Math(p_manager);
	InitializeModule_Core_Constants_Window(p_manager);
	InitializeModule_Core_Constants_ECS(p_manager);
	InitializeModule_Core_Constants_String(p_manager);

	return true;
}

bool ShutdownModule_Core_Constants(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Constants_Math(p_manager);
	ShutdownModule_Core_Constants_Window(p_manager);
	ShutdownModule_Core_Constants_ECS(p_manager);
	ShutdownModule_Core_Constants_String(p_manager);

	return true;
}

bool SerializeModule_Core_Constants(ktkMainManager* p_manager)
{
	SerializeModule_Core_Constants_Math(p_manager);
	SerializeModule_Core_Constants_Window(p_manager);
	SerializeModule_Core_Constants_ECS(p_manager);
	SerializeModule_Core_Constants_String(p_manager);

	return true;
}

bool DeserializeModule_Core_Constants(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Constants_Math(p_manager);
	DeserializeModule_Core_Constants_Window(p_manager);
	DeserializeModule_Core_Constants_ECS(p_manager);
	DeserializeModule_Core_Constants_String(p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK