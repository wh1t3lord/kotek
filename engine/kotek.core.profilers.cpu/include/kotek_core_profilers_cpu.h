#pragma once

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

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
		bool InitializeModule_Core_Profilers_CPU(ktkMainManager* p_manager);
		bool SerializeModule_Core_Profilers_CPU(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Profilers_CPU(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Profilers_CPU(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek