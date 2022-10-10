#include "../include/kotek_core_main_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_Main_Manager(ktkMainManager* p_main_manager)
{
	p_main_manager->Initialize();
	return true;
}

bool ShutdownModule_Core_Main_Manager(ktkMainManager* p_main_manager)
{
	p_main_manager->Shutdown();
	return true;
}

bool SerializeModule_Core_Main_Manager(ktkMainManager* p_main_manager)
{
	return true;
}

bool DeserializeModule_Core_Main_Manager(ktkMainManager* p_main_manager)
{
	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK