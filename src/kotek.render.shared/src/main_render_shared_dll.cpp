#include "../include/kotek_render_shared.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
bool InitializeModule_Render_Shared(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_BGFX
	KOTEK_INVOKE_MODULE(
		INIT, RENDER, InitializeModule_Render_Shared_BGFX, p_main_manager);
#endif

	return true;
}

bool ShutdownModule_Render_Shared(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_BGFX
	KOTEK_INVOKE_MODULE(
		SHUTDOWN, RENDER, ShutdownModule_Render_Shared_BGFX, p_main_manager);
#endif

	return true;
}
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
