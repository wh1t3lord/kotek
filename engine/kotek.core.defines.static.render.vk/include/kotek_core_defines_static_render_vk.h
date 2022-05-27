#pragma once

#include "kotek_std_preprocessors.h"

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
		bool InitializeModule_Core_Defines_Static_Render_Vulkan(
			ktkMainManager*);
		bool ShutdownModule_Core_Defines_Static_Render_Vulkan(ktkMainManager*);
		bool SerializeModule_Core_Defines_Static_Render_Vulkan(ktkMainManager*);
		bool DeserializeModule_Core_Defines_Static_Render_Vulkan(
			ktkMainManager*);
	} // namespace Core
} // namespace Kotek