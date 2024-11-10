#pragma once

#include "kotek_render_graph_simplified_types.h"
#include "kotek_render_graph_simplified_types_input.h"
#include "kotek_render_graph_simplified_types_output.h"
#include "kotek_render_data_types.h"
#include "kotek_render_format.h"

#ifdef KOTEK_DEBUG
	#define KOTEK_GL_ASSERT()                                            \
		{                                                                \
			auto stat = glGetError();                                    \
			KOTEK_ASSERT(stat == GL_NO_ERROR, "[GL/GLES][ERROR]: {}", (int)stat); \
		}
#else
	#define KOTEK_GL_ASSERT()
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER

bool InitializeModule_Render_Shared_GL(Core::ktkMainManager*);
bool ShutdownModule_Render_Shared_GL(Core::ktkMainManager*);

KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
