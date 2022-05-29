#pragma once

#include "kotek_log.h"


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
		bool InitializeModule_Core_Log(ktkMainManager* p_manager);
		bool SerializeModule_Core_Log(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Log(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Log(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
