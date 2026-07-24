#pragma once

#include <kotek.core.constants.math/include/kotek_core_constants_math.h>
#include <kotek.core.constants.ecs/include/kotek_core_constants_ecs.h>
#include <kotek.core.constants.string/include/kotek_core_constants_string.h>
#include <kotek.core.constants.window/include/kotek_core_constants_window.h>
#include <kotek.core.constants.render/include/kotek_core_constants_render.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Constants(ktkMainManager*);
bool ShutdownModule_Core_Constants(ktkMainManager*);
bool SerializeModule_Core_Constants(ktkMainManager*);
bool DeserializeModule_Core_Constants(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK