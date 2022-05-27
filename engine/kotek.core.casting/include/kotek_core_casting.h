#pragma once

#include <kotek.core.casting.lexical/include/kotek_core_casting_lexical.h>
#include <kotek.core.casting.string/include/kotek_core_casting_string.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
}

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Casting(ktkMainManager*);
		bool ShutdownModule_Core_Casting(ktkMainManager*);
		bool SerializeModule_Core_Casting(ktkMainManager*);
		bool DeserializeModule_Core_Casting(ktkMainManager*);
	}
}