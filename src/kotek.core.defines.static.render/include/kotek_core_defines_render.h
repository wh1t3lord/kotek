#pragma once

#include <kotek.core.defines.static.render.dx/include/kotek_core_defines_static_render_dx.h>
#include <kotek.core.defines.static.render.gl/include/kotek_core_defines_static_render_gl.h>
#include <kotek.core.defines.static.render.vk/include/kotek_core_defines_static_render_vk.h>
#include <kotek.core.defines.static.render.bgfx/include/kotek_core_defines_static_render_bgfx.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Defines_Static_Render(ktkMainManager*);
bool ShutdownModule_Core_Defines_Static_Render(ktkMainManager*);
bool SerializeModule_Core_Defines_Static_Render(ktkMainManager*);
bool DeserializeModule_Core_Defines_Static_Render(ktkMainManager*);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK