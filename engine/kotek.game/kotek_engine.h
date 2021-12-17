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
	namespace Engine
	{
		bool initializeEngine(Core::ktkMainManager& main_manager);
		bool executeEngine(Core::ktkMainManager& main_manager);
		bool shutdownEngine(Core::ktkMainManager& main_manager);
		bool serializeEngine(void);
		bool deserializeEngine(void);
	} // namespace Engine
} // namespace Kotek
