#pragma once

#include "kotek_main_manager.h"

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
		bool InitializeModule_Core_Main_Manager(void);
		bool ShutdownModule_Core_Main_Manager(void);
		bool SerializeModule_Core_Main_Manager(void);
		bool DeserializeModule_Core_Main_Manager(void);
	}
}