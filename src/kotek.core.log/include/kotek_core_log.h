#pragma once

#include "kotek_log.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Log(ktkMainManager* p_manager);
bool SerializeModule_Core_Log(ktkMainManager* p_manager);
bool DeserializeModule_Core_Log(ktkMainManager* p_manager);
bool ShutdownModule_Core_Log(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
