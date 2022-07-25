#include "../include/kotek_core_memory_cpu.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Memory_CPU(ktkMainManager* p_manager)
		{
			// TODO: think how to resolve the thing with logging, because I need
			// to write the mimalloc version here
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