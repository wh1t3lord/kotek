#pragma once

#include "../kotek.core/kotek_std.h"
#include "kotek_render_graph_types.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraph : public Core::ktkIRenderGraph
			{
			public:
				ktkRenderGraph(void);
				~ktkRenderGraph(void);

				void Initialize(void) override;
				void Shutdown(void) override;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek