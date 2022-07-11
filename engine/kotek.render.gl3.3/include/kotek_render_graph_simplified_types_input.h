#pragma once

#include "kotek_render_graph_simplified_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			// TODO: move to shared resources like in shared project, because implementation will be the same and will just shrink 
			class ktkRenderGraphSimplifiedStorageInput
			{
			public:
				ktkRenderGraphSimplifiedStorageInput(void);
				~ktkRenderGraphSimplifiedStorageInput(void);

				void AddImage(const ktk::string& image_name);
			};
		}
	} // namespace Render
} // namespace Kotek