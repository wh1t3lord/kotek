#pragma once

#include <variant>

namespace Kotek
{
	namespace ktk
	{
		template <typename... Args>
		using variant = std::variant<Args...>;
	}
} // namespace Kotek