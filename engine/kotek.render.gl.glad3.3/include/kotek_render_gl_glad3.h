#pragma once

#include <kotek.core.defines.static.render.gl/include/kotek_core_defines_static_render_gl.h>

#ifdef KOTEK_USE_OPENGL
	#if KOTEK_USE_OPENGL_MODERN_VERSION > 2
		#include "glad/glad.h"
	#endif
#endif