#pragma once

#include <kotek.core.defines.static.render.dx/include/kotek_core_defines_static_render_dx.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

#if KOTEK_USE_DIRECTX_VERSION > 6
	#include "kotek_enum_7.h"
#endif

#if KOTEK_USE_DIRECTX_VERSION > 7
	#include "kotek_enum_8.h"
#endif

#if KOTEK_USE_DIRECTX_VERSION > 8
	#include "kotek_enum_9.h"
#endif

#if KOTEK_USE_DIRECTX_VERSION > 9
	#include "kotek_enum_10.h"
#endif

#if KOTEK_USE_DIRECTX_VERSION > 10
	#include "kotek_enum_11.h"
#endif

#if KOTEK_USE_DIRECTX_VERSION > 11
	#include "kotek_enum_12.h"
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Enum_Render_DX(ktkMainManager* p_manager);
bool ShutdownModule_Core_Enum_Render_DX(ktkMainManager* p_manager);
bool SerializeModule_Core_Enum_Render_DX(ktkMainManager* p_manager);
bool DeserializeModule_Core_Enum_Render_DX(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK