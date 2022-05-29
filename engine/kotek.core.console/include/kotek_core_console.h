#pragma once

#include "kotek_console.h"

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
		bool InitializeModule_Core_Console(ktkMainManager* p_manager);
		bool SerializeModule_Core_Console(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Console(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Console(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
