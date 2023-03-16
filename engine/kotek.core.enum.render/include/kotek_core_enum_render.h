#pragma once

#include <kotek.core.defines.static.render/include/kotek_core_defines_render.h>

#ifdef KOTEK_USE_DIRECTX
	#include <kotek.core.enum.render.dx/include/kotek_core_enum_render_dx.h>
#endif

#ifdef KOTEK_USE_OPENGL
	#include <kotek.core.enum.render.gl/include/kotek_core_enum_render_gl.h>
#endif

#ifdef KOTEK_USE_VULKAN
	#include <kotek.core.enum.render.vk/include/kotek_core_enum_render_vk.h>
#endif

#include "kotek_enum.h"
#include "kotek_translation.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Enum_Render(ktkMainManager* p_manager);
bool ShutdownModule_Core_Enum_Render(ktkMainManager* p_manager);
bool SerializeModule_Core_Enum_Render(ktkMainManager* p_manager);
bool DeserializeModule_Core_Enum_Render(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK