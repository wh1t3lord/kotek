#pragma once

#include <kotek.ui.imgui/include/kotek_ui_imgui.h>

#ifdef KOTEK_USE_CEF_LIBRARY
	#include <kotek.ui.cef/include/kotek_ui_cef.h>
#endif

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
