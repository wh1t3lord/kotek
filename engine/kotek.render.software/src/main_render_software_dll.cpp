#include "../include/kotek_render_software.h"

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_Software(Core::ktkMainManager* p_main_manager)
		{
			KOTEK_MESSAGE("render module is initialized");

			return true;
		}

		bool ShutdownModule_Render_Software(Core::ktkMainManager* p_main_manager)
		{
			return true;
		}
	} // namespace Render
} // namespace Kotek