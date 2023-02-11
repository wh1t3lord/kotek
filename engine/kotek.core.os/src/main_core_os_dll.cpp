#include "../include/kotek_core_os.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	InitializeModule_Core_OS_Win32(p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	InitializeModule_Core_OS_Linux(p_manager);
#else
    #error Unknown platform
#endif

	return true;
}
bool SerializeModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	SerializeModule_Core_OS_Win32(p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	SerializeModule_Core_OS_Linux(p_manager);
#else
    #error Unknown platform
#endif
	return true;
}

bool DeserializeModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	DeserializeModule_Core_OS_Win32(p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	DeserializeModule_Core_OS_Linux(p_manager);
#else
    #error Unknown platform
#endif

	return true;
}

bool ShutdownModule_Core_OS(ktkMainManager* p_manager)
{
#ifdef KOTEK_PLATFORM_WINDOWS
	ShutdownModule_Core_OS_Win32(p_manager);
#elif defined(KOTEK_PLATFORM_LINUX)
	ShutdownModule_Core_OS_Linux(p_manager);
#else
    #error Unknown platform
#endif

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
