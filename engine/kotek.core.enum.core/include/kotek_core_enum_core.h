#pragma once

#include "kotek_enum.h"
#include "kotek_translation.h"

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
		bool InitializeModule_Core_Enum_Core(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Enum_Core(ktkMainManager* p_manager);
		bool SerializeModule_Core_Enum_Core(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Enum_Core(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek