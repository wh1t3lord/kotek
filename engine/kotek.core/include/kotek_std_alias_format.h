#pragma once

#include "kotek_std_alias_string.h"
#include "kotek_std_string.h"
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

	} // namespace ktk
} // namespace Kotek
