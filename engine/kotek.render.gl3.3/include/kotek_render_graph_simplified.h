#pragma once

namespace Kotek
{
	namespace Core
	{
		class ktkIRenderGraph;
	}

	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraphSimplifiedRenderPass;
			class ktkRenderGraphSimplifiedNode;
		} // namespace gl3_3
	}     // namespace Render
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
				ktkRenderGraphSimplified(
					const ktk::vector<ktkRenderGraphSimplifiedRenderPass*>&
						passes,
					const ktk::vector<ktkRenderGraphSimplifiedNode>& nodes);

				ktkRenderGraphSimplified(void);
				~ktkRenderGraphSimplified(void);

				void Initialize(void) override;
				void Shutdown(void) override;

				void Update_All(void);
				void Render_All(void);

			private:
				ktk::vector<ktkRenderGraphSimplifiedRenderPass*> m_passes;
				ktk::vector<ktkRenderGraphSimplifiedNode> m_nodes;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek