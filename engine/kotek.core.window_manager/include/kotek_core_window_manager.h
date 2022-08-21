#pragma once

#include <kotek.core.window/include/kotek_core_window.h>
#include "kotek_window_manager.h"

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
		bool InitializeModule_Core_Window_Manager(ktkMainManager* p_manager);
		bool SerializeModule_Core_Window_Manager(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Window_Manager(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Window_Manager(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
