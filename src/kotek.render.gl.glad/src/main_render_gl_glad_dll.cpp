#include "../include/kotek_render_gl_glad.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

int Initialize_Glad(GLADloadproc p_proc)
{
	return gladLoadGLLoader(p_proc);
}

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK