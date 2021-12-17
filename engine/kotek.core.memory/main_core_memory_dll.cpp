#include "kotek_core_memory.h"
#include <iostream>
#include <mimalloc.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Memory(void)
		{
			std::cout << "[" << __FILE__ << "]"
					  << "[" << __FUNCTION__ << "]"
					  << "[" << __LINE__ << "]"
					  << " "
					  << "initialized!" << std::endl;

			std::cout << "[" << __FILE__ << "]"
					  << "[" << __FUNCTION__ << "]"
					  << "[" << __LINE__ << "]"
					  << " "
					  << "mimalloc version: " << mi_version() << std::endl;

			return true;
		}

		bool SerializeModule_Core_Memory(void) { return true; }

		bool DeserializeModule_Core_Memory(void) { return true; }

		bool ShutdownModule_Core_Memory(void)
		{
			std::cout << "[" << __FILE__ << "]"
					  << "[" << __FUNCTION__ << "]"
					  << "[" << __LINE__ << "]"
					  << " "
					  << "shutdown" << std::endl;

			return true;
		}
	} // namespace Core
} // namespace Kotek