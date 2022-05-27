#pragma once

#include "kotek_std_constants.h"

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
		bool InitializeModule_Core_Constants_ECS(ktkMainManager*);
		bool ShutdownModule_Core_Constants_ECS(ktkMainManager*);
		bool SerializeModule_Core_Constants_ECS(ktkMainManager*);
		bool DeserializeModule_Core_Constants_ECS(ktkMainManager*);
	}
} // namespace Kotek