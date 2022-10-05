#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include "kotek_std_preprocessors.h"

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
		bool InitializeModule_Core_Defines_Static_OS_Linux(ktkMainManager*);
		bool ShutdownModule_Core_Defines_Static_OS_Linux(ktkMainManager*);
		bool SerializeModule_Core_Defines_Static_OS_Linux(ktkMainManager*);
		bool DeserializeModule_Core_Defines_Static_OS_Linux(ktkMainManager*);
	}
} // namespace Kotek