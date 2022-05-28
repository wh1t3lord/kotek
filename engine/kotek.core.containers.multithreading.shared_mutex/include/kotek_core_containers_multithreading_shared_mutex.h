#pragma once

#include "kotek_std_alias_shared_mutex.h"

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
		bool InitializeModule_Core_Containers_MultiThreading_Shared_Mutex(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers_MultiThreading_Shared_Mutex(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers_MultiThreading_Shared_Mutex(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers_MultiThreading_Shared_Mutex(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek