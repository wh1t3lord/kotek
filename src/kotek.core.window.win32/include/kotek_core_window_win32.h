#pragma once

/// \file kotek_core_window_win32.h
/// \~english own no-dependency Win32 window backend module (task K17) —
/// selected with -DKOTEK_WINDOW_LIBRARY=WIN32 (GLFW stays the default)

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Window_WIN32(ktkMainManager* p_manager);
bool ShutdownModule_Core_Window_WIN32(ktkMainManager* p_manager);
bool SerializeModule_Core_Window_WIN32(ktkMainManager* p_manager);
bool DeserializeModule_Core_Window_WIN32(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
