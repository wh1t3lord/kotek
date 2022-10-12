#include "../include/kotek_api.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_API(ktkMainManager* p_manager)
{
	// not used really

	return true;
}

bool SerializeModule_Core_API(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_API(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_API(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK