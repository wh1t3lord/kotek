#include "../include/kotek_core_log.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Log(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_BOOST_LIBRARY
// TODO: filter messages when you pass type through cmake like
// KOTEK_LOG_SEVERITY_LEVEL=info and will be generated preprocessor like
// KOTEK_USE_LOG_SEVERITY_LEVEL info
#endif

			return true;
		}

		bool SerializeModule_Core_Log(ktkMainManager* p_manager)
		{
			return true;
		}

		bool DeserializeModule_Core_Log(ktkMainManager* p_manager)
		{
			return true;
		}

		bool ShutdownModule_Core_Log(ktkMainManager* p_manager) { return true; }
	} // namespace Core
} // namespace Kotek
