#include "../include/kotek_component_transform.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Game
	{
		namespace ecs
		{
			ktkComponentTransform::ktkComponentTransform(void) :
				m_position(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f),
				m_rotation(0.0f, 0.0f, 0.0f, 1.0f)
			{
			}

			ktkComponentTransform::~ktkComponentTransform(void) {}

			const Kotek::ktk::math::vec3f_t& ktkComponentTransform::GetPosition(
				void) const noexcept
			{
				return this->m_position;
			}

			void ktkComponentTransform::SetPosition(
				const Kotek::ktk::math::vec3f_t& pos) noexcept
			{
				this->m_position = pos;
			}

			const Kotek::ktk::math::vec3f_t& ktkComponentTransform::GetScale(
				void) const noexcept
			{
				return this->m_scale;
			}

			void ktkComponentTransform::SetScale(
				const Kotek::ktk::math::vec3f_t& scale) noexcept
			{
				this->m_scale = scale;
			}

			const Kotek::ktk::math::quatf_t& ktkComponentTransform::GetRotation(
				void) const noexcept
			{
				return this->m_rotation;
			}

			void ktkComponentTransform::SetRotation(
				const Kotek::ktk::math::quatf_t& rot) noexcept
			{
				this->m_rotation = rot;
			}

			void ktkComponentTransform::Clear(void) noexcept
			{
				this->m_position = Kotek::ktk::math::vec3f_t();
				this->m_rotation = Kotek::ktk::math::quatf_t();
				this->m_scale = Kotek::ktk::math::vec3f_t();
			}

			void ktkComponentTransform::DrawImGui(
				Kotek::Core::ktkMainManager* main_manager) noexcept
			{
				Kotek::Core::ktkIImguiWrapper* p_wrapper_imgui =
					main_manager->Get_ImguiWrapper();

				if (p_wrapper_imgui)
				{
					if (p_wrapper_imgui->CollapsingHeader(
							"Component Transform"))
					{
						p_wrapper_imgui->EditDragVec3f(
							"position", &this->m_position);
						p_wrapper_imgui->EditDragVec3f("scale", &this->m_scale);
						p_wrapper_imgui->EditDragQuatf(
							"rotation", &this->m_rotation);
					}
				}
			}
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek