#pragma once

#include "kotek_enum.h"

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
		bool InitializeModule_Core_Enum_Render_GL(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Enum_Render_GL(ktkMainManager* p_manager);
		bool SerializeModule_Core_Enum_Render_GL(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Enum_Render_GL(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek