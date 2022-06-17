#pragma once

#include "kotek_resource_manager_loader.h"

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
		bool InitializeModule_Core_Resource_Manager_Loader(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Resource_Manager_Loader(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Resource_Manager_Loader(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Resource_Manager_Loader(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek