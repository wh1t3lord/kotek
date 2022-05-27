#include "../include/kotek_core_defines_static.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Defines_Static(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Defines_Static_CPP(p_manager);
			InitializeModule_Core_Defines_Static_Git(p_manager);
			InitializeModule_Core_Defines_Static_Math(p_manager);
			InitializeModule_Core_Defines_Static_OS(p_manager);
			InitializeModule_Core_Defines_Static_Profilers(p_manager);
			InitializeModule_Core_Defines_Static_SDK(p_manager);
			InitializeModule_Core_Defines_Static_String(p_manager);
			InitializeModule_Core_Defines_Static_Tests(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Defines_Static(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Defines_Static_CPP(p_manager);
			ShutdownModule_Core_Defines_Static_Git(p_manager);
			ShutdownModule_Core_Defines_Static_Math(p_manager);
			ShutdownModule_Core_Defines_Static_OS(p_manager);
			ShutdownModule_Core_Defines_Static_Profilers(p_manager);
			ShutdownModule_Core_Defines_Static_SDK(p_manager);
			ShutdownModule_Core_Defines_Static_String(p_manager);
			ShutdownModule_Core_Defines_Static_Tests(p_manager);

			return true;
		}

		bool SerializeModule_Core_Defines_Static(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Defines_Static_CPP(p_manager);
			SerializeModule_Core_Defines_Static_Git(p_manager);
			SerializeModule_Core_Defines_Static_Math(p_manager);
			SerializeModule_Core_Defines_Static_OS(p_manager);
			SerializeModule_Core_Defines_Static_Profilers(p_manager);
			SerializeModule_Core_Defines_Static_SDK(p_manager);
			SerializeModule_Core_Defines_Static_String(p_manager);
			SerializeModule_Core_Defines_Static_Tests(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Defines_Static(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Defines_Static_CPP(p_manager);
			DeserializeModule_Core_Defines_Static_Git(p_manager);
			DeserializeModule_Core_Defines_Static_Math(p_manager);
			DeserializeModule_Core_Defines_Static_OS(p_manager);
			DeserializeModule_Core_Defines_Static_Profilers(p_manager);
			DeserializeModule_Core_Defines_Static_SDK(p_manager);
			DeserializeModule_Core_Defines_Static_String(p_manager);
			DeserializeModule_Core_Defines_Static_Tests(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek