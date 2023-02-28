#include "../include/kotek_ui_videoplayer.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI_VideoPlayer(Core::ktkMainManager* p_main_manager)
{
	InitializeModule_UI_VideoPlayer_AVIF(p_main_manager);

	return true;
}
bool ShutdownModule_UI_VideoPlayer(Core::ktkMainManager* p_main_manager)
{
	ShutdownModule_UI_VideoPlayer_AVIF(p_main_manager);


	return true;
}
bool SerializeModule_UI_VideoPlayer(Core::ktkMainManager* p_main_manager)
{
	SerializeModule_UI_VideoPlayer_AVIF(p_main_manager);

	return true;
}
bool DeserializeModule_UI_VideoPlayer(Core::ktkMainManager* p_main_manager)
{
	DeserializeModule_UI_VideoPlayer_AVIF(p_main_manager);


	return true;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
