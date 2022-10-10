#include "../include/kotek_core_log.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Log(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_BOOST_LIBRARY
// TODO: filter messages when you pass type through cmake like
// KOTEK_LOG_SEVERITY_LEVEL=info and will be generated preprocessor like
// KOTEK_USE_LOG_SEVERITY_LEVEL info
#endif

	return true;
}

bool SerializeModule_Core_Log(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Log(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Log(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
