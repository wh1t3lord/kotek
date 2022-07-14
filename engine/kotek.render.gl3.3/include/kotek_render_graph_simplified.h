#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraphSimplified : public Core::ktkIRenderGraph
			{
			public:
				ktkRenderGraphSimplified(void);
				~ktkRenderGraphSimplified(void);

				void Initialize(void) override;
				void Shutdown(void) override;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek