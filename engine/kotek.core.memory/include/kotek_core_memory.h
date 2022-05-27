#pragma once

#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>
#include <kotek.core.memory.gpu/include/kotek_core_memory_gpu.h>

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
		bool InitializeModule_Core_Memory(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Memory(ktkMainManager* p_manager);
		bool SerializeModule_Core_Memory(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Memory(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek