#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Profilers_GPU(ktkMainManager* p_manager);
bool SerializeModule_Core_Profilers_GPU(ktkMainManager* p_manager);
bool DeserializeModule_Core_Profilers_GPU(ktkMainManager* p_manager);
bool ShutdownModule_Core_Profilers_GPU(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK