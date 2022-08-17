#pragma once

#include "kotek_render_graph_simplified_types.h"
#include "kotek_render_graph_simplified_types_input.h"
#include "kotek_render_graph_simplified_types_output.h"

#if (KOTEK_USE_OPENGL_MODERN_VERSION > 2)
#include <kotek.render.gl.glad3.3/include/kotek_render_gl_glad3.h>
#endif

#if (KOTEK_USE_OPENGL_MODERN_VERSION > 3)
#include <kotek.render.gl.glad4.6/include/kotek_render_gl_glad4.6.h>
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
		bool InitializeModule_Render_Shared_GL(Core::ktkMainManager*);
		bool ShutdownModule_Render_Shared_GL(Core::ktkMainManager*);
	} // namespace Render
} // namespace Kotek