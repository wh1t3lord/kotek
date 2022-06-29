#include "../include/kotek_core_engine_config.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Engine_Config(ktkMainManager* p_manager)
		{
			ktkEngineConfig* p_instance = new ktkEngineConfig();
			p_instance->Initialize();

			p_manager->Set_EngineConfig(p_instance);

			return true;
		}

		bool SerializeModule_Core_Engine_Config(ktkMainManager* p_manager)
		{
			return true;
		}

		bool DeserializeModule_Core_Engine_Config(ktkMainManager* p_manager)
		{
			return true;
		}

		bool ShutdownModule_Core_Engine_Config(ktkMainManager* p_manager)
		{
			ktkEngineConfig* p_instance =
				dynamic_cast<ktkEngineConfig*>(p_manager->Get_EngineConfig());

			KOTEK_ASSERT(p_instance,
				"failed to cast to ktkEngineConfig. You must have a valid "
			    "instance of it, otherwise something is wrong");

			p_instance->Shutdown();
			delete p_instance;

			return true;
		}
	} // namespace Core
} // namespace Kotek
