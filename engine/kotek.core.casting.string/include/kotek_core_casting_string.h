#pragma once

#include "kotek_std_alias_casting.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Casting_String(ktkMainManager*);
bool ShutdownModule_Core_Casting_String(ktkMainManager*);
bool SerializeModule_Core_Casting_String(ktkMainManager*);
bool DeserializeModule_Core_Casting_String(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK