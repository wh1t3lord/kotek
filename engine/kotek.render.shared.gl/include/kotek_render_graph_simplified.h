#pragma once

namespace Kotek
{
	namespace Core
	{
		class ktkIRenderGraph;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraphSimplified : public Core::ktkIRenderGraph
			{
			public:
				ktkRenderGraphSimplified(void);
				~ktkRenderGraphSimplified(void);

				void Initialize(void) override;
				void Shutdown(void) override;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek