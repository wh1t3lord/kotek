#pragma once

#include "../kotek.core/kotek_std.h"
#include "kotek_render_graph_data_types.h"

namespace Kotek
{
	namespace Core
	{
		class ktkProfiler;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace vk
		{
			class kotek_render_graph_render_pass;
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
			class kotek_render_graph : public Core::kotek_i_render_graph
			{
			public:
				kotek_render_graph(
					const ktk::vector<kotek_render_graph_render_pass*>& passes,
					const ktk::vector<ktkRenderGraphNode>& nodes,
					kotek_render_command_list_ring* p_command_list_ring,
					ktkRenderDevice* p_device,
					Core::ktkProfiler* p_profiler);

				kotek_render_graph(void);
				~kotek_render_graph(void);

				void initialize(void);
				void shutdown(void);
				void UpdateAll(void);
				void RenderAll(void);

				ktk::uint32_t GetNodesCount(void) const noexcept;
				
				kotek_render_command_list_ring* GetCommandListRing(
					void) const noexcept;

			private:
				ktk::vector<kotek_render_graph_render_pass*> m_passes;
				ktk::vector<ktkRenderGraphNode> m_nodes;
				kotek_render_command_list_ring* m_p_command_list_ring;
				ktkRenderDevice* m_p_render_device;
				Core::ktkProfiler* m_p_profiler;
			};
		} // namespace vk
	}     // namespace Render
} // namespace Kotek