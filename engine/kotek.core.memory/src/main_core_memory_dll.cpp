#include "../include/kotek_core_memory.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Memory(ktkMainManager* p_manager)
{
	InitializeModule_Core_Memory_CPU(p_manager);
	InitializeModule_Core_Memory_GPU(p_manager);

	return true;
}

bool ShutdownModule_Core_Memory(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Memory_GPU(p_manager);
	ShutdownModule_Core_Memory_CPU(p_manager);


	return true;
}

bool SerializeModule_Core_Memory(ktkMainManager* p_manager)
{
	SerializeModule_Core_Memory_CPU(p_manager);
	SerializeModule_Core_Memory_GPU(p_manager);

	return true;
}

bool DeserializeModule_Core_Memory(ktkMainManager* p_manager)
{
	SerializeModule_Core_Memory_CPU(p_manager);
	SerializeModule_Core_Memory_GPU(p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK