#include "../include/kotek_component_geometry.h"
#include <kotek.core.main_manager/include/kotek_core_main_manager.h>

namespace Kotek
{
	namespace Game
	{
		namespace ecs
		{
			ktkComponentGeometry::ktkComponentGeometry(void) :
				m_vertex_count{}, m_index_count{}
			{
			}

			ktkComponentGeometry::~ktkComponentGeometry(void) {}

			Kotek::ktk::size_t ktkComponentGeometry::GetVertexCount(
				void) const noexcept
			{
				return this->m_vertex_count;
			}

			void ktkComponentGeometry::SetVertexCount(
				Kotek::ktk::size_t count) noexcept
			{
				this->m_vertex_count = count;
			}

			Kotek::ktk::size_t ktkComponentGeometry::GetIndexCount(
				void) const noexcept
			{
				return this->m_index_count;
			}

			void ktkComponentGeometry::SetIndexCount(
				Kotek::ktk::size_t count) noexcept
			{
				this->m_index_count = count;
			}

			const Kotek::ktk::string& ktkComponentGeometry::GetPath(
				void) const noexcept
			{
				return this->m_path;
			}

			void ktkComponentGeometry::SetPath(
				const Kotek::ktk::string& path) noexcept
			{
				this->m_path = path;
			}

			void ktkComponentGeometry::Clear(void) noexcept
			{
				this->m_index_count = {};
				this->m_vertex_count = {};
				this->m_path = "";
			}
			void ktkComponentGeometry::DrawImGui(
				Kotek::Core::ktkMainManager* main_manager) noexcept
			{
			}
		} // namespace ecs
	}     // namespace Game
} // namespace Kotek