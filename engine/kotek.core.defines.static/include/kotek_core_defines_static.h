#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.defines.static.git/include/kotek_core_defines_static_git.h>
#include <kotek.core.defines.static.math/include/kotek_core_defines_static_math.h>
#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.profilers/include/kotek_core_defines_static_profilers.h>
#include <kotek.core.defines.static.sdk/include/kotek_core_defines_static_sdk.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>
#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>
#include <kotek.core.defines.static.render/include/kotek_core_defines_render.h>

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
		bool InitializeModule_Core_Defines_Static(ktkMainManager*);
		bool ShutdownModule_Core_Defines_Static(ktkMainManager*);
		bool SerializeModule_Core_Defines_Static(ktkMainManager*);
		bool DeserializeModule_Core_Defines_Static(ktkMainManager*);
	} // namespace Core
} // namespace Kotek