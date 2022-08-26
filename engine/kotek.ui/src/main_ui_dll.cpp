#include "../include/kotek_ui.h"

namespace Kotek
{
	namespace UI
	{
		bool InitializeModule_UI(Core::ktkMainManager* p_main_manager)
		{
			InitializeModule_UI_IMGUI(p_main_manager);

			return true;
		}
		bool ShutdownModule_UI(Core::ktkMainManager* p_main_manager)
		{
			ShutdownModule_UI_IMGUI(p_main_manager);

			return true;
		}
		bool SerializeModule_UI(Core::ktkMainManager* p_main_manager)
		{
			SerializeModule_UI_IMGUI(p_main_manager);

			return true;
		}
		bool DeserializeModule_UI(Core::ktkMainManager* p_main_manager)
		{
			DeserializeModule_UI_IMGUI(p_main_manager);

			return true;
		}
	} // namespace UI
} // namespace Kotek
