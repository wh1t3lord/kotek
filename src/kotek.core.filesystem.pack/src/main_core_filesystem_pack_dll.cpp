#include "../include/kotek_core_filesystem_pack.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_FileSystem_Pack(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text(
			"[core]: init [filesystem][pack]");
		p_manager->Get_Splash()->Set_Progress();
	}

	// the pack backend is owned BY VALUE by ktkFileSystem (module
	// kotek.core.filesystem) — nothing registers itself here; this entry
	// exists per the module-entry convention
	return true;
}

bool SerializeModule_Core_FileSystem_Pack(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_FileSystem_Pack(ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_FileSystem_Pack(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
