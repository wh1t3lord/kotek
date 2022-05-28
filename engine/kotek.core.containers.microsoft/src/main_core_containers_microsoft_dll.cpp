#include "../include/kotek_core_containers_microsoft.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager)
		{
			InitializeModule_Core_Containers_Microsoft_WRL_ComPtr(p_manager);

			return true;
		}

		bool SerializeModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager)
		{
			SerializeModule_Core_Containers_Microsoft_WRL_ComPtr(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Containers_Microsoft(
			ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Containers_Microsoft_WRL_ComPtr(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Containers_Microsoft(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Containers_Microsoft_WRL_ComPtr(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek