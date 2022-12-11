#pragma once

#include <kotek.core.defines.static.render.gl/include/kotek_core_defines_static_render_gl.h>

#ifdef KOTEK_USE_OPENGL
	#ifdef KOTEK_GLAD_PREPROCESSOR_VISIBILITY
		#include <glad/glad.h>
	#endif
#endif

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED
	#ifdef kotek_render_gl_glad_EXPORTS
		#define KOTEK_RENDER_GL_GLAD_API __declspec(dllexport)
	#else
		#define KOTEK_RENDER_GL_GLAD_API __declspec(dllimport)
	#endif
#else
	#ifdef kotek_render_gl_glad_EXPORTS
		#define KOTEK_RENDER_GL_GLAD_API
	#else
		#define KOTEK_RENDER_GL_GLAD_API
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK