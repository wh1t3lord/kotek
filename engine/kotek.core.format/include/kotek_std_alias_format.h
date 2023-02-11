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
template <>
struct std::formatter<Kotek::ktk::string, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(Kotek::ktk::string const& str, FormatContext& ctx)
	{
		return std::format_to(ctx.out(), KOTEK_TEXT("{}"), reinterpret_cast<const char*>(str.c_str()));
	}
};

template <>
struct std::formatter<Kotek::ktk::filesystem::path, char>
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
#elif defined(KOTEK_USE_PLATFORM_LINUX)
template <>
struct fmt::formatter<Kotek::ktk::string, char>
{
	template <typename ParseContext>
	constexpr inline auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	inline auto format(Kotek::ktk::string const& str, FormatContext& ctx)
	{
#ifdef KOTEK_USE_UNICODE
        return fmt::format_to(ctx.out(), u8"{}", reinterpret_cast<const char*>(str.c_str()));
#else
        return fmt::format_to(ctx.out(), "{}", reinterpret_cast<const char*>());
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
#ifdef KOTEK_USE_UNICODE
        return fmt::format_to(ctx.out(), u8"{}",
			Kotek::ktk::string(
                str.u8string().c_str()));
#else
        return fmt::format_to(ctx.out(), "{}",
            Kotek::ktk::string(
                str.string().c_str()));
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
			ctx.out(), KOTEK_TEXT("{}"), static_cast<int>(result_id));
	}
};
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename... Args>
ktk::string format(const ktk::string& text, Args&&... args) noexcept
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	const auto& data =
		std::vformat(text.c_str(), std::make_format_args(args...));
#elif defined(KOTEK_USE_PLATFORM_LINUX)
        	const auto& data =
		fmt::vformat(reinterpret_cast<const char*>(text.c_str()), fmt::make_format_args(args...));
#endif
                
	return ktk::string(data.begin(), data.end());
}

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

    return data;
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
