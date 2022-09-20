#pragma once

#include <kotek.core.api/include/kotek_api.h>

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
		};
	}
} // namespace Kotek