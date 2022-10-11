#pragma once

#ifdef KOTEK_USE_OPENGL
	#include <kotek.render.shared.gl/include/kotek_render_shared_gl.h>
#endif

#ifdef KOTEK_USE_VULKAN
	#include <kotek.render.shared.vk/include/kotek_render_shared_vk.h>
#endif

#ifdef KOTEK_USE_DIRECTX
	#include <kotek.render.shared.dx/include/kotek_render_shared_dx.h>
#endif

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