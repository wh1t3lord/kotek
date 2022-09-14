#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderGraphSimplifiedNode
			{
			public:
				ktkRenderGraphSimplifiedNode(
					const ktk::string& render_pass_name,
					const ktk::unordered_map<ktk::string, GLuint>* const
						programs);

				ktkRenderGraphSimplifiedNode(void);

				~ktkRenderGraphSimplifiedNode(void);

				GLuint Get_Program(
					const ktk::string& program_name) const noexcept;

				const ktk::string& Get_RenderPassName(void) const noexcept;

			private:
				const ktk::unordered_map<ktk::string, GLuint>* const
					m_p_programs;

				ktk::string m_render_pass_name;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek