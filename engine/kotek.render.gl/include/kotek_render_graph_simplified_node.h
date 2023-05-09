#pragma once

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
KOTEK_BEGIN_NAMESPACE_RENDER_GL

class ktkRenderGraphSimplifiedNode
{
public:
	ktkRenderGraphSimplifiedNode(const ktk::string& render_pass_name,
		const ktk::unordered_map<ktk::string, GLuint>* const programs,
		const ktk::unordered_map<ktk::cstring, ktkBufferModule>* const buffers);

	ktkRenderGraphSimplifiedNode(void);

	~ktkRenderGraphSimplifiedNode(void);

	GLuint Get_Program(
		const ktk::string& program_name) const KOTEK_CPP_KEYWORD_NOEXCEPT;

	const ktkBufferModule& Get_Buffer(
		const ktk::cstring& buffer_name) const KOTEK_CPP_KEYWORD_NOEXCEPT;

	const ktk::string& Get_RenderPassName(
		void) const KOTEK_CPP_KEYWORD_NOEXCEPT;

private:
	const ktk::unordered_map<ktk::string, GLuint>* m_p_programs;
	const ktk::unordered_map<ktk::cstring, ktkBufferModule>* m_p_buffers;

	ktk::string m_render_pass_name;
};

KOTEK_END_NAMESPACE_RENDER_GL
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK