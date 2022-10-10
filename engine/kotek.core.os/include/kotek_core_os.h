#pragma once

#include <kotek.core.os.win32/include/kotek_core_os_win32.h>
#include <kotek.core.os.linux/include/kotek_core_os_linux.h>

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
