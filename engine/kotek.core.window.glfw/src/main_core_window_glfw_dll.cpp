#include "../include/kotek_core_window_glfw.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Window_GLFW(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
			p_manager->Set_Window(new ktkWindow());
#endif
			return true;
		}

		bool ShutdownModule_Core_Window_GLFW(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
			ktkWindow* p_window = dynamic_cast<ktkWindow*>(p_manager->Get_Window());

			KOTEK_ASSERT(p_window,
				"you passed unknown type, because dynamic_cast return nullptr "
			    "of ktkWindow* type. Bad cast!");

			p_window->Shutdown();

			delete p_window;
			p_manager->Set_Window(nullptr);
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
