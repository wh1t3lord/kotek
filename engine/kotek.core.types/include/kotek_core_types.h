#pragma once

#include <kotek.core.types.char/include/kotek_core_types_char.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.types.string/include/kotek_core_types_string.h>

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
		bool InitializeModule_Core_Types(ktkMainManager* p_manager);
		bool SerializeModule_Core_Types(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Types(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Types(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
