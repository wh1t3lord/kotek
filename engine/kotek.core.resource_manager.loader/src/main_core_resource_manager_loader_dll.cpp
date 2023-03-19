#include "../include/kotek_core_resource_manager_loader.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
{
	return true;
}

bool SerializeModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK