#pragma once

#include <kotek.core.format/include/kotek_core_format.h>

#ifdef KOTEK_USE_PLATFORM_WINDOWS
/* remove code from vulkan template and add bgfx related things
template <>
struct std::formatter<VkResult, char>
{
    template <typename ParseContext>
    constexpr inline auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    inline auto format(VkResult const& result_id, auto& ctx) const
    {
        return std::format_to(ctx.out(), "{}", static_cast<int>(result_id));
    }
};

template <>
struct std::formatter<VkFormat, char>
{
    template <typename ParseContext>
    constexpr inline auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    inline auto format(VkFormat const& result_id, auto& ctx) const
    {
        return std::format_to(ctx.out(), "{}", static_cast<int>(result_id));
    }
};
*/
#elif defined(KOTEK_USE_PLATFORM_LINUX)
/*
template <>
struct fmt::formatter<VkResult, char>
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
            ctx.out(), "{}", static_cast<int>(result_id));
    }
};

template <>
struct fmt::formatter<VkFormat, char>
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
            ctx.out(), "{}", static_cast<int>(result_id));
    }
};
*/
#endif