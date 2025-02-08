#pragma once

// TODO: when std:: will implement header <format> for Linux you need to remove
// FMT library from that project

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#include <format>
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#include <fmt/core.h>
	#include <fmt/format.h>
	#include <fmt/xchar.h>
#else
	#error Unknown platform we cant know status about your format library
#endif

#ifdef KOTEK_USE_PLATFORM_WINDOWS

	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
template <>
struct std::formatter<kun_kotek kun_ktk ustring, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	inline auto format(kun_kotek kun_ktk ustring const& str, auto& ctx) const
	{
		#ifdef KOTEK_USE_UNICODE
		return std::format_to(
			ctx.out(), "{}", reinterpret_cast<const char*>(str.c_str()));
		#else
		return std::format_to(ctx.out(), "{}", str.c_str());
		#endif
	}
};

template <>
struct std::formatter<kun_kotek kun_ktk static_cstring_view, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	inline auto format(
		kun_kotek kun_ktk static_cstring_view const& str, auto& ctx) const
	{
		return std::format_to(ctx.out(), "{}", str.data());
	}
};

#include "kotek_formatter_static_cstring.h"

	#endif
#elif defined(KOTEK_USE_PLATFORM_LINUX)
template <>
struct fmt::formatter<kun_kotek kun_ktk ustring, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(kun_kotek kun_ktk ustring const& str, FormatContext& ctx)
	{
	#ifdef KOTEK_USE_UNICODE
		return fmt::format_to(
			ctx.out(), "{}", reinterpret_cast<const char*>(str.c_str()));
	#else
		return fmt::format_to(ctx.out(), "{}", str.c_str());
	#endif
	}
};
#else
	#error Undefined platform
#endif

#ifdef SHADERC_STATUS_H_
template <>
struct std::formatter<shaderc_compilation_status, char>
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
			ctx.out(), KOTEK_TEXTU("{}"), static_cast<int>(result_id));
	}
};
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifndef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
	#if KOTEK_USE_STRING_CONFIGURATION_CHAR_TYPE != 1
template <typename... Args>
cstring format(const ustring_view& text, Args&&... args) noexcept
{
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	const auto& data = std::vformat(reinterpret_cast<const char*>(text.data()),
		std::make_format_args(args...));
		#elif defined(KOTEK_USE_PLATFORM_LINUX)
	const auto& data = fmt::vformat(reinterpret_cast<const char*>(text.data()),
		fmt::make_format_args(args...));
		#endif

	return cstring(data.begin(), data.end());
}
	#endif
#endif

template <typename... Args>
cstring format(const cstring_view& text, Args&&... args) noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	const cstring& data =
		std::vformat(text.data(), std::make_format_args(args...));
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	const auto& data =
		fmt::vformat(text.data(), fmt::make_format_args(args...));
#endif

	return cstring(data.begin(), data.end());
}

template <size_t Size = 64, typename... Args>
static_cstring<Size> static_format(
	const cstring_view& text, Args&&... args) noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	static_cstring<Size> buffer{};

	std::vformat_to(std::back_insert_iterator{buffer}, text,
		std::make_format_args(args...));

#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error provide implementation
#endif

	return buffer;
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
