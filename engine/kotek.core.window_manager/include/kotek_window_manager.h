#pragma once

#include <kotek.core.api/include/kotek_api.h>

namespace Kotek
{
	namespace Core
	{
		class ktkWindowManager : public ktkIWindowManager
		{
		public:
			ktkWindowManager(void);
			~ktkWindowManager(void);

			void Initialize(ktkIWindow* p_active_window) override;
			void Shutdown(void) override;

			void ActiveWindow_PollEvents(void) override;
			void* ActiveWindow_GetHandle(void) const noexcept override;
			int ActiveWindow_GetHeight(void) const noexcept override;
			int ActiveWindow_GetWidth(void) const noexcept override;
			bool ActiveWindow_ShouldToClose(void) override;

		private:
			ktkIWindow* m_p_active_window;
		};
	} // namespace Core
} // namespace Kotek