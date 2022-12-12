#pragma once

#include <kotek.core.enum.core/include/kotek_core_enum_core.h>
#include <kotek.core.enum.render/include/kotek_core_enum_render.h>

#include <type_traits>

// unary ~operator
template <typename Enum,
	typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr inline Enum& operator~(Enum& val)
{
	val = static_cast<Enum>(~static_cast<std::underlying_type_t<Enum>>(val));
	return val;
}

// & operator
template <typename Enum,
	typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr inline Enum operator&(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) &
		static_cast<std::underlying_type_t<Enum>>(rhs));
}

// &= operator
template <typename Enum,
	typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr inline Enum operator&=(Enum& lhs, Enum rhs)
{
	lhs = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) &
		static_cast<std::underlying_type_t<Enum>>(rhs));
	return lhs;
}

//| operator

template <typename Enum,
	typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr inline Enum operator|(Enum lhs, Enum rhs)
{
	return static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) |
		static_cast<std::underlying_type_t<Enum>>(rhs));
}
//|= operator

template <typename Enum,
	typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr inline Enum& operator|=(Enum& lhs, Enum rhs)
{
	lhs = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(lhs) |
		static_cast<std::underlying_type_t<Enum>>(rhs));
	return lhs;
}

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

bool InitializeModule_Core_Enum(ktkMainManager* p_manager);
bool ShutdownModule_Core_Enum(ktkMainManager* p_manager);
bool SerializeModule_Core_Enum(ktkMainManager* p_manager);
bool DeserializeModule_Core_Enum(ktkMainManager* p_manager);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
