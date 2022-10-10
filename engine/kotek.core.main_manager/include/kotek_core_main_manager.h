#pragma once

#include "kotek_main_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Main_Manager(ktkMainManager*);
bool ShutdownModule_Core_Main_Manager(ktkMainManager*);
bool SerializeModule_Core_Main_Manager(ktkMainManager*);
bool DeserializeModule_Core_Main_Manager(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK