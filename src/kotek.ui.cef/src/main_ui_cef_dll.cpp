#include "../include/kotek_ui_cef.h"

#ifdef KOTEK_USE_CEF_LIBRARY
	#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#endif

namespace Kotek
{
	namespace UI
	{
		bool InitializeModule_UI_CEF(Core::ktkMainManager* p_main_manager)
		{
#ifdef KOTEK_USE_CEF_LIBRARY
			p_main_manager->Set_GameUIEngine(new ktkGameUI_CEF);
#endif

			return true;
		}

		bool ShutdownModule_UI_CEF(Core::ktkMainManager* p_main_manager)
		{
#ifdef KOTEK_USE_CEF_LIBRARY
			ktkGameUI_CEF* p_engine = dynamic_cast<ktkGameUI_CEF*>(p_main_manager->Get_GameUIEngine());
#endif

			return true;
		}

		bool SerializeModule_UI_CEF(Core::ktkMainManager* p_main_manager)
		{
#ifdef KOTEK_USE_CEF_LIBRARY

#endif

			return true;
		}

		bool DeserializeModule_UI_CEF(Core::ktkMainManager* p_main_manager)
		{
#ifdef KOTEK_USE_CEF_LIBRARY

#endif

			return true;
		}
	} // namespace UI
} // namespace Kotek
