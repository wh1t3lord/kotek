#include "../include/kotek_ui.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI(Core::ktkMainManager* p_main_manager)
{
	if (p_main_manager->Get_Splash())
	{
		p_main_manager->Get_Splash()->Set_Text("[ui]: init");
		p_main_manager->Get_Splash()->Set_Progress();
	}

	InitializeModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
	InitializeModule_UI_CEF(p_main_manager);
#elif defined(KOTEK_USE_RMLUI_LIBRARY)
	InitializeModule_UI_RMLUI(p_main_manager);
#endif

	InitializeModule_UI_VideoPlayer(p_main_manager);

	return true;
}
bool ShutdownModule_UI(Core::ktkMainManager* p_main_manager)
{
	ShutdownModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
	ShutdownModule_UI_CEF(p_main_manager);
#elif defined(KOTEK_USE_RMLUI_LIBRARY)
	ShutdownModule_UI_RMLUI(p_main_manager);
#endif

	ShutdownModule_UI_VideoPlayer(p_main_manager);

	return true;
}
bool SerializeModule_UI(Core::ktkMainManager* p_main_manager)
{
	SerializeModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
	SerializeModule_UI_CEF(p_main_manager);
#elif defined(KOTEK_USE_RMLUI_LIBRARY)
	SerializeModule_UI_RMLUI(p_main_manager);
#endif

	SerializeModule_UI_VideoPlayer(p_main_manager);

	return true;
}
bool DeserializeModule_UI(Core::ktkMainManager* p_main_manager)
{
	DeserializeModule_UI_IMGUI(p_main_manager);

#ifdef KOTEK_USE_CEF_LIBRARY
	DeserializeModule_UI_CEF(p_main_manager);
#elif defined(KOTEK_USE_RMLUI_LIBRARY)
	DeserializeModule_UI_RMLUI(p_main_manager);
#endif

	DeserializeModule_UI_VideoPlayer(p_main_manager);

	return true;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
