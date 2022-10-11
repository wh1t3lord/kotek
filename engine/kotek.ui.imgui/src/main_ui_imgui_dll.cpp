#include "../include/kotek_ui_imgui.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

bool InitializeModule_UI_IMGUI(Core::ktkMainManager* p_main_manager)
{
	p_main_manager->Set_ImguiWrapper(new UI::ktkImguiWrapper());

	return true;
}

bool ShutdownModule_UI_IMGUI(Core::ktkMainManager* p_main_manager)
{
	UI::ktkImguiWrapper* p_imgui_wrapper =
		dynamic_cast<UI::ktkImguiWrapper*>(p_main_manager->Get_ImguiWrapper());

	KOTEK_ASSERT(p_imgui_wrapper,
		"bad cast to UI::ktkImguiWrapper* it means you have differnt");

	delete p_imgui_wrapper;
	p_main_manager->Set_ImguiWrapper(nullptr);

	return true;
}

bool SerializeModule_UI_IMGUI(Core::ktkMainManager* p_main_manager)
{
	return true;
}

bool DeserializeModule_UI_IMGUI(Core::ktkMainManager* p_main_manager)
{
	return true;
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
