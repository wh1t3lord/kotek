#pragma once

#include "../kotek.core/kotek_std.h"

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
		bool InitializeModule_Render(Core::ktkMainManager& main_manager);
		bool ShutdownModule_Render(Core::ktkMainManager& main_manager);
	} // namespace Render
} // namespace Kotek