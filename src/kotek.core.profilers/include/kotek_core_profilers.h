#pragma once

#include <kotek.core.profilers.cpu/include/kotek_core_profilers_cpu.h>
#include <kotek.core.profilers.gpu/include/kotek_core_profilers_gpu.h>
#include "kotek_profiler.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Profilers(ktkMainManager* p_manager);
bool SerializeModule_Core_Profilers(ktkMainManager* p_manager);
bool DeserializeModule_Core_Profilers(ktkMainManager* p_manager);
bool ShutdownModule_Core_Profilers(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK