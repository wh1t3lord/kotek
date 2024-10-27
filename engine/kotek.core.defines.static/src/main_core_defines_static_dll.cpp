#include "../include/kotek_core_defines_static.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines_Static(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [defines][static]");
		p_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_Core_Defines_Static_CPP(p_manager);
	InitializeModule_Core_Defines_Static_Git(p_manager);
	InitializeModule_Core_Defines_Static_Math(p_manager);
	InitializeModule_Core_Defines_Static_OS(p_manager);
	InitializeModule_Core_Defines_Static_Profilers(p_manager);
	InitializeModule_Core_Defines_Static_SDK(p_manager);
	InitializeModule_Core_Defines_Static_String(p_manager);
	InitializeModule_Core_Defines_Static_Tests(p_manager);
	InitializeModule_Core_Defines_Static_Render(p_manager);

	return true;
}

bool ShutdownModule_Core_Defines_Static(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Defines_Static_CPP(p_manager);
	ShutdownModule_Core_Defines_Static_Git(p_manager);
	ShutdownModule_Core_Defines_Static_Math(p_manager);
	ShutdownModule_Core_Defines_Static_OS(p_manager);
	ShutdownModule_Core_Defines_Static_Profilers(p_manager);
	ShutdownModule_Core_Defines_Static_SDK(p_manager);
	ShutdownModule_Core_Defines_Static_String(p_manager);
	ShutdownModule_Core_Defines_Static_Tests(p_manager);
	ShutdownModule_Core_Defines_Static_Render(p_manager);

	return true;
}

bool SerializeModule_Core_Defines_Static(ktkMainManager* p_manager)
{
	SerializeModule_Core_Defines_Static_CPP(p_manager);
	SerializeModule_Core_Defines_Static_Git(p_manager);
	SerializeModule_Core_Defines_Static_Math(p_manager);
	SerializeModule_Core_Defines_Static_OS(p_manager);
	SerializeModule_Core_Defines_Static_Profilers(p_manager);
	SerializeModule_Core_Defines_Static_SDK(p_manager);
	SerializeModule_Core_Defines_Static_String(p_manager);
	SerializeModule_Core_Defines_Static_Tests(p_manager);
	SerializeModule_Core_Defines_Static_Render(p_manager);

	return true;
}

bool DeserializeModule_Core_Defines_Static(ktkMainManager* p_manager)
{
	DeserializeModule_Core_Defines_Static_CPP(p_manager);
	DeserializeModule_Core_Defines_Static_Git(p_manager);
	DeserializeModule_Core_Defines_Static_Math(p_manager);
	DeserializeModule_Core_Defines_Static_OS(p_manager);
	DeserializeModule_Core_Defines_Static_Profilers(p_manager);
	DeserializeModule_Core_Defines_Static_SDK(p_manager);
	DeserializeModule_Core_Defines_Static_String(p_manager);
	DeserializeModule_Core_Defines_Static_Tests(p_manager);
	DeserializeModule_Core_Defines_Static_Render(p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK