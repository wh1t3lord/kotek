#pragma once

// TODO: when std:: will implement header <format> for Linux you need to remove
// FMT library from that project

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
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
struct std::formatter<Kotek::ktk::ustring, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	inline auto format(Kotek::ktk::ustring const& str, auto& ctx) const
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
struct std::formatter<ktk_filesystem_path, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	inline auto format(
		ktk_filesystem_path const& str, auto& ctx) const
	{
		return std::format_to(ctx.out(), "{}",
			reinterpret_cast<const char*>(str.u8string().c_str()));
	}
};

	#endif
#elif defined(KOTEK_USE_PLATFORM_LINUX)
template <>
struct fmt::formatter<Kotek::ktk::ustring, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(Kotek::ktk::ustring const& str, FormatContext& ctx)
	{
	#ifdef KOTEK_USE_UNICODE
		return fmt::format_to(
			ctx.out(), "{}", reinterpret_cast<const char*>(str.c_str()));
	#else
		return fmt::format_to(ctx.out(), "{}", str.c_str());
	#endif
	}
};

template <>
struct fmt::formatter<Kotek::ktk::filesystem::path, char>
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
		return fmt::format_to(
			ctx.out(), u8"{}", Kotek::ktk::ustring(str.u8string().c_str()));
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
ktk::cstring format(const ktk::ustring& text, Args&&... args) noexcept
{
		#ifdef KOTEK_USE_PLATFORM_WINDOWS
	const auto& data = std::vformat(reinterpret_cast<const char*>(text.c_str()),
		std::make_format_args(args...));
		#elif defined(KOTEK_USE_PLATFORM_LINUX)
	const auto& data = fmt::vformat(reinterpret_cast<const char*>(text.c_str()),
		fmt::make_format_args(args...));
		#endif

	return ktk::cstring(data.begin(), data.end());
}
	#endif
#endif

template <typename... Args>
ktk::cstring format(const ktk::cstring& text, Args&&... args) noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	const auto& data =
		std::vformat(text.c_str(), std::make_format_args(args...));
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	const auto& data =
		fmt::vformat(text.c_str(), fmt::make_format_args(args...));
#endif

	return ktk::cstring(data.begin(), data.end());
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
