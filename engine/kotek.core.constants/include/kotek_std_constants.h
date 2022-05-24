#pragma once

#include <kotek.core.types.char/include/kotek_core_types_char.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <limits>

#undef max
#undef min

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_PLATFORM_WINDOWS
		constexpr tchar kPathSeparator = KOTEK_TEXT('\\');
#else
		constexpr tchar kPathSeparator = KOTEK_TEXT('/');
#endif

		constexpr ktk::uint64_t kMax_UINT64 =
			std::numeric_limits<ktk::uint64_t>::max();
		constexpr ktk::uint32_t kMax_UINT32 =
			std::numeric_limits<ktk::uint32_t>::max();
		constexpr ktk::uint16_t kMax_UINT16 =
			std::numeric_limits<ktk::uint16_t>::max();
		constexpr ktk::uint8_t kMax_UINT8 =
			std::numeric_limits<ktk::uint8_t>::max();

		constexpr ktk::int64_t kMax_INT64 =
			std::numeric_limits<ktk::int64_t>::max();
		constexpr ktk::int32_t kMax_INT32 =
			std::numeric_limits<ktk::int32_t>::max();
		constexpr ktk::int16_t kMax_INT16 =
			std::numeric_limits<ktk::int16_t>::max();
		constexpr ktk::int8_t kMax_INT8 =
			std::numeric_limits<ktk::int8_t>::max();

		constexpr ktk::uint64_t kMin_UINT64 =
			std::numeric_limits<ktk::uint64_t>::min();
		constexpr ktk::uint32_t kMin_UINT32 =
			std::numeric_limits<ktk::uint32_t>::min();
		constexpr ktk::uint16_t kMin_UINT16 =
			std::numeric_limits<ktk::uint16_t>::min();
		constexpr ktk::uint8_t kMin_UINT8 =
			std::numeric_limits<ktk::uint8_t>::min();

		constexpr ktk::int64_t kMin_INT64 =
			std::numeric_limits<ktk::int64_t>::min();
		constexpr ktk::int32_t kMin_INT32 =
			std::numeric_limits<ktk::int32_t>::min();
		constexpr ktk::int16_t kMin_INT16 =
			std::numeric_limits<ktk::int16_t>::min();
		constexpr ktk::int8_t kMin_INT8 =
			std::numeric_limits<ktk::int8_t>::min();
	} // namespace ktk

	constexpr ktk::entity_t kInvalidEntityID = 0;
	constexpr ktk::entity_t kActorEntityID = 1;

	constexpr int _kDefaultWindowSizeWidth = 640;
	constexpr int _kDefaultWindowSizeHeight = 480;
} // namespace Kotek
