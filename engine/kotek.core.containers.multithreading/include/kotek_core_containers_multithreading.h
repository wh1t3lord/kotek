#pragma once

#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.semaphore/include/kotek_core_containers_multithreading_semaphore.h>
#include <kotek.core.containers.multithreading.shared_mutex/include/kotek_core_containers_multithreading_shared_mutex.h>
#include <kotek.core.containers.multithreading.tbb/include/kotek_core_containers_multithreading_tbb.h>
#include <kotek.core.containers.multithreading.thread/include/kotek_core_containers_multithreading_thread.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers_MultiThreading(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek