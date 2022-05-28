#pragma once

#include "kotek_std_alias_shared_ptr.h"

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
		bool InitializeModule_Core_Containers_Shared_Ptr(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers_Shared_Ptr(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers_Shared_Ptr(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers_Shared_Ptr(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek