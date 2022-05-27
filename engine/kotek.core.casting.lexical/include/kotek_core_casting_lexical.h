#pragma once

#include "kotek_std_alias_casting.h"

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
		bool InitializeModule_Core_Casting_Lexical(ktkMainManager*);
		bool ShutdownModule_Core_Casting_Lexical(ktkMainManager*);
		bool SerializeModule_Core_Casting_Lexical(ktkMainManager*);
		bool DeserializeModule_Core_Casting_Lexical(ktkMainManager*);
	}
}