#include "../include/kotek_core_containers_multithreading.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager)
		{
			InitializeModule_Core_Containers_MultiThreading_Atomic(p_manager);
			InitializeModule_Core_Containers_MultiThreading_Mutex(p_manager);
			InitializeModule_Core_Containers_MultiThreading_Semaphore(
				p_manager);
			InitializeModule_Core_Containers_MultiThreading_Shared_Mutex(
				p_manager);
			InitializeModule_Core_Containers_MultiThreading_TBB(p_manager);
			InitializeModule_Core_Containers_MultiThreading_Thread(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Containers_MultiThreading_Atomic(p_manager);
			ShutdownModule_Core_Containers_MultiThreading_Mutex(p_manager);
			ShutdownModule_Core_Containers_MultiThreading_Semaphore(p_manager);
			ShutdownModule_Core_Containers_MultiThreading_Shared_Mutex(
				p_manager);
			ShutdownModule_Core_Containers_MultiThreading_TBB(p_manager);
			ShutdownModule_Core_Containers_MultiThreading_Thread(p_manager);

			return true;
		}

		bool SerializeModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager)
		{
			SerializeModule_Core_Containers_MultiThreading_Atomic(p_manager);
			SerializeModule_Core_Containers_MultiThreading_Mutex(p_manager);
			SerializeModule_Core_Containers_MultiThreading_Semaphore(p_manager);
			SerializeModule_Core_Containers_MultiThreading_Shared_Mutex(
				p_manager);
			SerializeModule_Core_Containers_MultiThreading_TBB(p_manager);
			SerializeModule_Core_Containers_MultiThreading_Thread(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Containers_MultiThreading_Atomic(p_manager);
			DeserializeModule_Core_Containers_MultiThreading_Mutex(p_manager);
			DeserializeModule_Core_Containers_MultiThreading_Semaphore(
				p_manager);
			DeserializeModule_Core_Containers_MultiThreading_Shared_Mutex(
				p_manager);
			DeserializeModule_Core_Containers_MultiThreading_TBB(p_manager);
			DeserializeModule_Core_Containers_MultiThreading_Thread(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek