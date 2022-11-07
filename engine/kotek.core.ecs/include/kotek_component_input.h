#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.defines_dependent.ecs/include/kotek_core_defines_dependent_ecs.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
class ktkMainManager;
KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

namespace Kotek
{
	namespace Game
	{
		namespace ecs
		{
			class ktkComponentInput
			{
				KOTEK_COMPONENT(ktkComponentInput)

			public:
				ktkComponentInput(void);
				~ktkComponentInput(void);

				float GetPositionMouseX(void) const noexcept;

				float GetPositionMouseY(void) const noexcept;

				void SetPositionMouseX(float value) noexcept;

				void SetPositionMouseY(float value) noexcept;

				float GetOffsetMousePositionX(void) const noexcept;

				float GetOffsetMousePositionY(void) const noexcept;

				void SetOffsetMousePositionX(float value) noexcept;

				void SetOffsetMousePositionY(float value) noexcept;

				float GetPositionMousePreviousX(void) const noexcept;

				float GetPositionMousePreviousY(void) const noexcept;

				void SetPositionMousePreviousX(float value) noexcept;

				void SetPositionMousePreviousY(float value) noexcept;

				void Clear(void) noexcept;
				void DrawImGui(
					Kotek::Core::ktkMainManager* main_manager) noexcept;

			private:
				float m_position_mouse_x;
				float m_position_mouse_y;
				float m_position_mouse_previous_x;
				float m_position_mouse_previous_y;
				float m_offset_mouse_position_x;
				float m_offset_mouse_position_y;
			};
		} // namespace ecs
	}     // namespace Game
} // namespace Sandbox