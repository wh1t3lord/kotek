#pragma once

#include "kotek_render_graph_simplified_types.h"
#include "kotek_render_graph_simplified_types_input.h"
#include "kotek_render_graph_simplified_types_output.h"
#include "kotek_render_graph_simplified_render_pass.h"
#include "kotek_render_graph_simplified_builder.h"
#include "kotek_render_graph_simplified.h"


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