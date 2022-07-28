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
		namespace gl3_3
		{
			class ktkRenderGraphSimplified : public Core::ktkIRenderGraph
			{
			public:
				ktkRenderGraphSimplified(void);
				~ktkRenderGraphSimplified(void);

				void Initialize(void) override;
				void Shutdown(void) override;

				void Update_All(void);
				void Render_All(void);
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek