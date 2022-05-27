#pragma once

#include "kotek_std_alias_math.h"
#include "kotek_std_math.h"

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
		bool InitializeModule_Core_Math(ktkMainManager*);
		bool ShutdownModule_Core_Math(ktkMainManager*);
		bool SerializeModule_Core_Math(ktkMainManager*);
		bool DeserializeModule_Core_Math(ktkMainManager*);
	}
}