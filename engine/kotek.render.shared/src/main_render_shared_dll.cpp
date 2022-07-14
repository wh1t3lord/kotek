#include "../include/kotek_render_shared.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_Shared(
			Core::ktkMainManager* p_main_manager)
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
	} // namespace Render
} // namespace Kotek