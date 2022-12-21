#include "../include/kotek_component_model.h"

KOTEK_BEGIN_NAMESPACE_KOTEK

namespace Game
{
	namespace ecs
	{
		ktkComponentModel::ktkComponentModel(void) {}
		
		ktkComponentModel::~ktkComponentModel(void) {}
		
		void ktkComponentModel::Clear(void) noexcept {}

		void ktkComponentModel::DrawImGui(
			Kotek::Core::ktkMainManager* main_manager) noexcept
		{
		}
	} // namespace ecs
}

KOTEK_END_NAMESPACE_KOTEK