#pragma once

#include "kotek_std_alias_unordered_map.h"

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
		bool InitializeModule_Core_Containers_Unordered_Map(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers_Unordered_Map(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers_Unordered_Map(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers_Unordered_Map(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek