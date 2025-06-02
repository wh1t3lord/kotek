#include "../include/kotek_render_shared.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
bool InitializeModule_Render_Shared(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_DIRECTX
	InitializeModule_Render_Shared_DX(p_main_manager);
#endif

#ifdef KOTEK_USE_OPENGL
	InitializeModule_Render_Shared_GL(p_main_manager);
#endif

#ifdef KOTEK_USE_VULKAN
	InitializeModule_Render_Shared_VK(p_main_manager);
#endif
	return true;
}

bool ShutdownModule_Render_Shared(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_DIRECTX
	ShutdownModule_Render_Shared_DX(p_main_manager);
#endif

#ifdef KOTEK_USE_OPENGL
	ShutdownModule_Render_Shared_GL(p_main_manager);
#endif

#ifdef KOTEK_USE_VULKAN
	ShutdownModule_Render_Shared_VK(p_main_manager);
#endif

	return true;
}
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK