#include "../include/kotek_core_memory_gpu.h"

namespace Kotek
{
	namespace Core
	{

		bool InitializeModule_Core_Memory_GPU(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Memory_GPU_Vulkan(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Memory_GPU(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Memory_GPU_Vulkan(p_manager);
			
			return true;
		}

		bool SerializeModule_Core_Memory_GPU(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Memory_GPU_Vulkan(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Memory_GPU(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Memory_GPU_Vulkan(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek