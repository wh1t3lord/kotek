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
			class ktkComponentTransform
			{
				KOTEK_COMPONENT(ktkComponentTransform)

			public:
				ktkComponentTransform(void);
				~ktkComponentTransform(void);

				const Kotek::ktk::math::vec3f_t& GetPosition(void) const noexcept;
				void SetPosition(const Kotek::ktk::math::vec3f_t& pos) noexcept;

				const Kotek::ktk::math::vec3f_t& GetScale(void) const noexcept;
				void SetScale(const Kotek::ktk::math::vec3f_t& scale) noexcept;
				
				const Kotek::ktk::math::quatf_t& GetRotation(void) const noexcept;
				void SetRotation(const Kotek::ktk::math::quatf_t& rot) noexcept;

				void Clear(void) noexcept;
				void DrawImGui(
					Kotek::Core::ktkMainManager* main_manager) noexcept;
				
			private:
				Kotek::ktk::math::vec3f_t m_position;
				Kotek::ktk::math::vec3f_t m_scale;
				Kotek::ktk::math::quatf_t m_rotation;
			};
		} // namespace ecs
	}     // namespace Game
} // namespace Sandbox