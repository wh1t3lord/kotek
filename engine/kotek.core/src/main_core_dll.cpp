#include <kotek.core.memory/include/kotek_core_memory.h>
#include <kotek.engine.window/include/kotek_engine_window.h>

#include "../include/kotek_core.h"
#include "../include/kotek_main_manager.h"

#ifdef KOTEK_PLATFORM_WINDOWS
	#include <mimalloc-new-delete.h>
#endif

namespace Kotek
{
	namespace Core
	{
		bool RegisterCommands(ktkMainManager& main_manager) noexcept
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

		bool InitializeModule_Core(ktkMainManager& main_manager)
		{
			InitializeModule_Core_Memory();
			initializeModule_Core_API();
			RegisterCommands(main_manager);
			RegisterAllTests();

			return true;
		}

		bool SerializeModule_Core(void) { return true; }

		bool DeserializeModule_Core(void) { return true; }

		bool ShutdownModule_Core(void)
		{
			shutdownModule_Core_API();
			ShutdownModule_Core_Memory();

			return true;
		}
	} // namespace Core
} // namespace Kotek
