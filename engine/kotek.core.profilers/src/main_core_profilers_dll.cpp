#include "../include/kotek_core_profilers.h"

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Profilers(ktkMainManager* p_manager)
		{
			InitializeModule_Core_Profilers_CPU(p_manager);
			InitializeModule_Core_Profilers_GPU(p_manager);

			return true;
		}

		bool SerializeModule_Core_Profilers(ktkMainManager* p_manager)
		{
			SerializeModule_Core_Profilers_CPU(p_manager);
			SerializeModule_Core_Profilers_GPU(p_manager);

			return true;
		}

		bool DeserializeModule_Core_Profilers(ktkMainManager* p_manager)
		{
			DeserializeModule_Core_Profilers_CPU(p_manager);
			DeserializeModule_Core_Profilers_GPU(p_manager);

			return true;
		}

		bool ShutdownModule_Core_Profilers(ktkMainManager* p_manager)
		{
			ShutdownModule_Core_Profilers_CPU(p_manager);
			ShutdownModule_Core_Profilers_GPU(p_manager);

			return true;
		}
	} // namespace Core
} // namespace Kotek
