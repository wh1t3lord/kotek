#pragma once

#include <kotek.core.math/include/kotek_core_math.h>
#include <kotek.core.memory/include/kotek_core_memory.h>
#include <kotek.core.casting/include/kotek_core_casting.h>
#include <kotek.core.console/include/kotek_core_console.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core(ktkMainManager* p_manager);
		bool SerializeModule_Core(ktkMainManager* p_manager);
		bool DeserializeModule_Core(ktkMainManager* p_manager);
		bool ShutdownModule_Core(ktkMainManager* p_manager);

		void RegisterTests_String_ForModule_Core(void);
		void RegisterTests_Filesystem_ForModule_Core(void);
		void RegisterTests_Math_ForModule_Core(void);
	} // namespace Core
} // namespace Kotek
