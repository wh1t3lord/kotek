#pragma once

#include "kotek_loader.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Render
	{
		bool InitializeModule_Render_Model_CGLTF(
			Core::ktkMainManager* p_main_manager);

		bool ShutdownModule_Render_Model_CGLTF(
			Core::ktkMainManager* p_main_manager);
	} // namespace Render
} // namespace Kotek