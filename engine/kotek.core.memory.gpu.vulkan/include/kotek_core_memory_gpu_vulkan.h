#pragma once

#include <kotek.core.defines.static.render.vk/include/kotek_core_defines_static_render_vk.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include "vk_mem_alloc.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
bool ShutdownModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
bool SerializeModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
bool DeserializeModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK