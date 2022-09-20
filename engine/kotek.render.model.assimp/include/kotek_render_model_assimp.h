#pragma once

#include "kotek_model.h"

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
		bool InitializeModule_Render_Model_ASSIMP(
			Core::ktkMainManager* p_main_manager);

		bool ShutdownModule_Render_Model_ASSIMP(
			Core::ktkMainManager* p_main_manager);
	} // namespace Render
} // namespace Kotek