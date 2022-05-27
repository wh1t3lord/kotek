#pragma once

#include <kotek.core.defines.static.render.dx/include/kotek_core_defines_static_render_dx.h>
#include <kotek.core.defines.static.render.gl/include/kotek_core_defines_static_render_gl.h>
#include <kotek.core.defines.static.render.vk/include/kotek_core_defines_static_render_vk.h>

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Defines_Static_Render(ktkMainManager*);
		bool ShutdownModule_Core_Defines_Static_Render(ktkMainManager*);
		bool SerializeModule_Core_Defines_Static_Render(ktkMainManager*);
		bool DeserializeModule_Core_Defines_Static_Render(ktkMainManager*);
	}
} // namespace Kotek