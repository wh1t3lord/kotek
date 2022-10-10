#pragma once

#include <kotek.core.resource_manager.loader/include/kotek_core_resource_manager_loader.h>
#include <kotek.core.resource_manager.saver/include/kotek_core_resource_manager_saver.h>
#include "kotek_resource_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Resource_Manager(ktkMainManager* p_manager);
		bool SerializeModule_Core_Resource_Manager(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Resource_Manager(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Resource_Manager(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek