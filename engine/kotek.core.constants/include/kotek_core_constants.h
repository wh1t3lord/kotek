#pragma once

#include <kotek.core.constants.math/include/kotek_core_constants_math.h>
#include <kotek.core.constants.ecs/include/kotek_core_constants_ecs.h>
#include <kotek.core.constants.string/include/kotek_core_constants_string.h>
#include <kotek.core.constants.window/include/kotek_core_constants_window.h>

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
		bool InitializeModule_Core_Constants(ktkMainManager*);
		bool ShutdownModule_Core_Constants(ktkMainManager*);
		bool SerializeModule_Core_Constants(ktkMainManager*);
		bool DeserializeModule_Core_Constants(ktkMainManager*);
	}
} // namespace Kotek