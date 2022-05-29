#pragma once

#include <kotek.core.os.win32/include/kotek_core_os_win32.h>
#include <kotek.core.os.linux/include/kotek_core_os_linux.h>

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
		bool InitializeModule_Core_OS(ktkMainManager* p_manager);
		bool SerializeModule_Core_OS(ktkMainManager* p_manager);
		bool DeserializeModule_Core_OS(ktkMainManager* p_manager);
		bool ShutdownModule_Core_OS(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
