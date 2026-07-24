#include "../include/kotek_ui_game_ui_manager.h"

#ifdef KOTEK_USE_CEF_LIBRARY
namespace Kotek
{
	namespace UI
	{
		ktkGameUI_CEF::ktkGameUI_CEF(void) {}

		ktkGameUI_CEF::~ktkGameUI_CEF(void) {}

		void ktkGameUI_CEF::Initialize(void) noexcept {}

		void ktkGameUI_CEF::Shutdown(void) noexcept {}
	} // namespace UI
} // namespace Kotek
#endif
