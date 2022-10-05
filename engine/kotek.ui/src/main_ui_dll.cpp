#include "../include/kotek_ui.h"

namespace Kotek
{
	namespace UI
	{
		bool InitializeModule_UI(Core::ktkMainManager* p_main_manager)
		{
			InitializeModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
			InitializeModule_UI_CEF(p_main_manager);
#endif

			return true;
		}
		bool ShutdownModule_UI(Core::ktkMainManager* p_main_manager)
		{
			ShutdownModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
			ShutdownModule_UI_CEF(p_main_manager);
#endif

			return true;
		}
		bool SerializeModule_UI(Core::ktkMainManager* p_main_manager)
		{
			SerializeModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
			SerializeModule_UI_CEF(p_main_manager);
#endif

			return true;
		}
		bool DeserializeModule_UI(Core::ktkMainManager* p_main_manager)
		{
			DeserializeModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
			DeserializeModule_UI_CEF(p_main_manager);
#endif

			return true;
		}
	} // namespace UI
} // namespace Kotek
