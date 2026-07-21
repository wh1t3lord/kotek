#pragma once

#include <kotek.core.defines_dependent.ecs/include/kotek_core_defines_dependent_ecs.h>

#ifdef KOTEK_USE_ECS_BACKEND_ENTT
	#include <entt/entt.hpp>
#elif defined(KOTEK_USE_ECS_BACKEND_PICO)
	#include "pico_ecs.h"
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_ECS_BACKEND_ENTT
using view_entities_t = entt::basic_view<
	entt::get_t<entt::constness_as_t<
		entt::storage_type_t<
			entt::entity,
			entt::entity,
			std::allocator<entt::entity>>,
		const entt::entity>>,
	entt::exclude_t<>,
	void>;
using entity_t = entt::entity;
constexpr entity_t kInvalidECSEntity = entt::null;
#elif defined(KOTEK_USE_ECS_BACKEND_PICO)
using entity_t = ecs_entity_t;
inline const auto kInvalidECSEntity = ecs_invalid_entity();
#endif

KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE

#ifdef KOTEK_USE_ECS_BACKEND_ENTT
using view_entities_t = KUN_KOTEK KUN_KTK view_entities_t;
#elif defined(KOTEK_USE_ECS_BACKEND_PICO)
using entity_t = ecs_entity_t;
#endif

KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_ECS(ktkMainManager* p_manager);
bool SerializeModule_Core_ECS(ktkMainManager* p_manager);
bool DeserializeModule_Core_ECS(ktkMainManager* p_manager);
bool ShutdownModule_Core_ECS(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#include <kotek.core.format/include/kotek_core_format.h>

#ifdef KOTEK_USE_ECS_BACKEND_PICO
template <>
struct std::formatter<kun_kotek kun_ktk entity_t, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	inline auto format(
		kun_kotek kun_ktk entity_t const& entity, auto& ctx
	) const
	{
		return std::format_to(ctx.out(), "{}", entity.id);
	}
};
#elif defined(KOTEK_USE_ECS_BACKEND_ENTT)
	#error todo: provide impl
#endif

#include <kotek.core.utility/include/kotek_std_utility_variant.h>

#ifdef KOTEK_USE_ECS_BACKEND_PICO
inline bool
operator!=(const kun_kotek kun_ktk entity_t& left, const kun_kotek kun_ktk entity_t& right)
{
	return left.id != right.id;
}

inline bool
operator==(const kun_kotek kun_ktk entity_t& left, const kun_kotek kun_ktk entity_t& right)
{
	return left.id == right.id;
}

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

/// @brief \~english string->entity conversion for console
/// command argument parsing, entity id under pico is a dense
/// numeric index so it converts as a plain unsigned integer
template <>
inline entity_t convert_impl<entity_t>(
	std::string_view str, bool& status, custom_tag
)
{
	entity_t result = kInvalidECSEntity;

	result.id =
		convert_impl<ecs_id_t>(str, status, integral_tag{});

	return result;
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
#endif