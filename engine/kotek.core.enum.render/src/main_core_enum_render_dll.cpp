#include "../include/kotek_core_enum_render.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Enum_Render(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_DIRECTX
			InitializeModule_Core_Enum_Render_DX(p_manager);
#endif

#ifdef KOTEK_USE_OPENGL
			InitializeModule_Core_Enum_Render_GL(p_manager);
#endif

#ifdef KOTEK_USE_VULKAN
			InitializeModule_Core_Enum_Render_VK(p_manager);
#endif

			return true;
		}

		bool ShutdownModule_Core_Enum_Render(ktkMainManager* p_manager)
		{
#ifdef KOTEK_USE_DIRECTX
			ShutdownModule_Core_Enum_Render_DX(p_manager);
#endif

#ifdef KOTEK_USE_OPENGL
			ShutdownModule_Core_Enum_Render_GL(p_manager);
#endif

#ifdef KOTEK_USE_VULKAN
			ShutdownModule_Core_Enum_Render_VK(p_manager);
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

			return true;
		}
	} // namespace Core
} // namespace Kotek