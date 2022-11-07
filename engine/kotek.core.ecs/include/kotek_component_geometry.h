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
			class ktkComponentGeometry
			{
				KOTEK_COMPONENT(ktkComponentGeometry)

			public:
				ktkComponentGeometry(void);
				~ktkComponentGeometry(void);

				Kotek::ktk::size_t GetVertexCount(void) const noexcept;
				void SetVertexCount(Kotek::ktk::size_t count) noexcept;

				Kotek::ktk::size_t GetIndexCount(void) const noexcept;
				void SetIndexCount(Kotek::ktk::size_t count) noexcept;

				const Kotek::ktk::string& GetPath(void) const noexcept;
				void SetPath(const Kotek::ktk::string& path) noexcept;

				void Clear(void) noexcept;
				void DrawImGui(
					Kotek::Core::ktkMainManager* main_manager) noexcept;

			private:
				Kotek::ktk::size_t m_vertex_count;
				Kotek::ktk::size_t m_index_count;
				Kotek::ktk::string m_path;
			};
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek