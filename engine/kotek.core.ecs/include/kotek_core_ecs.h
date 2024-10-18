#pragma once

#include "kotek_component_allocator.h"

#include <kotek.core.defines_dependent.ecs/include/kotek_core_defines_dependent_ecs.h>

#include <entt/entt.hpp>

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK
using view_entities_t = entt::basic_view<entt::get_t<entt::constness_as_t<entt::storage_type_t<entt::entity,entt::entity,std::allocator<entt::entity>>,const entt::entity>>, entt::exclude_t<>, void>;
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE

using view_entities_t = KUN_KOTEK KUN_KTK view_entities_t;

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_ECS(ktkMainManager* p_manager);
bool SerializeModule_Core_ECS(ktkMainManager* p_manager);
bool DeserializeModule_Core_ECS(ktkMainManager* p_manager);
bool ShutdownModule_Core_ECS(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK