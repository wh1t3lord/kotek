#pragma once

#include "kotek_render_format.h"
#include "kotek_render_data_types.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_Shared_BGFX(kun_core ktkMainManager*);
bool ShutdownModule_Render_Shared_BGFX(kun_core ktkMainManager*);

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
