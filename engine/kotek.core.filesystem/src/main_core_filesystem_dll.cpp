#include "../include/kotek_core_filesystem.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_FileSystem(ktkMainManager* p_manager)
		{
			InitializeModule_Core_FileSystem_File_Text(p_manager);

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

			return true;
		}

		bool ShutdownModule_Core_FileSystem(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_FileSystem_File_Text(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek