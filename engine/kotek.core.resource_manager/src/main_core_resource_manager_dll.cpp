#include "../include/kotek_core_resource_manager.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Resource_Manager(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Resource_Manager_Loader(p_manager);
			InitializeModule_Core_Resource_Manager_Saver(p_manager);

			return true;
		}

		bool SerializeModule_Core_Resource_Manager(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Resource_Manager_Loader(p_manager);
			SerializeModule_Core_Resource_Manager_Saver(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Resource_Manager(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Resource_Manager_Loader(p_manager);
			DeserializeModule_Core_Resource_Manager_Saver(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Resource_Manager(ktkMainManager* p_manager) 
		{
			ShutdownModule_Core_Resource_Manager_Loader(p_manager);
			ShutdownModule_Core_Resource_Manager_Saver(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek