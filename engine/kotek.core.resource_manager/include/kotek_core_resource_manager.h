#pragma once

#include <kotek.core.resource_manager.loader/include/kotek_core_resource_manager_loader.h>
#include <kotek.core.resource_manager.saver/include/kotek_core_resource_manager_saver.h>
#include "kotek_resource_manager.h"

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
		bool InitializeModule_Core_Resource_Manager(ktkMainManager* p_manager);
		bool SerializeModule_Core_Resource_Manager(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Resource_Manager(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Resource_Manager(ktkMainManager* p_manager);
	}
} // namespace Kotek