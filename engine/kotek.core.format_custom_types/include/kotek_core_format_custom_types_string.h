#pragma once

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>

#include <fmt/format.h>

template <>
struct fmt::formatter<Kotek::ktk::string>
{
	template <typename ParseContext>
	constexpr auto parse(ParseContext& context)
	{
		return context.begin();
	}

	template <typename FormatContext>
	auto format(const Kotek::ktk::string& str, FormatContext& context)
	{
		return fmt::format_to(context.out(), "{}", str.get_as_is());
	}
};
