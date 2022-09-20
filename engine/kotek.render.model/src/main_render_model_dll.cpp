#include "../include/kotek_render_model.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_Model(Core::ktkMainManager* p_main_manager)
		{
			InitializeModule_Render_Model_CGLTF(p_main_manager);

			return true;
		}

		bool ShutdownModule_Render_Model(Core::ktkMainManager* p_main_manager)
		{
			ShutdownModule_Render_Model_CGLTF(p_main_manager);

			return true;
		}
	} // namespace Render
} // namespace Kotek