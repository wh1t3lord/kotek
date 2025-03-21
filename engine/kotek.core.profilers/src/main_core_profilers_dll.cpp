#include "../include/kotek_core_profilers.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Profilers(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [profilers]");
		p_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_Core_Profilers_CPU(p_manager);
	InitializeModule_Core_Profilers_GPU(p_manager);

	p_manager->Set_Profiler(new ktkProfiler());

	return true;
}

bool SerializeModule_Core_Profilers(ktkMainManager* p_manager)
{
	SerializeModule_Core_Profilers_CPU(p_manager);
	SerializeModule_Core_Profilers_GPU(p_manager);

	return true;
}

bool DeserializeModule_Core_Profilers(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Profilers_CPU(p_manager);
	DeserializeModule_Core_Profilers_GPU(p_manager);

	return true;
}

bool ShutdownModule_Core_Profilers(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Profilers_CPU(p_manager);
	ShutdownModule_Core_Profilers_GPU(p_manager);

	ktkProfiler* p_instance =
		dynamic_cast<ktkProfiler*>(p_manager->GetProfiler());

	KOTEK_ASSERT(p_instance,
		"you must get a valid pointer of ktkProfiler otherwise you got "
		"different type at all!");

	delete p_instance;

	p_manager->Set_Profiler(nullptr);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
