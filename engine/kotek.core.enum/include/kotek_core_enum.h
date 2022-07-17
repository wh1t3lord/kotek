#pragma once

#include <kotek.core.enum.core/include/kotek_core_enum_core.h>
#include <kotek.core.enum.render/include/kotek_core_enum_render.h>

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
		bool InitializeModule_Core_Enum(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Enum(ktkMainManager* p_manager);
		bool SerializeModule_Core_Enum(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Enum(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek