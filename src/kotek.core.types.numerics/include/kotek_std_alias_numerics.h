#pragma once

#include <cstddef>
#include <cstdint>
#include <chrono>

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

using uint64_t = std::uint64_t;
using uint32_t = std::uint32_t;
using uint16_t = std::uint16_t;
using uint8_t = std::uint8_t;
using int64_t = std::int64_t;
using int32_t = std::int32_t;
using int16_t = std::int16_t;
using int8_t = std::int8_t;
using size_t = std::size_t;
using ptrdiff_t = std::ptrdiff_t;
using enum_base_t = int;
using flag_t = unsigned int;
using uintptr_t = std::uintptr_t;

using float_t = float;
using double_t = double;
using long_double_t = long double;
using streamsize_t = std::streamsize;

namespace chrono = std::chrono;
namespace chrono_literals = std::chrono_literals;

static_assert(!std::is_unsigned_v<enum_base_t>,
	"you must specify this type as signed type, because of system's legacy "
	"(and rational approach for defining enums)");

constexpr enum_base_t kInvalidEnumBase = enum_base_t(-1);

KOTEK_END_NAMESPACE_KTK

using uint64_t = KUN_KOTEK KUN_KTK uint64_t;
using uint32_t = KUN_KOTEK KUN_KTK uint32_t;
using uint16_t = KUN_KOTEK KUN_KTK uint16_t;
using uint8_t = KUN_KOTEK KUN_KTK uint8_t;
using int64_t = KUN_KOTEK KUN_KTK int64_t;
using int32_t = KUN_KOTEK KUN_KTK int32_t;
using int16_t = KUN_KOTEK KUN_KTK int16_t;
using int8_t = KUN_KOTEK KUN_KTK int8_t;
using size_t = KUN_KOTEK KUN_KTK size_t;
using ptrdiff_t = KUN_KOTEK KUN_KTK ptrdiff_t;
using enum_base_t = KUN_KOTEK KUN_KTK enum_base_t;
using uintptr_t = KUN_KOTEK KUN_KTK uintptr_t;

using float_t = KUN_KOTEK KUN_KTK float_t;
using double_t = KUN_KOTEK KUN_KTK double_t;
using long_double_t = KUN_KOTEK KUN_KTK long_double_t;
using streamsize_t = KUN_KOTEK KUN_KTK streamsize_t;
namespace chrono = KUN_KOTEK KUN_KTK chrono;
namespace chrono_literals = KUN_KOTEK KUN_KTK chrono_literals;

KOTEK_END_NAMESPACE_KOTEK
