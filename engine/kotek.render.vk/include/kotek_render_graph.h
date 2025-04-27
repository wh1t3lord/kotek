#pragma once

#include "kotek_render_graph_data_types.h"

namespace Kotek
{
	namespace Core
	{
		class ktkProfiler;
		class ktkIRenderResourceManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class ktkRenderGraphRenderPass;
			class kotek_render_command_list_ring;
			class ktkRenderDevice;
		} // namespace vk
	}     // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			// TODO: implement recreation of render graph and its resource
			// manager
			// UPD: maybe we don't need it, but think about what I wrote in TODO
			class ktkRenderGraph : public Core::ktkIRenderGraph
			{
			public:
				ktkRenderGraph(
					const ktk::vector<ktkRenderGraphRenderPass*>& passes,
					const ktk::vector<ktkRenderGraphNode>& nodes,
					kotek_render_command_list_ring* p_command_list_ring,
					ktkRenderDevice* p_device,
					Core::ktkProfiler* p_profiler);

				ktkRenderGraph(void);
				~ktkRenderGraph(void);

				void Initialize(kun_core ktkMainManager* p_main_manager, kun_core ktkIRenderResourceManager* p_resource_manager) override;
				bool Is_Initialized(void) const noexcept override;
				void Shutdown(void) override;

				void UpdateAll(void);
				void RenderAll(void);

				ktk::uint32_t GetNodesCount(void) const noexcept;
				
				kotek_render_command_list_ring* GetCommandListRing(
					void) const noexcept;

			private:
				ktk::vector<ktkRenderGraphRenderPass*> m_passes;
				ktk::vector<ktkRenderGraphNode> m_nodes;
				kotek_render_command_list_ring* m_p_command_list_ring;
				ktkRenderDevice* m_p_render_device;
				Core::ktkProfiler* m_p_profiler;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek