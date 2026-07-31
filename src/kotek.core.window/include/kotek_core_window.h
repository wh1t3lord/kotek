#pragma once

// BOTH backend umbrellas are included unconditionally: they are
// declaration-only (no third-party headers), and guarding them on
// KOTEK_USE_WINDOW_LIBRARY_* is fragile — an earlier transitive include of
// this umbrella (before the defines copy that sets the flag) makes the
// pragma-once block permanent and the backend declarations vanish from
// every later TU (observed: GLFW branch compiled with no declaration in
// scope). The #if in main_core_window_dll.cpp selects the call; the
// inactive backend's module simply is not linked.

#include <kotek.core.window.glfw/include/kotek_core_window_glfw.h>
#include <kotek.core.window.win32/include/kotek_core_window_win32.h>

#include "kotek_window_console.h"

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
