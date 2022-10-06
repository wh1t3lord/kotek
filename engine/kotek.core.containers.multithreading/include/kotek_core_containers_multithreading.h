#pragma once

#undef max
#undef min
#include <kotek.core.containers.multithreading.tbb/include/kotek_core_containers_multithreading_tbb.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.multithreading.mutex/include/kotek_core_containers_multithreading_mutex.h>
#include <kotek.core.containers.multithreading.semaphore/include/kotek_core_containers_multithreading_semaphore.h>
#include <kotek.core.containers.multithreading.shared_mutex/include/kotek_core_containers_multithreading_shared_mutex.h>
#include <kotek.core.containers.multithreading.thread/include/kotek_core_containers_multithreading_thread.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_MultiThreading(ktkMainManager* p_manager);
bool SerializeModule_Core_Containers_MultiThreading(ktkMainManager* p_manager);
bool DeserializeModule_Core_Containers_MultiThreading(
	ktkMainManager* p_manager);
bool ShutdownModule_Core_Containers_MultiThreading(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK