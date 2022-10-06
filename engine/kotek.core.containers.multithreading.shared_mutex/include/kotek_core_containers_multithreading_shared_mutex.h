#pragma once

#include "kotek_std_alias_shared_mutex.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_MultiThreading_Shared_Mutex(
	ktkMainManager* p_manager);
bool SerializeModule_Core_Containers_MultiThreading_Shared_Mutex(
	ktkMainManager* p_manager);
bool DeserializeModule_Core_Containers_MultiThreading_Shared_Mutex(
	ktkMainManager* p_manager);
bool ShutdownModule_Core_Containers_MultiThreading_Shared_Mutex(
	ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK