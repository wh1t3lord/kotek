#pragma once

#include <kotek.core.containers.microsoft.wrl.comptr/include/kotek_core_containers_microsoft_wrl_comptr.h>

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
		bool InitializeModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager);
		bool SerializeModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager);
		bool DeserializeModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager);
		bool ShutdownModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek