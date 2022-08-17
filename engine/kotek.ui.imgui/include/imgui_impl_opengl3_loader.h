#pragma once

#include <kotek.core.defines.static.render.gl/include/kotek_core_defines_static_render_gl.h>

#if (KOTEK_USE_OPENGL_MODERN_VERSION > 2)
	#include <kotek.render.gl.glad3.3/include/kotek_render_gl_glad3.h>
#endif

#if (KOTEK_USE_OPENGL_MODERN_VERSION > 3)
	#include <kotek.render.gl.glad4.6/include/kotek_render_gl_glad4.6.h>
#endif

int imgl3wInit(void)
{
	return 0;
}