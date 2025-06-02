#include "../include/kotek_ui_videoplayer_avif.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI_VideoPlayer_AVIF(Core::ktkMainManager* p_main_manager)
{
	if (p_main_manager)
	{
		if (p_main_manager->Get_Splash())
		{
			p_main_manager->Get_Splash()->Set_Text(
				"[ui]: init [videoplayer][avif]");
			p_main_manager->Get_Splash()->Set_Progress();
		}
	}

	return true;
}
bool ShutdownModule_UI_VideoPlayer_AVIF(Core::ktkMainManager* p_main_manager)
{
	return true;
}
bool SerializeModule_UI_VideoPlayer_AVIF(Core::ktkMainManager* p_main_manager)
{
	return true;
}
bool DeserializeModule_UI_VideoPlayer_AVIF(Core::ktkMainManager* p_main_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
