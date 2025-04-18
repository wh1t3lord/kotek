﻿#include "../include/kotek_core.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool RegisterCommands(ktkMainManager* p_manager) noexcept
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [registercommands]");
		p_manager->Get_Splash()->Set_Progress();
	}

	return true;
}

void RegisterAllTests(void)
{
#ifdef KOTEK_USE_TESTS
	RegisterTests_String_ForModule_Containers_String();
	RegisterTests_Filesystem_ForModule_Core();
	RegisterTests_Math_ForModule_Core();
	RegisterTests_Translation_ForModule_Enum_Core();
	RegisterTests_Json_ForModule_Core();
	RegisterTests_String_ForModule_Core();
	RegisterTests_Input_ForModule_Core();
	RegisterTests_Utility_ForModule_Core();
#endif
}

bool InitializeModule_Core(ktkMainManager* p_manager)
{
	InitializeModule_Core_Memory(p_manager);
	InitializeModule_Core_Resource_Manager(p_manager);
	InitializeModule_Core_Enum(p_manager);
	InitializeModule_Core_API(p_manager);
	InitializeModule_Core_Math(p_manager);
	InitializeModule_Core_Casting(p_manager);
	InitializeModule_Core_Constants(p_manager);
	InitializeModule_Core_Defines(p_manager);
	InitializeModule_Core_Console(p_manager);
	InitializeModule_Core_Containers(p_manager);
	InitializeModule_Core_FileSystem(p_manager);
	InitializeModule_Core_Log(p_manager);
	InitializeModule_Core_Format(p_manager);
	InitializeModule_Core_Profilers(p_manager);
	InitializeModule_Core_OS(p_manager);
	InitializeModule_Core_Window_Manager(p_manager);
	InitializeModule_Core_Utility(p_manager);
	InitializeModule_Core_ECS(p_manager);
	InitializeModule_Core_Input(p_manager);
	InitializeModule_Core_Engine_Config(p_manager);
	InitializeModule_Core_Main_Manager(p_manager);

	RegisterCommands(p_manager);

	return true;
}

bool SerializeModule_Core(ktkMainManager* p_manager)
{
	SerializeModule_Core_Engine_Config(p_manager);

	return true;
}

bool DeserializeModule_Core(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: deserialize [core]");
		p_manager->Get_Splash()->Set_Progress();
	}

	DeserializeModule_Core_Engine_Config(p_manager);

	return true;
}

bool ShutdownModule_Core(ktkMainManager* p_manager)
{
	ShutdownModule_Core_Enum(p_manager);
	ShutdownModule_Core_Math(p_manager);
	ShutdownModule_Core_API(p_manager);
	ShutdownModule_Core_Casting(p_manager);
	ShutdownModule_Core_Constants(p_manager);
	ShutdownModule_Core_Defines(p_manager);
	ShutdownModule_Core_Console(p_manager);
	ShutdownModule_Core_Containers(p_manager);
	ShutdownModule_Core_FileSystem(p_manager);
	ShutdownModule_Core_Format(p_manager);
	ShutdownModule_Core_Profilers(p_manager);
	ShutdownModule_Core_OS(p_manager);
	ShutdownModule_Core_Window_Manager(p_manager);
	ShutdownModule_Core_Log(p_manager);
	ShutdownModule_Core_ECS(p_manager);
	ShutdownModule_Core_Input(p_manager);
	ShutdownModule_Core_Utility(p_manager);
	ShutdownModule_Core_Resource_Manager(p_manager);
	ShutdownModule_Core_Engine_Config(p_manager);

	ShutdownModule_Core_Main_Manager(p_manager);
	ShutdownModule_Core_Memory(p_manager);

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
