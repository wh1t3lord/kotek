#include "../include/kotek_core_containers_filesystem_path.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

char fs_give_opposite_to_preferred_separator(char separator)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (separator == '\\')
		return '/';
	else
		return separator;
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error implement
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#else
	#error unknown platform, report to developers or community
	return 0;
#endif
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Containers_FileSystem_Path(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text(
			"[core]: init [containers][filesystem][path]");
		p_manager->Get_Splash()->Set_Progress();
	}

	return true;
}

bool SerializeModule_Core_Containers_FileSystem_Path(ktkMainManager* p_manager)
{
	return true;
}

bool DeserializeModule_Core_Containers_FileSystem_Path(
	ktkMainManager* p_manager)
{
	return true;
}

bool ShutdownModule_Core_Containers_FileSystem_Path(ktkMainManager* p_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK