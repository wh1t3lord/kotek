#pragma once

#include "kotek_ui_game_ui_manager.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI_RMLUI(Core::ktkMainManager* p_main_manager);
bool ShutdownModule_UI_RMLUI(Core::ktkMainManager* p_main_manager);
bool SerializeModule_UI_RMLUI(Core::ktkMainManager* p_main_manager);
bool DeserializeModule_UI_RMLUI(Core::ktkMainManager* p_main_manager);

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK