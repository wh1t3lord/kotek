#include "../include/kotek_core_memory_cpu.h"
#include <kotek.core.main_manager/include/kotek_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Memory_CPU(ktkMainManager* p_manager)
{
	// TODO: think how to resolve the thing with logging, because I need
	// to write the mimalloc version here

	if (p_manager)
	{
		if (p_manager->Get_Splash())
		{
			p_manager->Get_Splash()->Set_Text("[core]: init [memory][cpu]");
			p_manager->Get_Splash()->Set_Progress();
		}
	}

#ifdef KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW);
#endif

	return true;
}

bool ShutdownModule_Core_Memory_CPU(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_MEMORY_LEAK_DETECTION_CRT
#endif

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

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK