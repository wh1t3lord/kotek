#include "../include/kotek_render_graph_simplified_node.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	ktkRenderGraphSimplifiedNode::ktkRenderGraphSimplifiedNode(
		const ktk::ustring& render_pass_name,
		const ktk::unordered_map<ktk::ustring, GLuint>* const programs,
		const ktk::unordered_map<ktk::cstring, ktkBufferModule>* const
			buffers) :
		m_p_programs{programs},
		m_p_buffers{buffers}, m_render_pass_name{render_pass_name}
	{
		KOTEK_ASSERT(this->m_p_programs,
			"you have to initialize this field with valid pointer");
	}

	ktkRenderGraphSimplifiedNode::ktkRenderGraphSimplifiedNode(void) :
		m_p_programs{}, m_p_buffers{}
	{
	}

	ktkRenderGraphSimplifiedNode::~ktkRenderGraphSimplifiedNode(void) {}

	GLuint ktkRenderGraphSimplifiedNode::Get_Program(
		const ktk::ustring& program_name) const KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		KOTEK_ASSERT(
			program_name.empty() == false, "you can't pass an empty string");

		KOTEK_ASSERT(this->m_p_programs,
			"you must initialize programs map! Probably you don't use any "
			"shaders in render graph pass and it is pointless to create a such "
			"pass!");

		KOTEK_ASSERT(
			this->m_p_programs->find(program_name) != this->m_p_programs->end(),
			"can't find program by name: [{}]",
			reinterpret_cast<const char*>(program_name.c_str()));

		return this->m_p_programs->at(program_name);
	}

	const ktkBufferModule& ktkRenderGraphSimplifiedNode::Get_Buffer(
		const ktk::cstring& buffer_name) const KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		KOTEK_ASSERT(buffer_name.empty() == false,
			"you can't pass an empty buffer name");

		KOTEK_ASSERT(this->m_p_buffers,
			"you have to add some buffer when you initialize render graph, "
			"because the map is nullptr");

		KOTEK_ASSERT(
			this->m_p_buffers->find(buffer_name) != this->m_p_buffers->end(),
			"can't find buffer by its name: [{}]", buffer_name);

		return this->m_p_buffers->at(buffer_name);
	}

	const ktk::ustring& ktkRenderGraphSimplifiedNode::Get_RenderPassName(
		void) const KOTEK_CPP_KEYWORD_NOEXCEPT
	{
		return this->m_render_pass_name;
	}

} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK
