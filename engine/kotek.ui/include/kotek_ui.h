#pragma once

#include <kotek.ui.imgui/include/kotek_ui_imgui.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace UI
	{
		bool InitializeModule_UI(Core::ktkMainManager* p_main_manager);
		bool ShutdownModule_UI(Core::ktkMainManager* p_main_manager);
		bool SerializeModule_UI(Core::ktkMainManager* p_main_manager);
		bool DeserializeModule_UI(Core::ktkMainManager* p_main_manager);
	} // namespace UI
} // namespace Kotek
