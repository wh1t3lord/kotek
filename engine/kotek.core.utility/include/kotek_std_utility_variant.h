#pragma once

#include <kotek.core.containers.variant\include\kotek_core_containers_variant.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename T>
struct is_variant : std::false_type
{
};

template <typename... Types>
struct is_variant<std::variant<Types...>> : std::true_type
{
};

template <typename T>
inline constexpr bool is_variant_v = is_variant<T>::value;

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK