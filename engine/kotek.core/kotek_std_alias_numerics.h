#pragma once

#include <cstddef>
#include <cstdint>

namespace Kotek
{
	namespace ktk
	{
		using uint64_t = std::uint64_t;
		using uint32_t = std::uint32_t;
		using uint16_t = std::uint16_t;
		using uint8_t = std::uint8_t;
		using int64_t = std::int64_t;
		using int32_t = std::int32_t;
		using int16_t = std::int16_t;
		using int8_t = std::int8_t;
		using size_t = std::size_t;
		using entity_t = uint64_t;
		using enum_base_t = int;

		constexpr uint32_t kMemoryConvertValue_Gigabytes = 1073741824;
		constexpr uint32_t kMemoryConvertValue_Megabytes = 1048576;
		constexpr uint32_t kMemoryConvertValue_Kilobytes = 1024;
	} // namespace ktk
} // namespace Kotek
