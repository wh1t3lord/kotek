#include "../include/kotek_core_main_manager.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Main_Manager(ktkMainManager* p_main_manager) 
		{
			p_main_manager->Initialize();
			return true; 
		}

		bool ShutdownModule_Core_Main_Manager(ktkMainManager* p_main_manager) 
		{
			p_main_manager->Shutdown();
			return true;
		}

		bool SerializeModule_Core_Main_Manager(ktkMainManager* p_main_manager) 
		{
			return true; 
		}

		bool DeserializeModule_Core_Main_Manager(ktkMainManager* p_main_manager) 
		{
			return true; 
		}
	} // namespace Core
} // namespace Kotek