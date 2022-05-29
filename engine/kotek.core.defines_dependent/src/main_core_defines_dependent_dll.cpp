#include "../include/kotek_core_defines_dependent.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Defines_Dependent(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Defines_Dependent_Assert(p_manager);
			InitializeModule_Core_Defines_Dependent_ECS(p_manager);
			InitializeModule_Core_Defines_Dependent_Message(p_manager);
			InitializeModule_Core_Defines_Dependent_Text(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Defines_Dependent(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Defines_Dependent_Assert(p_manager);
			ShutdownModule_Core_Defines_Dependent_ECS(p_manager);
			ShutdownModule_Core_Defines_Dependent_Message(p_manager);
			ShutdownModule_Core_Defines_Dependent_Text(p_manager);

			return true;
		}

		bool SerializeModule_Core_Defines_Dependent(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Defines_Dependent_Assert(p_manager);
			SerializeModule_Core_Defines_Dependent_ECS(p_manager);
			SerializeModule_Core_Defines_Dependent_Message(p_manager);
			SerializeModule_Core_Defines_Dependent_Text(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Defines_Dependent(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Defines_Dependent_Assert(p_manager);
			DeserializeModule_Core_Defines_Dependent_ECS(p_manager);
			DeserializeModule_Core_Defines_Dependent_Message(p_manager);
			DeserializeModule_Core_Defines_Dependent_Text(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek