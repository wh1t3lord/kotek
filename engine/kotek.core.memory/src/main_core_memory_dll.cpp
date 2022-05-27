#include "../include/kotek_core_memory.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Memory(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Memory_CPU(p_manager);
			InitializeModule_Core_Memory_GPU(p_manager);

			return true;
		}
		
		bool ShutdownModule_Core_Memory(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Memory_CPU(p_manager);
			ShutdownModule_Core_Memory_GPU(p_manager);

			return true;
		}
		
		bool SerializeModule_Core_Memory(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Memory_CPU(p_manager);
			SerializeModule_Core_Memory_GPU(p_manager);

			return true;
		}
		
		bool DeserializeModule_Core_Memory(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Memory_CPU(p_manager);
			SerializeModule_Core_Memory_GPU(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek