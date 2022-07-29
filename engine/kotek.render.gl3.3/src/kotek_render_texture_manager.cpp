#include "../include/kotek_render_texture_manager.h"

namespace Kotek
{
	namespace Render
	{
		namespace gl3_3
		{
			ktkRenderTextureManager::ktkRenderTextureManager(
				Core::ktkMainManager* p_main_manager) :
				m_p_main_manager{p_main_manager}
			{
			}

			ktkRenderTextureManager::~ktkRenderTextureManager(void) {}

			void Initialize(void) {}
			void Shutdown(void) {}
		} // namespace gl3_3
	}     // namespace Render
} // namespace Kotek