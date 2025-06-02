#pragma once

#include "kotek_enum.h"
#include "kotek_translation.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Enum_Core(ktkMainManager* p_manager);
bool ShutdownModule_Core_Enum_Core(ktkMainManager* p_manager);
bool SerializeModule_Core_Enum_Core(ktkMainManager* p_manager);
bool DeserializeModule_Core_Enum_Core(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK