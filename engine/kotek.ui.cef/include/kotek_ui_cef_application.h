#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_CEF_LIBRARY
	#include <include/cef_app.h>
	#include <include/cef_client.h>

namespace Kotek
{
	namespace UI
	{
		class ktkCEFApplication : public CefApp, public CefRenderProcessHandler
		{
		public:
			ktkCEFApplication(void);

			CefRefPtr<CefRenderProcessHandler>
			GetRenderProcessHandler() override
			{
				return this;
			}

			void OnWebKitInitialized() override;

			IMPLEMENT_REFCOUNTING(ktkCEFApplication);
		};
	} // namespace UI
} // namespace Kotek
#endif