#include "../include/kotek_core_window.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Window(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Window_GLFW(p_manager);

			return true;
		}

		bool SerializeModule_Core_Window(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Window_GLFW(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Window(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Window_GLFW(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Window(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Window_GLFW(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek
