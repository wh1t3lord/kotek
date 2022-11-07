#include "../include/kotek_component_visibility.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Game
	{
		namespace ecs
		{
			ktkComponentVisibility::ktkComponentVisibility(void) :
				m_is_visible(true)
			{
			}

			ktkComponentVisibility::~ktkComponentVisibility(void) {}

			void ktkComponentVisibility::SetVisible(bool is_visible) noexcept
			{
				this->m_is_visible = is_visible;
			}

			bool ktkComponentVisibility::GetVisible(void) const noexcept
			{
				return this->m_is_visible;
			}

			void ktkComponentVisibility::Clear(void) noexcept
			{
				this->m_is_visible = true;
			}

			void ktkComponentVisibility::DrawImGui(
				Kotek::Core::ktkMainManager* main_manager) noexcept
			{
				Kotek::Core::ktkIImguiWrapper* p_wrapper_imgui =
					main_manager->Get_ImguiWrapper();

				if (p_wrapper_imgui->CollapsingHeader("Component Visibility"))
				{
					p_wrapper_imgui->Checkbox(
						"visibility", &this->m_is_visible);
				}
			}
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek