#include "../include/kotek_core_os.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_OS(ktkMainManager* p_manager)
		{
			InitializeModule_Core_OS_Win32(p_manager);
			InitializeModule_Core_OS_Linux(p_manager);

			return true;
		}
		bool SerializeModule_Core_OS(ktkMainManager* p_manager) 
		{
			SerializeModule_Core_OS_Win32(p_manager);
			SerializeModule_Core_OS_Linux(p_manager);

			return true; 
		}

		bool DeserializeModule_Core_OS(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_OS_Win32(p_manager);
			DeserializeModule_Core_OS_Linux(p_manager);

			return true;
		}
		
		bool ShutdownModule_Core_OS(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_OS_Win32(p_manager);
			ShutdownModule_Core_OS_Linux(p_manager);

			return true; 
		}
	} // namespace Core
} // namespace Kotek
