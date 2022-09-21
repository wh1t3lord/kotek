#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include "kotek_ui_cef_application.h"




#ifdef KOTEK_USE_CEF_LIBRARY
namespace Kotek
{
	namespace UI
	{
		class ktkGameUI_CEF : public Core::ktkIGameUIManager
		{
		public:
			ktkGameUI_CEF(void);
			~ktkGameUI_CEF(void);

			void Initialize(void) noexcept override;
			void Shutdown(void) noexcept override;

		private:
			CefMainArgs m_cef_args;
			CefRefPtr<ktkCEFApplication> m_p_application;
		};
	} // namespace UI
} // namespace Kotek
#endif
