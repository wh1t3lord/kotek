#pragma once

#include <kotek.core.defines.static.os.linux/include/kotek_core_defines_static_os_linux.h>
#include <kotek.core.defines.static.os.win32/include/kotek_core_defines_static_os_win32.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines_Static_OS(ktkMainManager*);
bool ShutdownModule_Core_Defines_Static_OS(ktkMainManager*);
bool SerializeModule_Core_Defines_Static_OS(ktkMainManager*);
bool DeserializeModule_Core_Defines_Static_OS(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
