#pragma once

#include <kotek.ui.imgui/include/kotek_ui_imgui.h>

#ifdef KOTEK_USE_CEF_LIBRARY
	#include <kotek.ui.cef/include/kotek_ui_cef.h>
#elif defined(KOTEK_USE_RMLUI_LIBRARY)
	#include <kotek.ui.rmlui/include/kotek_ui_rmlui.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI(Core::ktkMainManager* p_main_manager);
bool ShutdownModule_UI(Core::ktkMainManager* p_main_manager);
bool SerializeModule_UI(Core::ktkMainManager* p_main_manager);
bool DeserializeModule_UI(Core::ktkMainManager* p_main_manager);

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK