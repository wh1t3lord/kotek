#pragma once

#include "kotek_input.h"

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
		bool InitializeModule_Core_Input(ktkMainManager* p_manager);
		bool SerializeModule_Core_Input(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Input(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Input(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
