#include "../include/kotek_core_types.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Types(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Types_Char, p_manager);
	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Types_Numerics, p_manager);
	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Types_String, p_manager);

	return true;
}

bool SerializeModule_Core_Types(ktkMainManager* p_manager)
{
	SerializeModule_Core_Types_Char(p_manager);
	SerializeModule_Core_Types_Numerics(p_manager);
	SerializeModule_Core_Types_String(p_manager);

	return true;
}

bool DeserializeModule_Core_Types(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Types_Char(p_manager);
	DeserializeModule_Core_Types_Numerics(p_manager);
	DeserializeModule_Core_Types_String(p_manager);

	return true;
}

bool ShutdownModule_Core_Types(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Types_Char, p_manager);
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Types_Numerics, p_manager);
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Types_String, p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
