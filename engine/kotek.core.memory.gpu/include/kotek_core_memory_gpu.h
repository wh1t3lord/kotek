#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_MEMORY_LEAK_DETECTION_VLD
	#include <kotek.core.memory.vld/include/kotek_core_memory_vld.h>
#endif

#include <kotek.core.memory.gpu.vulkan/include/kotek_core_memory_gpu_vulkan.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Memory_GPU(ktkMainManager* p_manager);
bool ShutdownModule_Core_Memory_GPU(ktkMainManager* p_manager);
bool SerializeModule_Core_Memory_GPU(ktkMainManager* p_manager);
bool DeserializeModule_Core_Memory_GPU(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK