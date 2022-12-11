#include "../include/kotek_render_graph_simplified_node.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderGraphSimplifiedNode::ktkRenderGraphSimplifiedNode(
		const ktk::string& render_pass_name,
		const ktk::unordered_map<ktk::string, GLuint>* const programs) :
		m_p_programs{programs},
		m_render_pass_name{render_pass_name}
	{
		KOTEK_ASSERT(this->m_p_programs,
			"you have to initialize this field with valid pointer");
	}

	ktkRenderGraphSimplifiedNode::ktkRenderGraphSimplifiedNode(void) :
		m_p_programs{}
	{
	}

	ktkRenderGraphSimplifiedNode::~ktkRenderGraphSimplifiedNode(void) {}

	GLuint ktkRenderGraphSimplifiedNode::Get_Program(
		const ktk::string& program_name) const noexcept
	{
		KOTEK_ASSERT(
			program_name.empty() == false, "you can't pass an empty string");

		KOTEK_ASSERT(
			this->m_p_programs->find(program_name) != this->m_p_programs->end(),
			"can't find program by name: [{}]", program_name);

		return this->m_p_programs->at(program_name);
	}

	const ktk::string& ktkRenderGraphSimplifiedNode::Get_RenderPassName(
		void) const noexcept
	{
		return this->m_render_pass_name;
	}

} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK