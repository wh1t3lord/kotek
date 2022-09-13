#include "../include/kotek_render_graph_simplified_node.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderGraphSimplifiedNode::ktkRenderGraphSimplifiedNode(
				const ktk::string& render_pass_name,
				const ktk::unordered_map<ktk::string, ktkShaderModule*>&
					programs)
			{
			}

			ktkRenderGraphSimplifiedNode::ktkRenderGraphSimplifiedNode(void) {}
			ktkRenderGraphSimplifiedNode::~ktkRenderGraphSimplifiedNode(void) {}

			const ktkShaderModule* ktkRenderGraphSimplifiedNode::GetProgram(
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

			const ktk::string& ktkRenderGraphSimplifiedNode::GetRenderPassName(
				void) const noexcept 
			{
				return this->m_render_pass_name;
			}

		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek