#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class shader_module_t;
		}
	} // namespace Render
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		namespace gl
		{
			class ktkRenderGraphNode
			{
			public:
				ktkRenderGraphNode(const ktk::string& render_pass_name,
					const ktk::unordered_map<ktk::string, shader_module_t*>&
						programs);
				ktkRenderGraphNode(void);
				~ktkRenderGraphNode(void);

				const shader_module_t* GetProgram(
					const ktk::string& program_name) const noexcept;

				const ktk::string& GetRenderPassName(void) const noexcept;

			private:
				ktk::unordered_map<ktk::string, shader_module_t*> m_programs;
				ktk::string m_render_pass_name;
			};
		} // namespace gl
	}     // namespace Render
} // namespace Kotek