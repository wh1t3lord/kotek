#include "../include/kotek_core_defines.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Defines(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Defines_Static(p_manager);
			InitializeModule_Core_Defines_Dependent(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Defines(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Defines_Static(p_manager);
			ShutdownModule_Core_Defines_Dependent(p_manager);

			return true;
		}

		bool SerializeModule_Core_Defines(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Defines_Static(p_manager);
			SerializeModule_Core_Defines_Dependent(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Defines(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Defines_Static(p_manager);
			DeserializeModule_Core_Defines_Dependent(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek