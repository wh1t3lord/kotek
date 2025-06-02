#pragma once

#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>
#include <kotek.core.memory.gpu/include/kotek_core_memory_gpu.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Memory(ktkMainManager* p_manager);
bool ShutdownModule_Core_Memory(ktkMainManager* p_manager);
bool SerializeModule_Core_Memory(ktkMainManager* p_manager);
bool DeserializeModule_Core_Memory(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK