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

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_Shared(Core::ktkMainManager*);
		bool ShutdownModule_Render_Shared(Core::ktkMainManager*);
	} // namespace Render
} // namespace Kotek