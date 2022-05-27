#include "../include/kotek_core_memory_cpu.h"
#include <mimalloc.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Memory_CPU(ktkMainManager* p_manager)
		{
			// TODO: add printing mimalloc version to log mi_version();

			return true;
		}

		bool ShutdownModule_Core_Memory_CPU(ktkMainManager* p_manager)
		{
			return true;
		}

		bool SerializeModule_Core_Memory_CPU(ktkMainManager* p_manager)
		{
			return true;
		}

		bool DeserializeModule_Core_Memory_CPU(ktkMainManager* p_manager)
		{
			return true;
		}
	} // namespace Core
} // namespace Kotek