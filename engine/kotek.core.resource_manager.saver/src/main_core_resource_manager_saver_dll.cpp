#include "../include/kotek_core_resource_manager_saver.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Resource_Manager_Saver(ktkMainManager* p_manager)
{
	KOTEK_ASSERT(p_manager->GetResourceManager(),
		"you must initialize resource manager");

	p_manager->GetResourceManager()->Set_ResourceSaver(
		new ktkResourceSaverManager());

	return true;
}

bool SerializeModule_Core_Resource_Manager_Saver(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Resource_Manager_Saver(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Resource_Manager_Saver(ktkMainManager* p_manager)
{
	KOTEK_ASSERT(p_manager->GetResourceManager(),
		"you must have an initialized instance of ktkResourceManager "
		"(ktkIResourceManager)");

	ktkResourceSaverManager* p_instance =
		dynamic_cast<ktkResourceSaverManager*>(
			p_manager->GetResourceManager()->Get_ResourceSaver());

	KOTEK_ASSERT(p_instance,
		"you must get valid ktkResourceSaverManager* otherwise it means that "
		"engine can't cast to that type");

	delete p_instance;
	p_manager->GetResourceManager()->Set_ResourceSaver(nullptr);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK