#include "../include/kotek_component_camera.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Game
	{
		namespace ecs
		{
			ktkComponentCamera::ktkComponentCamera(void) :
				m_plane_near(0.1f), m_plane_far(1000.0f), m_fov(60.0f),
				m_yaw(-90.0f), m_pitch(0.0f), m_mouse_sensetivity(0.5f),
				m_front(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f)
			{
			}

			ktkComponentCamera::~ktkComponentCamera(void) {}

			float ktkComponentCamera::GetYaw(void) const noexcept
			{
				return this->m_yaw;
			}

			void ktkComponentCamera::SetYaw(float value) noexcept
			{
				this->m_yaw = value;
			}

			float ktkComponentCamera::GetPitch(void) const noexcept
			{
				return this->m_pitch;
			}

			void ktkComponentCamera::SetPitch(float value) noexcept
			{
				this->m_pitch = value;
			}

			float ktkComponentCamera::GetPlaneNear(void) const noexcept
			{
				return this->m_plane_near;
			}

			void ktkComponentCamera::SetPlaneNear(float value) noexcept
			{
				this->m_plane_near = value;
			}

			float ktkComponentCamera::GetPlaneFar(void) const noexcept
			{
				return this->m_plane_far;
			}

			void ktkComponentCamera::SetPlaneFar(float value) noexcept
			{
				this->m_plane_far = value;
			}

			float ktkComponentCamera::GetFieldOfView(void) const noexcept
			{
				return this->m_fov;
			}

			void ktkComponentCamera::SetFieldOfView(float value) noexcept
			{
				this->m_fov = value;
			}

			const Kotek::ktk::math::vec3f_t& ktkComponentCamera::GetFront(
				void) const noexcept
			{
				return this->m_front;
			}

			void ktkComponentCamera::SetFront(
				const Kotek::ktk::math::vec3f_t& vector) noexcept
			{
				this->m_front = vector;
			}

			const Kotek::ktk::math::vec3f_t& ktkComponentCamera::GetUp(
				void) const noexcept
			{
				return this->m_up;
			}

			void ktkComponentCamera::SetUp(
				const Kotek::ktk::math::vec3f_t& vector) noexcept
			{
				this->m_up = vector;
			}

			float ktkComponentCamera::GetMouseSensetivity(void) const noexcept
			{
				return this->m_mouse_sensetivity;
			}

			void ktkComponentCamera::SetMouseSensetivity(float value) noexcept
			{
				this->m_mouse_sensetivity = value;
			}

			void ktkComponentCamera::Clear(void) noexcept
			{
				this->m_plane_near = 0.1f;
				this->m_plane_far = 1000.0f;
				this->m_fov = 60.0f;
				this->m_yaw = -90.0f;
				this->m_pitch = 0.0f;
				this->m_mouse_sensetivity = 0.0f;
				this->m_front = {0.0f, 0.0f, -1.0f};
				this->m_up = {0.0f, 1.0f, 0.0f};
			}

			void ktkComponentCamera::DrawImGui(
				Kotek::Core::ktkMainManager* main_manager) noexcept
			{
			}
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek