#include "../include/kotek_core_resource_manager_loader.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

namespace Kotek
{
	namespace Core
	{
		bool InitializeModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
		{
			KOTEK_ASSERT(p_manager->GetResourceManager(),
				"you must initialize resource manager before calling this "
			    "function!");

			p_manager->GetResourceManager()->Set_ResourceLoader(new ktkResourceLoaderManager());

			return true;
		}

		bool SerializeModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
		{
			return true;
		}

		bool DeserializeModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
		{
			return true;
		}

		bool ShutdownModule_Core_Resource_Manager_Loader(ktkMainManager* p_manager)
		{
			KOTEK_ASSERT(p_manager->GetResourceManager(),
				"you must have an initialized instance of ktkResourceManager "
			    "(ktkIResourceManager)");

			ktkResourceLoaderManager* p_instance =
				dynamic_cast<ktkResourceLoaderManager*>(
					p_manager->GetResourceManager()->Get_ResourceLoader());

			KOTEK_ASSERT(p_instance,
				"you must get a valid casted instance of ktkResourceManager. "
			    "Otherwise it means you got a different type at all!!");

			delete p_instance;
			p_manager->GetResourceManager()->Set_ResourceLoader(nullptr);

			return true;
		}
	} // namespace Core
} // namespace Kotek