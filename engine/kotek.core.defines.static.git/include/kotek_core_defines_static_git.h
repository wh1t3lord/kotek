#pragma once

#include "kotek_std_preprocessors.h"

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines_Static_Git(ktkMainManager*);
bool ShutdownModule_Core_Defines_Static_Git(ktkMainManager*);
bool SerializeModule_Core_Defines_Static_Git(ktkMainManager*);
bool DeserializeModule_Core_Defines_Static_Git(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK