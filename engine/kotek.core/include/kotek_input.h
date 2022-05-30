#pragma once

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

			void SetMouseX(float value) noexcept;
			float GetMouseX(void) const noexcept;

			void SetMouseY(float value) noexcept;
			float GetMouseY(void) const noexcept;

			void SetMouseLastX(float value) noexcept;
			float GetMouseLastX(void) const noexcept;

			void SetMouseLastY(float value) noexcept;
			float GetMouseLastY(void) const noexcept;

			void SetMouseSensitivity(float value) noexcept;
			float GetMouseSensitivity(void) const noexcept;

		private:
			float m_mouse_last_x;
			float m_mouse_last_y;
			float m_mouse_x;
			float m_mouse_y;
			float m_mouse_sensitivity;
		};
	} // namespace Core
} // namespace Kotek
