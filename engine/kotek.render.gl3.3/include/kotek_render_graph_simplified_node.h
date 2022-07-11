#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class shader_module_t;
		}
	} // namespace Render
} // namespace Kotek

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
					const ktk::unordered_map<ktk::string, shader_module_t*>&
						programs);
				ktkRenderGraphSimplifiedNode(void);
				~ktkRenderGraphSimplifiedNode(void);

				const shader_module_t* GetProgram(
					const ktk::string& program_name) const noexcept;

				const ktk::string& GetRenderPassName(void) const noexcept;

			private:
				ktk::unordered_map<ktk::string, shader_module_t*> m_programs;
				ktk::string m_render_pass_name;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek