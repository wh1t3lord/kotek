#pragma once

#include <kotek.core.profilers.cpu/include/kotek_core_profilers_cpu.h>
#include <kotek.core.profilers.gpu/include/kotek_core_profilers_gpu.h>

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
		bool InitializeModule_Core_Profilers(ktkMainManager* p_manager);
		bool SerializeModule_Core_Profilers(ktkMainManager* p_manager);
		bool DeserializeModule_Core_Profilers(ktkMainManager* p_manager);
		bool ShutdownModule_Core_Profilers(ktkMainManager* p_manager);
	} // namespace Core
} // namespace Kotek