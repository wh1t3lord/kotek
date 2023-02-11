#pragma once

#include <kotek.core.format/include/kotek_core_format.h>

template <>
struct fmt::formatter<VkResult, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(VkResult const& result_id, FormatContext& ctx)
	{
		return fmt::format_to(
			ctx.out(), KOTEK_TEXT("{}"), static_cast<int>(result_id));
	}
};

template <>
struct fmt::formatter<VkFormat, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(VkFormat const& result_id, FormatContext& ctx)
	{
		return fmt::format_to(
			ctx.out(), KOTEK_TEXT("{}"), static_cast<int>(result_id));
	}
};
