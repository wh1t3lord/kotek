#include "../include/kotek_core_filesystem.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_FileSystem(ktkMainManager* p_manager)
		{
			InitializeModule_Core_FileSystem_File_Text(p_manager);

			p_manager->Set_FileSystem(new ktkFileSystem());

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

			ktkFileSystem* p_instance =
				dynamic_cast<ktkFileSystem*>(p_manager->GetFileSystem());

			KOTEK_ASSERT(p_instance,
				"you must get the valid pointer of ktkFileSystem otherwise "
			    "something is wrong!!!");

			delete p_instance;

			p_manager->Set_FileSystem(nullptr);

			return true;
		}
	} // namespace Core
} // namespace Kotek