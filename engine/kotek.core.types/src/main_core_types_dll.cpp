#include "../include/kotek_core_types.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Types(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Types_Char(p_manager);
			InitializeModule_Core_Types_Numerics(p_manager);
			InitializeModule_Core_Types_String(p_manager);

			return true;
		}

		bool SerializeModule_Core_Types(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Types_Char(p_manager);
			SerializeModule_Core_Types_Numerics(p_manager);
			SerializeModule_Core_Types_String(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Types(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Types_Char(p_manager);
			DeserializeModule_Core_Types_Numerics(p_manager);
			DeserializeModule_Core_Types_String(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Types(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Types_Char(p_manager);
			ShutdownModule_Core_Types_Numerics(p_manager);
			ShutdownModule_Core_Types_String(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek
