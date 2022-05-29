#pragma once

#include "kotek_os.h"

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
		bool InitializeModule_Core_OS_Linux(ktkMainManager* p_manager);
		bool SerializeModule_Core_OS_Linux(ktkMainManager* p_manager);
		bool DeserializeModule_Core_OS_Linux(ktkMainManager* p_manager);
		bool ShutdownModule_Core_OS_Linux(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
