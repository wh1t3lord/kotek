#include "../include/kotek_input.h"

namespace Kotek
{
	namespace Core
	{
		ktkInput::ktkInput(void) :
			m_mouse_x(0.0f), m_mouse_y(0.0f), m_mouse_sensitivity(0.1f),
			m_mouse_last_x(_kDefaultWindowSizeWidth /
				2.0f), // TODO: учитывать состояние пользователя здесь
			m_mouse_last_y(_kDefaultWindowSizeHeight / 2.0f)
		{
		}

		ktkInput::~ktkInput(void) {}

		void ktkInput::Initialize(void) {}

		void ktkInput::Shutdown(void) {}

		void ktkInput::SetMouseX(float value) noexcept
		{
			this->m_mouse_x = value;
		}
		float ktkInput::GetMouseX(void) const noexcept
		{
			return this->m_mouse_x;
		}
		void ktkInput::SetMouseY(float value) noexcept
		{
			this->m_mouse_y = value;
		}
		float ktkInput::GetMouseY(void) const noexcept
		{
			return this->m_mouse_y;
		}

		void ktkInput::SetMouseLastX(float value) noexcept
		{
			this->m_mouse_last_x = value;
		}

		float ktkInput::GetMouseLastX(void) const noexcept
		{
			return this->m_mouse_last_x;
		}

		void ktkInput::SetMouseLastY(float value) noexcept
		{
			this->m_mouse_last_y = value;
		}

		float ktkInput::GetMouseLastY(void) const noexcept
		{
			return this->m_mouse_last_y;
		}

		void ktkInput::SetMouseSensitivity(float value) noexcept
		{
			this->m_mouse_sensitivity = value;
		}

		float ktkInput::GetMouseSensitivity(void) const noexcept
		{
			return this->m_mouse_sensitivity;
		}

	} // namespace Core
} // namespace Kotek