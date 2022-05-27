#pragma once

#include <kotek.core.defines.static.os.linux/include/kotek_core_defines_static_os_linux.h>
#include <kotek.core.defines.static.os.win32/include/kotek_core_defines_static_os_win32.h>

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
		bool InitializeModule_Core_Defines_Static_OS(ktkMainManager*);
		bool ShutdownModule_Core_Defines_Static_OS(ktkMainManager*);
		bool SerializeModule_Core_Defines_Static_OS(ktkMainManager*);
		bool DeserializeModule_Core_Defines_Static_OS(ktkMainManager*);
	}
} // namespace Kotek
