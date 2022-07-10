#pragma once

#include "kotek_render_graph_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraph : public Core::ktkIRenderGraph
			{
			public:
				ktkRenderGraph(void);
				~ktkRenderGraph(void);

				void Initialize(void) override;
				void Shutdown(void) override;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek