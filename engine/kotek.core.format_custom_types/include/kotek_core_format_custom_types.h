#pragma once

#include "kotek_core_format_custom_types_string.h"

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
		bool InitializeModule_Core_Format_Custom_Types(ktkMainManager* p_manager);
		bool SerializeModule_Core_Format_Custom_Types(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Format_Custom_Types(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Format_Custom_Types(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
