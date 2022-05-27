#include "../include/kotek_core_defines_render.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Defines_Static_Render(
			ktkMainManager* p_manager)
		{
			InitializeModule_Core_Defines_Static_Render_DirectX(p_manager);
			InitializeModule_Core_Defines_Static_Render_OpenGL(p_manager);
			InitializeModule_Core_Defines_Static_Render_Vulkan(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Defines_Static_Render(
			ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Defines_Static_Render_DirectX(p_manager);
			ShutdownModule_Core_Defines_Static_Render_OpenGL(p_manager);
			ShutdownModule_Core_Defines_Static_Render_Vulkan(p_manager);

			return true;
		}

		bool SerializeModule_Core_Defines_Static_Render(
			ktkMainManager* p_manager)
		{
			SerializeModule_Core_Defines_Static_Render_DirectX(p_manager);
			SerializeModule_Core_Defines_Static_Render_OpenGL(p_manager);
			SerializeModule_Core_Defines_Static_Render_Vulkan(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Defines_Static_Render(
			ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Defines_Static_Render_DirectX(p_manager);
			DeserializeModule_Core_Defines_Static_Render_OpenGL(p_manager);
			DeserializeModule_Core_Defines_Static_Render_Vulkan(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek
