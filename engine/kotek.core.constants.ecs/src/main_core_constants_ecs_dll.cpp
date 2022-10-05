#include "../include/kotek_core_constants_ecs.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
	KOTEK_BEGIN_NAMESPACE_CORE
		bool InitializeModule_Core_Constants_ECS(ktkMainManager* p_manager) 
		{
			return true;
		}
		
		bool ShutdownModule_Core_Constants_ECS(ktkMainManager* p_manager) 
		{
			return true;
		}
		
		bool SerializeModule_Core_Constants_ECS(ktkMainManager* p_manager) 
		{
			return true;
		}

		bool DeserializeModule_Core_Constants_ECS(ktkMainManager* p_manager)
		{
			return true;
		}
	KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK