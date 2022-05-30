#include "../include/kotek_core_ecs.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_ECS(ktkMainManager* p_manager)
		{
			return true;
		}
		bool SerializeModule_Core_ECS(ktkMainManager* p_manager) 
		{
			return true; 
		}

		bool DeserializeModule_Core_ECS(ktkMainManager* p_manager)
		{
			return true;
		}
		
		bool ShutdownModule_Core_ECS(ktkMainManager* p_manager)
		{
			return true; 
		}
	} // namespace Core
} // namespace Kotek
