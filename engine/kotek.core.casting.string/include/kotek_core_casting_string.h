#pragma once

#include "kotek_std_alias_casting.h"

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
		bool InitializeModule_Core_Casting_String(ktkMainManager*);
		bool ShutdownModule_Core_Casting_String(ktkMainManager*);
		bool SerializeModule_Core_Casting_String(ktkMainManager*);
		bool DeserializeModule_Core_Casting_String(ktkMainManager*);
	} // namespace Core
} // namespace Kotek