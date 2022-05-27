#pragma once

#include <kotek.core.memory.vld/include/kotek_core_memory_vld.h>
#include <kotek.core.memory.gpu.vulkan/include/kotek_core_memory_gpu_vulkan.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{

	namespace Core
	{
		bool InitializeModule_Core_Memory_GPU(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Memory_GPU(ktkMainManager* p_manager);
		bool SerializeModule_Core_Memory_GPU(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Memory_GPU(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek