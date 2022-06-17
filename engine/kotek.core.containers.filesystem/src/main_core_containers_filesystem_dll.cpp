#include "../include/kotek_core_containers_filesystem.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Containers_FileSystem(
			ktkMainManager* p_manager)
		{
			InitializeModule_Core_Containers_FileSystem_Path(p_manager);

			return true;
		}

		bool SerializeModule_Core_Containers_FileSystem(
			ktkMainManager* p_manager)
		{
			SerializeModule_Core_Containers_FileSystem_Path(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Containers_FileSystem(
			ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Containers_FileSystem_Path(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Containers_FileSystem(
			ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Containers_FileSystem_Path(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek