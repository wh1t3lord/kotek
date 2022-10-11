#include "../include/kotek_core_resource_manager.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Resource_Manager(ktkMainManager* p_manager)
{
	ktkResourceManager* p_instance = new ktkResourceManager();

	p_instance->Set_MainManager(p_manager);

	p_manager->SetResourceManager(p_instance);

	InitializeModule_Core_Resource_Manager_Loader(p_manager);
	InitializeModule_Core_Resource_Manager_Saver(p_manager);

	return true;
}

bool SerializeModule_Core_Resource_Manager(ktkMainManager* p_manager)
{
	SerializeModule_Core_Resource_Manager_Loader(p_manager);
	SerializeModule_Core_Resource_Manager_Saver(p_manager);

	return true;
}

bool DeserializeModule_Core_Resource_Manager(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Resource_Manager_Loader(p_manager);
	DeserializeModule_Core_Resource_Manager_Saver(p_manager);

	return true;
}

bool ShutdownModule_Core_Resource_Manager(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Resource_Manager_Loader(p_manager);
	ShutdownModule_Core_Resource_Manager_Saver(p_manager);

	ktkResourceManager* p_instance =
		dynamic_cast<ktkResourceManager*>(p_manager->GetResourceManager());

	KOTEK_ASSERT(p_instance,
		"you must got a valid casted instance of ktkResourceManager. "
		"Otherwise it is a different type at all!!");

	delete p_instance;
	p_manager->SetResourceManager(nullptr);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK