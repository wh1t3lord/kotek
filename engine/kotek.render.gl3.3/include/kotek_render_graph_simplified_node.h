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
					const ktk::unordered_map<ktk::string, ktkShaderModule*>&
						programs);
				ktkRenderGraphSimplifiedNode(void);
				~ktkRenderGraphSimplifiedNode(void);

				const ktkShaderModule* GetProgram(
					const ktk::string& program_name) const noexcept;

				const ktk::string& GetRenderPassName(void) const noexcept;

			private:
				ktk::unordered_map<ktk::string, ktkShaderModule*> m_programs;
				ktk::string m_render_pass_name;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek