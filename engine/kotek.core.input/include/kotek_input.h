#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.constants.window/include/kotek_core_constants_window.h>

namespace Kotek
{
	namespace Core
	{
		class ktkInput : public ktkIInput
		{
		public:
			ktkInput(void);
			~ktkInput(void);

			void Initialize(void) override;
			void Shutdown(void) override;

			void SetMouseX(float value) noexcept override;
			float GetMouseX(void) const noexcept override;

			void SetMouseY(float value) noexcept override;
			float GetMouseY(void) const noexcept override;

			void SetMouseLastX(float value) noexcept override;
			float GetMouseLastX(void) const noexcept override;

			void SetMouseLastY(float value) noexcept override;
			float GetMouseLastY(void) const noexcept override;

			void SetMouseSensitivity(float value) noexcept override;
			float GetMouseSensitivity(void) const noexcept override;

		private:
			float m_mouse_last_x;
			float m_mouse_last_y;
			float m_mouse_x;
			float m_mouse_y;
			float m_mouse_sensitivity;
		};
	} // namespace Core
} // namespace Kotek
