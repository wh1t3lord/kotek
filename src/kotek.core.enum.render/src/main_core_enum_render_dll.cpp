#include "../include/kotek_core_enum_render.h"
#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
bool InitializeModule_Core_Enum_Render(ktkMainManager* p_manager)
{
	if (p_manager->Get_Splash())
	{
		p_manager->Get_Splash()->Set_Text("[core]: init [enum][render]");
		p_manager->Get_Splash()->Set_Progress();
	}

#ifdef KOTEK_USE_DIRECTX
	KOTEK_INVOKE_MODULE_INIT(InitializeModule_Core_Enum_Render_DX, p_manager);
#endif

#ifdef KOTEK_USE_OPENGL
	KOTEK_INVOKE_MODULE_INIT(InitializeModule_Core_Enum_Render_GL, p_manager);
#endif

#ifdef KOTEK_USE_VULKAN
	KOTEK_INVOKE_MODULE_INIT(InitializeModule_Core_Enum_Render_VK, p_manager);
#endif

#ifdef KOTEK_USE_BGFX
	KOTEK_INVOKE_MODULE_INIT(InitializeModule_Core_Enum_Render_BGFX, p_manager);
#endif

	return true;
}

bool ShutdownModule_Core_Enum_Render(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_DIRECTX
	KOTEK_INVOKE_MODULE_SHUTDOWN(ShutdownModule_Core_Enum_Render_DX, p_manager);
#endif

#ifdef KOTEK_USE_OPENGL
	KOTEK_INVOKE_MODULE_SHUTDOWN(ShutdownModule_Core_Enum_Render_GL, p_manager);
#endif

#ifdef KOTEK_USE_VULKAN
	KOTEK_INVOKE_MODULE_SHUTDOWN(ShutdownModule_Core_Enum_Render_VK, p_manager);
#endif

#ifdef KOTEK_USE_BGFX
	KOTEK_INVOKE_MODULE_SHUTDOWN(ShutdownModule_Core_Enum_Render_BGFX, p_manager);
#endif

	return true;
}

bool SerializeModule_Core_Enum_Render(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_DIRECTX
	SerializeModule_Core_Enum_Render_DX(p_manager);
#endif

#ifdef KOTEK_USE_OPENGL
	SerializeModule_Core_Enum_Render_GL(p_manager);
#endif

#ifdef KOTEK_USE_VULKAN
	SerializeModule_Core_Enum_Render_VK(p_manager);
#endif

#ifdef KOTEK_USE_BGFX
	SerializeModule_Core_Enum_Render_BGFX(p_manager);
#endif

	return true;
}

bool DeserializeModule_Core_Enum_Render(ktkMainManager* p_manager)
{
#ifdef KOTEK_USE_DIRECTX
	DeserializeModule_Core_Enum_Render_DX(p_manager);
#endif

#ifdef KOTEK_USE_OPENGL
	DeserializeModule_Core_Enum_Render_GL(p_manager);
#endif

#ifdef KOTEK_USE_VULKAN
	DeserializeModule_Core_Enum_Render_VK(p_manager);
#endif

#ifdef KOTEK_USE_BGFX
	DeserializeModule_Core_Enum_Render_BGFX(p_manager);
#endif

	return true;
}
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK