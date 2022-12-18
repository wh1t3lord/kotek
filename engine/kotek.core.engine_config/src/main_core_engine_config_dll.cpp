#include "../include/kotek_core_engine_config.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.filesystem/include/kotek_core_filesystem.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Engine_Config(ktkMainManager* p_manager)
{
	ktkEngineConfig* p_instance = new ktkEngineConfig();
	p_instance->Initialize();

	p_manager->Set_EngineConfig(p_instance);

	return true;
}

bool SerializeModule_Core_Engine_Config(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Engine_Config(ktkMainManager* p_manager)
{
	auto* p_filesystem = p_manager->GetFileSystem();

	KOTEK_ASSERT(p_filesystem,
		"you must initialize filesystem instance before calling this function");

	auto path_to_sys_info_json =
		p_filesystem->GetFolderByEnum(eFolderIndex::kFolderIndex_Root);

	path_to_sys_info_json /= kConfigFileNameSystemInfo;

	if (!p_filesystem->IsValidPath(path_to_sys_info_json))
	{
		KOTEK_ASSERT(p_manager->GetResourceManager(),
			"you must initialize resource manager");
		KOTEK_ASSERT(p_manager->GetResourceManager()->Get_ResourceSaver(),
			"you must initialize general manager saver");
		// so we didn't find our file, we need to generate that

		// it is our standard we can't change and alter name of sys_info config!
		// All who uses that must follow one line otherwise it causes break
		// changes and it is not standartization way :)))))
		ktkFileText sys_info("sys_info");

		sys_info.Write(
			kSysInfoFieldName_InitializeCallback, kUserCallbackName_Initialize);
		sys_info.Write(
			kSysInfoFieldName_ShutdownCallback, kUserCallbackName_Shutdown);
		sys_info.Write(
			kSysInfoFieldName_UpdateCallback, kUserCallbackName_Update);
		sys_info.Write(kSysInfoFieldName_InitializeCallback_Render,
			kUserCallbackName_Initialize_Render);

		// TODO: make predefined on cmake side preprocessor !!! Important
		sys_info.Write(kSysInfoFieldName_UserLibraryName,
			KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME);

		p_manager->GetResourceManager()->Get_ResourceSaver()->Save(
			path_to_sys_info_json, &sys_info);
	}

	if (p_filesystem->IsValidPath(path_to_sys_info_json))
	{
	}

	return true;
}

bool ShutdownModule_Core_Engine_Config(ktkMainManager* p_manager)
{
	ktkEngineConfig* p_instance =
		dynamic_cast<ktkEngineConfig*>(p_manager->Get_EngineConfig());

	KOTEK_ASSERT(p_instance,
		"failed to cast to ktkEngineConfig. You must have a valid "
		"instance of it, otherwise something is wrong");

	p_instance->Shutdown();
	delete p_instance;

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
