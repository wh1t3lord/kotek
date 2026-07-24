#pragma once

#include "kotek_std_alias_math.h"
#include "kotek_std_math.h"
#include "kotek_std_math_functions.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Math(ktkMainManager*);
bool ShutdownModule_Core_Math(ktkMainManager*);
bool SerializeModule_Core_Math(ktkMainManager*);
bool DeserializeModule_Core_Math(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK