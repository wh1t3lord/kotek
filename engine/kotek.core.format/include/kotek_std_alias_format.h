#pragma once

// TODO: when std:: will implement header <format> for Linux you need to remove
// FMT library from that project

#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <fmt/format.h>
#include <fmt/xchar.h>

namespace Kotek
{
	namespace ktk
	{
		template <typename... Args>
		ktk::string format(const ktk::string& text, Args&&... args) noexcept
		{
			const auto& data =
				fmt::format(text.get_as_is(), std::forward<Args>(args)...);
			return ktk::string(data.begin(), data.end());
		}

		template <typename... Args>
		void print(fmt::format_string<Args...> fmt, Args&&... args)
		{
			fmt::print(fmt, args...);
		}

	} // namespace ktk
} // namespace Kotek