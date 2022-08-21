#include "../include/kotek_core_window_glfw.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
			p_manager->Get_WindowManager()->Initialize(new ktkWindow());
#endif
			return true;
		}

		bool ShutdownModule_Core_Window_GLFW(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
#endif		

			return true;
		}

		bool SerializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW

#endif
			return true;
		}

		bool DeserializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW

#endif
			return true;
		}
	} // namespace Core
} // namespace Kotek
