#pragma once

#include <kotek.core.casting.lexical/include/kotek_core_casting_lexical.h>
#include <kotek.core.casting.string/include/kotek_core_casting_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_Casting(ktkMainManager*);
bool ShutdownModule_Core_Casting(ktkMainManager*);
bool SerializeModule_Core_Casting(ktkMainManager*);
bool DeserializeModule_Core_Casting(ktkMainManager*);
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK