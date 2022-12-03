#pragma once

// TODO: when std:: will implement header <format> for Linux you need to remove
// FMT library from that project

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

#include <format>

template <>
struct std::formatter<Kotek::ktk::string, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(Kotek::ktk::string const& str, FormatContext& ctx)
	{
		return std::format_to(ctx.out(), KOTEK_TEXT("{}"), str.get_as_is());
	}
};

template <>
struct std::formatter<Kotek::ktk::filesystem::path, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(
		Kotek::ktk::filesystem::path const& str, FormatContext& ctx)
	{
		return std::format_to(ctx.out(), KOTEK_TEXT("{}"),
			Kotek::ktk::string(
				reinterpret_cast<const char*>(str.u8string().c_str())));
	}
};

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename... Args>
ktk::string format(const ktk::string& text, Args&&... args) noexcept
{
	const auto& data = std::format(text.get_as_is(), fmt::make_format_args(std::forward<Args>(args)...));

	return ktk::string(data.begin(), data.end());
}

template <typename... Args>
void print(std::format_string<Args...> fmt, Args&&... args)
{
	std::print(fmt, args...);
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK