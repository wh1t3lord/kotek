#pragma once

#include <kotek.core.enum.core/include/kotek_core_enum_core.h>
#include <kotek.core.enum.render/include/kotek_core_enum_render.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Enum(ktkMainManager* p_manager);
bool ShutdownModule_Core_Enum(ktkMainManager* p_manager);
bool SerializeModule_Core_Enum(ktkMainManager* p_manager);
bool DeserializeModule_Core_Enum(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
