#include "../include/kotek_core_containers_multithreading_thread.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_Containers_MultiThreading_Thread(
	ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [containers][multithreading][thread]");
		p_manager->Get_Splash()->Set_Progress();
	}

	return true;
}

bool SerializeModule_Core_Containers_MultiThreading_Thread(
	ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Containers_MultiThreading_Thread(
	ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Containers_MultiThreading_Thread(
	ktkMainManager* p_manager)
{
	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK