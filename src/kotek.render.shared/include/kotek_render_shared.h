#pragma once

#ifdef KOTEK_USE_BGFX
	#include <kotek.render.shared.bgfx/include/kotek_render_shared_bgfx.h>
#endif

#include "kotek_render_data_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
bool InitializeModule_Render_Shared(Core::ktkMainManager*);
bool ShutdownModule_Render_Shared(Core::ktkMainManager*);
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK