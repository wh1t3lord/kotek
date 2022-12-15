#include "../include/kotek_core_filesystem.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_FileSystem(ktkMainManager* p_manager)
{
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

	auto* p_filesystem = p_manager->GetFileSystem();

	KOTEK_ASSERT(p_filesystem,
		"you must initialize filesystem instance before calling this function");

	auto path_to_sys_info_json =
		p_filesystem->GetFolderByEnum(eFolderIndex::kFolderIndex_Root);

	path_to_sys_info_json /= kConfigFileNameSystemInfo;

	if (p_filesystem->IsValidPath(path_to_sys_info_json))
	{
		// we do nothing here because this stage in kotek.game
	}
	else
	{
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
		sys_info.Write(kSysInfoFieldName_UserLibraryNameWindows, "game.dll");
		sys_info.Write(kSysInfoFieldName_UserLibraryNameLinux, "game.so");
		sys_info.Write(kSysInfoFieldName_UserLibraryNameMacOS, "game.so");

		sys_info.Write(kSysInfoFieldName_FallbackRenderer,
			KOTEK_SYSINFO_FIELD_FALLBACK_RENDERER_VALUE);
		sys_info.Write(kSysInfoFieldName_RendererForLoading,
			KOTEK_SYSINFO_FIELD_RENDERER_FOR_LOADING_VALUE);
	}

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