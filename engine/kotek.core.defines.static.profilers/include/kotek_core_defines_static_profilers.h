#pragma once

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
		bool InitializeModule_Core_Defines_Static_Profilers(ktkMainManager*);
		bool ShutdownModule_Core_Defines_Static_Profilers(ktkMainManager*);
		bool SerializeModule_Core_Defines_Static_Profilers(ktkMainManager*);
		bool DeserializeModule_Core_Defines_Static_Profilers(ktkMainManager*);
	} // namespace Core
} // namespace Kotek