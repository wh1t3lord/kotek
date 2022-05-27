#pragma once

#include <kotek.core.memory.vld/include/kotek_core_memory_vld.h>
#include "kotek_std_memory.h"

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
		bool InitializeModule_Core_Memory_CPU(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Memory_CPU(ktkMainManager* p_manager);
		bool SerializeModule_Core_Memory_CPU(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Memory_CPU(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek