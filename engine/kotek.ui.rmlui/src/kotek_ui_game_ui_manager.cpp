#include "../include/kotek_ui_game_ui_manager.h"

#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

#ifdef KOTEK_RMLUI_LIBRARY
	#include <RmlUi/Core.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkGameUI_RMLUI::ktkGameUI_RMLUI(void) {}

ktkGameUI_RMLUI::~ktkGameUI_RMLUI(void) {}

void ktkGameUI_RMLUI::Initialize(void) noexcept
{
#ifdef KOTEK_RMLUI_LIBRARY
	bool status = Rml::Initialise();

	KOTEK_ASSERT(status, "Can't initialize RmlUI library!");

	#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
//	Rml::SetSystemInterface();
	#elif KOTEK_USE_WINDOW_LIBRARY_SDL
	#endif
#endif
}

void ktkGameUI_RMLUI::Shutdown(void) noexcept
{
#ifdef KOTEK_RMLUI_LIBRARY
	Rml::Shutdown();
#endif
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
