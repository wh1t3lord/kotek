#pragma once

#include <kotek.core.window.glfw/include/kotek_core_window_glfw.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Window(ktkMainManager* p_manager);
bool SerializeModule_Core_Window(ktkMainManager* p_manager);
bool DeserializeModule_Core_Window(ktkMainManager* p_manager);
bool ShutdownModule_Core_Window(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
