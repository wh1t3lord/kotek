#pragma once

#include <kotek.core.defines.static/include/kotek_core_defines_static.h>
#include <kotek.core.defines_dependent/include/kotek_core_defines_dependent.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines(ktkMainManager* p_manager);
bool ShutdownModule_Core_Defines(ktkMainManager* p_manager);
bool SerializeModule_Core_Defines(ktkMainManager* p_manager);
bool DeserializeModule_Core_Defines(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK