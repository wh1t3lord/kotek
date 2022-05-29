#include "../include/kotek_core.h"
#include "../include/kotek_main_manager.h"

namespace Kotek
{
	namespace Core
	{
		bool RegisterCommands(ktkMainManager* p_manager) noexcept
		{
			return true;
		}

		void RegisterAllTests(void)
		{
#ifdef KOTEK_USE_TESTS
			RegisterTests_String_ForModule_Core();
			RegisterTests_Filesystem_ForModule_Core();
			RegisterTests_Math_ForModule_Core();
#endif
		}

		bool InitializeModule_Core(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Memory(p_manager);
			InitializeModule_Core_API(p_manager);
			InitializeModule_Core_Math(p_manager);
			InitializeModule_Core_Casting(p_manager);
			InitializeModule_Core_Constants(p_manager);
			InitializeModule_Core_Defines(p_manager);
			InitializeModule_Core_Console(p_manager);
			InitializeModule_Core_Containers(p_manager);
			InitializeModule_Core_FileSystem(p_manager);
			InitializeModule_Core_Format(p_manager);
			InitializeModule_Core_Profilers(p_manager);

			RegisterCommands(p_manager);
			RegisterAllTests();

			return true;
		}

		bool SerializeModule_Core(ktkMainManager* p_manager) { return true; }

		bool DeserializeModule_Core(ktkMainManager* p_manager) { return true; }

		bool ShutdownModule_Core(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Math(p_manager);
			ShutdownModule_Core_API(p_manager);
			ShutdownModule_Core_Memory(p_manager);
			ShutdownModule_Core_Casting(p_manager);
			ShutdownModule_Core_Constants(p_manager);
			ShutdownModule_Core_Defines(p_manager);
			ShutdownModule_Core_Console(p_manager);
			ShutdownModule_Core_Containers(p_manager);
			ShutdownModule_Core_FileSystem(p_manager);
			ShutdownModule_Core_Format(p_manager);
			ShutdownModule_Core_Profilers(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek
