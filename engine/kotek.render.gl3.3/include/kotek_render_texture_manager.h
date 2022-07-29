#pragma once

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			class ktkRenderTextureManager
			{
			public:
				ktkRenderTextureManager(Core::ktkMainManager* p_main_manager);
				~ktkRenderTextureManager(void);

				void Initialize(void);
				void Shutdown(void);

			private:
				Core::ktkMainManager* m_p_main_manager;
			};
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek