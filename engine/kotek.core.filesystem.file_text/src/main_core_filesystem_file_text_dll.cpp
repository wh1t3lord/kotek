#include "../include/kotek_core_filesystem_file_text.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_FileSystem_File_Text(ktkMainManager* p_manager)
{
	KOTEK_ASSERT(p_manager->GetResourceManager(),
		"you must initialize resource manager before calling this function!");
	KOTEK_ASSERT(p_manager->GetResourceManager()->Get_ResourceLoader(),
		"before calling this function you must initialize resource loader!");
	KOTEK_ASSERT(p_manager->GetResourceManager()->Get_ResourceSaver(),
		"before calling this function you must initialize resource saver!");

	p_manager->GetResourceManager()->Get_ResourceLoader()->Set_Loader(
		eResourceLoadingType::kText, new ktkResourceLoaderFile_Text(p_manager));
	p_manager->GetResourceManager()->Get_ResourceSaver()->Set_Saver(
		eResourceLoadingType::kText, new ktkResourceSaverFile_Text(p_manager));
	return true;
}

bool SerializeModule_Core_FileSystem_File_Text(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_FileSystem_File_Text(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_FileSystem_File_Text(ktkMainManager* p_manager)
{
	KOTEK_ASSERT(p_manager->GetResourceManager(),
		"you must have a valid resource manager before calling this function!");
	KOTEK_ASSERT(p_manager->GetResourceManager()->Get_ResourceLoader(),
		"before calling this function you must have a valid resource loader!");

	auto* p_loader =
		p_manager->GetResourceManager()->Get_ResourceLoader()->Get_Loader(
			eResourceLoadingType::kText);

	KOTEK_ASSERT(p_loader, "you must have a registered loader for text files");

	delete p_loader;

	auto* p_saver =
		p_manager->GetResourceManager()->Get_ResourceSaver()->Get_Saver(
			eResourceLoadingType::kText);

	KOTEK_ASSERT(p_saver, "you must have a registered saver for text files");

	delete p_saver;

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK