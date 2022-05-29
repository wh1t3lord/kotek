#pragma once

#include <kotek.core.defines.static/include/kotek_core_defines_static.h>
#include <kotek.core.defines_dependent/include/kotek_core_defines_dependent.h>

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
		bool InitializeModule_Core_Defines(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Defines(ktkMainManager* p_manager);
		bool SerializeModule_Core_Defines(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Defines(ktkMainManager* p_manager);
	}
}