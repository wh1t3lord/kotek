#include "../include/kotek_render_model.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_Model(Core::ktkMainManager* p_main_manager)
		{
			// TODO: create selection by console command and overriding for
			// format analyzer and loader and selection between cgltf and assimp
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