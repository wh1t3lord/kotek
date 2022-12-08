#pragma once

// TODO: when std:: will implement header <format> for Linux you need to remove
// FMT library from that project

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

#include <format>

enum VkResult;
enum VkFormat;

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

template <>
struct std::formatter<VkResult, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(VkResult const& result_id, FormatContext& ctx)
	{
		return std::format_to(
			ctx.out(), KOTEK_TEXT("{}"), static_cast<int>(result_id));
	}
};

template <>
struct std::formatter<VkFormat, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(VkFormat const& result_id, FormatContext& ctx)
	{
		return std::format_to(
			ctx.out(), KOTEK_TEXT("{}"), static_cast<int>(result_id));
	}
};

#ifdef SHADERC_STATUS_H_
template <>
struct std::formatter<shaderc_compilation_status, Kotek::ktk::tchar>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(
		shaderc_compilation_status const& result_id, FormatContext& ctx)
	{
		return std::format_to(
			ctx.out(), KOTEK_TEXT("{}"), static_cast<int>(result_id));
	}
};
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename... Args>
ktk::string format(const ktk::string& text, Args&&... args) noexcept
{
	const auto& data =
		std::vformat(text.get_as_is().c_str(), std::make_wformat_args(args...));
	return ktk::string(data.begin(), data.end());
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK