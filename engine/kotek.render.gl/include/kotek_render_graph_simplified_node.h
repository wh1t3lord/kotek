#pragma once

#include <kotek.render.gl.glad/include/kotek_render_gl_glad.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_RENDER
namespace gl
{
	class ktkRenderGraphSimplifiedNode
	{
	public:
		ktkRenderGraphSimplifiedNode(const ktk::string& render_pass_name,
			const ktk::unordered_map<ktk::string, GLuint>* const programs);

		ktkRenderGraphSimplifiedNode(void);

		~ktkRenderGraphSimplifiedNode(void);

		GLuint Get_Program(const ktk::string& program_name) const noexcept;

		const ktk::string& Get_RenderPassName(void) const noexcept;

	private:
		const ktk::unordered_map<ktk::string, GLuint>* m_p_programs;

		ktk::string m_render_pass_name;
	};
} // namespace gl
KOTEK_END_NAMESPACE_RENDER
KOTEK_END_NAMESPACE_KOTEK