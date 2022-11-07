#pragma once

#include <kotek.core.math/include/kotek_core_math.h>
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
			class ktkComponentCamera
			{
				KOTEK_COMPONENT(ktkComponentCamera)

			public:
				ktkComponentCamera(void);
				~ktkComponentCamera(void);

				float GetYaw(void) const noexcept;
				void SetYaw(float value) noexcept;

				float GetPitch(void) const noexcept;
				void SetPitch(float value) noexcept;

				float GetPlaneNear(void) const noexcept;
				void SetPlaneNear(float value) noexcept;

				float GetPlaneFar(void) const noexcept;
				void SetPlaneFar(float value) noexcept;

				float GetFieldOfView(void) const noexcept;
				void SetFieldOfView(float value) noexcept;

				const Kotek::ktk::math::vec3f_t& GetFront(void) const noexcept;
				void SetFront(const Kotek::ktk::math::vec3f_t& vector) noexcept;

				const Kotek::ktk::math::vec3f_t& GetUp(void) const noexcept;
				void SetUp(const Kotek::ktk::math::vec3f_t& vector) noexcept;

				float GetMouseSensetivity(void) const noexcept;
				void SetMouseSensetivity(float value) noexcept;

				void Clear(void) noexcept;
				void DrawImGui(
					Kotek::Core::ktkMainManager* main_manager) noexcept;

			private:
				float m_plane_near;
				float m_plane_far;
				float m_fov;
				float m_yaw;
				float m_pitch;
				float m_mouse_sensetivity;
				Kotek::ktk::math::vec3f_t m_front;
				Kotek::ktk::math::vec3f_t m_up;
			};
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek