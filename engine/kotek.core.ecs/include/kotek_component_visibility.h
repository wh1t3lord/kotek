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
			class ktkComponentVisibility
			{
				KOTEK_COMPONENT(ktkComponentVisibility)

			public:
				ktkComponentVisibility(void);
				~ktkComponentVisibility(void);

				void SetVisible(bool is_visible) noexcept;

				bool GetVisible(void) const noexcept;

				void Clear(void) noexcept;
				void DrawImGui(
					Kotek::Core::ktkMainManager* main_manager) noexcept;

			private:
				bool m_is_visible;
			};
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek