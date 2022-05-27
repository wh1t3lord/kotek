#include "../include/kotek_core_constants.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Constants(ktkMainManager* p_manager) 
		{
			InitializeModule_Core_Constants_Math(p_manager);

			return true;
		}
		
		bool ShutdownModule_Core_Constants(ktkMainManager* p_manager) 
		{
			ShutdownModule_Core_Constants_Math(p_manager);

			return true;
		}
		
		bool SerializeModule_Core_Constants(ktkMainManager* p_manager) 
		{
			SerializeModule_Core_Constants_Math(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Constants(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Constants_Math(p_manager);

			return true;
		}
	}
}