#include "../include/kotek_component_input.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Game
	{
		namespace ecs
		{
			ktkComponentInput::ktkComponentInput(void) :
				m_position_mouse_x(0.0f), m_position_mouse_y(0.0f),
				m_offset_mouse_position_x(0.0f),
				m_offset_mouse_position_y(0.0f),
				m_position_mouse_previous_x(0.0f),
				m_position_mouse_previous_y(0.0f)
			{
			}

			ktkComponentInput::~ktkComponentInput(void) {}

			float ktkComponentInput::GetPositionMouseX(void) const noexcept
			{
				return this->m_position_mouse_x;
			}

			float ktkComponentInput::GetPositionMouseY(void) const noexcept
			{
				return this->m_position_mouse_y;
			}

			void ktkComponentInput::SetPositionMouseX(float value) noexcept
			{
				this->m_position_mouse_x = value;
			}

			void ktkComponentInput::SetPositionMouseY(float value) noexcept
			{
				this->m_position_mouse_y = value;
			}

			float ktkComponentInput::GetOffsetMousePositionX(
				void) const noexcept
			{
				return this->m_offset_mouse_position_x;
			}
			float ktkComponentInput::GetOffsetMousePositionY(
				void) const noexcept
			{
				return this->m_offset_mouse_position_y;
			}

			void ktkComponentInput::SetOffsetMousePositionX(
				float value) noexcept
			{
				this->m_offset_mouse_position_x = value;
			}

			void ktkComponentInput::SetOffsetMousePositionY(
				float value) noexcept
			{
				this->m_offset_mouse_position_y = value;
			}

			float ktkComponentInput::GetPositionMousePreviousX(
				void) const noexcept
			{
				return this->m_position_mouse_previous_x;
			}

			float ktkComponentInput::GetPositionMousePreviousY(
				void) const noexcept
			{
				return this->m_position_mouse_previous_y;
			}

			void ktkComponentInput::SetPositionMousePreviousX(
				float value) noexcept
			{
				this->m_position_mouse_previous_x = value;
			}

			void ktkComponentInput::SetPositionMousePreviousY(
				float value) noexcept
			{
				this->m_position_mouse_previous_y = value;
			}

			void ktkComponentInput::Clear(void) noexcept
			{
				this->m_position_mouse_x = 0.0f;
				this->m_position_mouse_y = 0.0f;
			}
			void ktkComponentInput::DrawImGui(
				Kotek::Core::ktkMainManager* main_manager) noexcept
			{
			}
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek