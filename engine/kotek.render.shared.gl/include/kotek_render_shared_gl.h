#pragma once

#include "kotek_render_graph_simplified_types.h"
#include "kotek_render_graph_simplified_types_input.h"
#include "kotek_render_graph_simplified_types_output.h"
#include "kotek_render_data_types.h"

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