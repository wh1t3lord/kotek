#include "../include/kotek_core_input.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Input(ktkMainManager* p_manager)
{
	p_manager->Set_Input(new ktkInput());

	return true;
}
bool SerializeModule_Core_Input(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Input(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Input(ktkMainManager* p_manager)
{
	ktkInput* p_instance = dynamic_cast<ktkInput*>(p_manager->GetInput());

	KOTEK_ASSERT(p_instance,
		"you must get a valid pointer of ktkInput. Otherwise you got a "
		"different type at all!!");

	delete p_instance;

	p_manager->Set_Input(nullptr);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
