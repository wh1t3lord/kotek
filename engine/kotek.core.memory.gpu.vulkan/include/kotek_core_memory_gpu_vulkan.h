#pragma once

#include <kotek.core.defines.static.render.vk/include/kotek_core_defines_static_render_vk.h>
#include "vk_mem_alloc.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
}

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
		bool SerializeModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Memory_GPU_Vulkan(ktkMainManager* p_manager);
	}
}