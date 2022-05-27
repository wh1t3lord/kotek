#include "../include/kotek_api.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_API(ktkMainManager* p_manager)
		{
			// not used really

			return true;
		}

		bool SerializeModule_Core_API(ktkMainManager* p_manager)
		{
			return true;
		}

		bool DeserializeModule_Core_API(ktkMainManager* p_manager)
		{
			return true;
		}

		bool ShutdownModule_Core_API(ktkMainManager* p_manager) { return true; }
	} // namespace Core
} // namespace Kotek