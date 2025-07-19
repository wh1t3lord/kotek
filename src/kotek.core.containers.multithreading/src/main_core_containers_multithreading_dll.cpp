#include "../include/kotek_core_containers_multithreading.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_MultiThreading(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [containers][multithreading]");
		p_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_Core_Containers_MultiThreading_Atomic(p_manager);
	InitializeModule_Core_Containers_MultiThreading_Mutex(p_manager);
	InitializeModule_Core_Containers_MultiThreading_Semaphore(p_manager);
	InitializeModule_Core_Containers_MultiThreading_Shared_Mutex(p_manager);
	InitializeModule_Core_Containers_MultiThreading_TBB(p_manager);
	InitializeModule_Core_Containers_MultiThreading_Thread(p_manager);
	InitializeModule_Core_Containers_MultiThreading_Queue(p_manager);
	InitializeModule_Core_Containers_MultiThreading_Condition_Variable(
		p_manager);

	return true;
}

bool ShutdownModule_Core_Containers_MultiThreading(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Containers_MultiThreading_Atomic(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_Mutex(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_Semaphore(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_Shared_Mutex(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_TBB(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_Thread(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_Queue(p_manager);
	ShutdownModule_Core_Containers_MultiThreading_Condition_Variable(p_manager);

	return true;
}

bool SerializeModule_Core_Containers_MultiThreading(ktkMainManager* p_manager)
{
	SerializeModule_Core_Containers_MultiThreading_Atomic(p_manager);
	SerializeModule_Core_Containers_MultiThreading_Mutex(p_manager);
	SerializeModule_Core_Containers_MultiThreading_Semaphore(p_manager);
	SerializeModule_Core_Containers_MultiThreading_Shared_Mutex(p_manager);
	SerializeModule_Core_Containers_MultiThreading_TBB(p_manager);
	SerializeModule_Core_Containers_MultiThreading_Thread(p_manager);
	SerializeModule_Core_Containers_MultiThreading_Queue(p_manager);
	SerializeModule_Core_Containers_MultiThreading_Condition_Variable(
		p_manager);

	return true;
}

bool DeserializeModule_Core_Containers_MultiThreading(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Containers_MultiThreading_Atomic(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_Mutex(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_Semaphore(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_Shared_Mutex(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_TBB(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_Thread(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_Queue(p_manager);
	DeserializeModule_Core_Containers_MultiThreading_Condition_Variable(
		p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK