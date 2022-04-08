#include "kotek_render_graph_node.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			ktkRenderGraphNode::ktkRenderGraphNode(
				const ktk::string& render_pass_name,
				const ktk::unordered_map<ktk::string, shader_module_t*>&
					programs)
			{
			}

			ktkRenderGraphNode::ktkRenderGraphNode(void) {}
			ktkRenderGraphNode::~ktkRenderGraphNode(void) {}

			const shader_module_t* ktkRenderGraphNode::GetProgram(
				const ktk::string& program_name) const noexcept
			{
				if (program_name.empty()) 
				{
					KOTEK_ASSERT(false, "you can't pass an empty string");
					return nullptr;
				}

				if (this->m_programs.find(program_name) ==
					this->m_programs.end())
				{
					KOTEK_ASSERT(false, "can't find program by name: [{}]",
						program_name.get_as_is());
					return nullptr;
				}

				return this->m_programs.at(program_name);
			}

			const ktk::string& ktkRenderGraphNode::GetRenderPassName(
				void) const noexcept 
			{
				return this->m_render_pass_name;
			}

		} // namespace gl
	}     // namespace Render
} // namespace Kotek