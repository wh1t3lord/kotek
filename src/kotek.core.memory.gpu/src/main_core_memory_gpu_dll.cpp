#include "../include/kotek_core_memory_gpu.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Memory_GPU(ktkMainManager* p_manager)
{
	if (p_manager)
	{
		if (p_manager->Get_Splash())
		{
			p_manager->Get_Splash()->Set_Text("[core]: init [memory][gpu]");
			p_manager->Get_Splash()->Set_Progress();
		}
	}

	KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core_Memory_GPU_Vulkan, p_manager);

	return true;
}

bool ShutdownModule_Core_Memory_GPU(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(SHUTDOWN, CORE, ShutdownModule_Core_Memory_GPU_Vulkan, p_manager);

	return true;
}

bool SerializeModule_Core_Memory_GPU(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(SERIALIZE, CORE, SerializeModule_Core_Memory_GPU_Vulkan, p_manager);

	return true;
}

bool DeserializeModule_Core_Memory_GPU(ktkMainManager* p_manager)
{
	KOTEK_INVOKE_MODULE(DESERIALIZE, CORE, DeserializeModule_Core_Memory_GPU_Vulkan, p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK