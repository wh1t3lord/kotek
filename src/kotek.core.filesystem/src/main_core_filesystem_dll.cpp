#include "../include/kotek_core_filesystem.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

#include <kotek.core.engine_config/include/kotek_core_engine_config.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_FileSystem(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [filesystem]");
		p_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_Core_FileSystem_File_Text(p_manager);

	ktkFileSystem* p_instance = new ktkFileSystem();
	p_instance->Initialize();

	p_manager->Set_FileSystem(p_instance);

	return true;
}

bool SerializeModule_Core_FileSystem(ktkMainManager* p_manager)
{
	SerializeModule_Core_FileSystem_File_Text(p_manager);

	return true;
}

bool DeserializeModule_Core_FileSystem(ktkMainManager* p_manager)
{
	DeserializeModule_Core_FileSystem_File_Text(p_manager);

	return true;
}

bool ShutdownModule_Core_FileSystem(ktkMainManager* p_manager)
{
	ShutdownModule_Core_FileSystem_File_Text(p_manager);

	ktkFileSystem* p_instance =
		dynamic_cast<ktkFileSystem*>(p_manager->GetFileSystem());

	KOTEK_ASSERT(p_instance,
		"you must get the valid pointer of ktkFileSystem otherwise "
		"something is wrong!!!");

	p_instance->Shutdown();
	delete p_instance;

	p_manager->Set_FileSystem(nullptr);

	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK