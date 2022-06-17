#pragma once

#include <kotek.core.containers.filesystem.path/include/kotek_core_containers_filesystem_path.h>
#include "kotek_std_alias_filesystem.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Containers_FileSystem(ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers_FileSystem(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers_FileSystem(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers_FileSystem(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek