#pragma once

#include <kotek.core.types.char/include/kotek_core_types_char.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.types.string/include/kotek_core_types_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Types(ktkMainManager* p_manager);
bool SerializeModule_Core_Types(ktkMainManager* p_manager);
bool DeserializeModule_Core_Types(ktkMainManager* p_manager);
bool ShutdownModule_Core_Types(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
