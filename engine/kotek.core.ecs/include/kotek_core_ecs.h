#pragma once

#include "kotek_component_allocator.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
	}
} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_ECS(ktkMainManager* p_manager);
		bool SerializeModule_Core_ECS(ktkMainManager* p_manager);
		bool DeserializeModule_Core_ECS(ktkMainManager* p_manager);
		bool ShutdownModule_Core_ECS(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek
