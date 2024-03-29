#include "../include/kotek_core_enum.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Enum(ktkMainManager* p_manager)
{
	InitializeModule_Core_Enum_Core(p_manager);
	InitializeModule_Core_Enum_Render(p_manager);

	return true;
}

bool ShutdownModule_Core_Enum(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Enum_Core(p_manager);
	ShutdownModule_Core_Enum_Render(p_manager);

	return true;
}

bool SerializeModule_Core_Enum(ktkMainManager* p_manager)
{
	SerializeModule_Core_Enum_Core(p_manager);
	SerializeModule_Core_Enum_Render(p_manager);

	return true;
}

bool DeserializeModule_Core_Enum(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Enum_Core(p_manager);
	DeserializeModule_Core_Enum_Render(p_manager);

	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK