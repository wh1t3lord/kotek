#pragma once

/*
    Note: if you have errors related to preprocessor (like it is undefined) that
   means you need to specify in cmake " target_link_libraries(${PROJECT_NAME}
   PUBLIC kotek.core.defines.static.os) "

    That means you explicit define dependency for project don't use
   KOTEK_USE_PLATFORM_XXX preprocessor because it is for projects that don't
   need to have explicit connection (but we strongly suggest to have explicit
   connection between libraries that connection based on cmake via
   target_link_libraries) making implicit connection by include (where
   preprocessor specified) is not right because you need to specify library
   where preprocessor is located by that logic.
*/
#ifdef KOTEK_PLATFORM_WINDOWS
	#include <kotek.core.os.win32/include/kotek_core_os_win32.h>
#elif defined(KOTEK_PLATFORM_LINUX)
	#include <kotek.core.os.linux/include/kotek_core_os_linux.h>
#else
	#error unknown platform
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_OS(ktkMainManager* p_manager);
bool SerializeModule_Core_OS(ktkMainManager* p_manager);
bool DeserializeModule_Core_OS(ktkMainManager* p_manager);
bool ShutdownModule_Core_OS(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
