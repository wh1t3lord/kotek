#pragma once

#include "kotek_main_manager.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Main_Manager(ktkMainManager*);
		bool ShutdownModule_Core_Main_Manager(ktkMainManager*);
		bool SerializeModule_Core_Main_Manager(ktkMainManager*);
		bool DeserializeModule_Core_Main_Manager(ktkMainManager*);
	}
}