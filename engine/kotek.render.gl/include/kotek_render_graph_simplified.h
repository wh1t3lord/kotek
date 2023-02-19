#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_CORE
class ktkIRenderGraph;
KOTEK_END_NAMESPACE_CORE

KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphSimplifiedRenderPass;
	class ktkRenderGraphSimplifiedNode;
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphSimplified : public Core::ktkIRenderGraph
	{
	public:
		ktkRenderGraphSimplified(
			const ktk::vector<ktkRenderGraphSimplifiedRenderPass*>& passes,
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
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
