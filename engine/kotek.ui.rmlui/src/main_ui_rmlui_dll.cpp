#include "../include/kotek_ui_rmlui.h"

#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI_RMLUI(Core::ktkMainManager* p_main_manager)
{
	if (p_main_manager->Get_Splash())
	{
		p_main_manager->Get_Splash()->Set_Text("[ui]: init [rmlui]");
		p_main_manager->Get_Splash()->Set_Progress();
	}

#ifdef KOTEK_USE_RMLUI_LIBRARY
	KOTEK_ASSERT(
		p_main_manager, "you can't pass an invalid pointer to ktkMainManager");

	if (p_main_manager)
	{
		p_main_manager->Set_GameUIEngine(new ktkGameUI_RMLUI());
	}
#endif

	return true;
}

bool ShutdownModule_UI_RMLUI(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY
	KOTEK_ASSERT(
		p_main_manager, "you can't pass an invalid pointer to ktkMainManager");

	if (p_main_manager)
	{
		Core::ktkIGameUIManager* p_manager = p_main_manager->Get_GameUIEngine();

		ktkGameUI_RMLUI* p_casted = dynamic_cast<ktkGameUI_RMLUI*>(p_manager);

		KOTEK_ASSERT(p_casted, "can't cast to ktkGameUI_RMLUI* instance!");

		delete p_casted;
		p_main_manager->Set_GameUIEngine(nullptr);
	}
#endif

	return true;
}

bool SerializeModule_UI_RMLUI(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY

#endif

	return true;
}

bool DeserializeModule_UI_RMLUI(Core::ktkMainManager* p_main_manager)
{
#ifdef KOTEK_USE_RMLUI_LIBRARY

#endif

	return true;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
