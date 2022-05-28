#pragma once

#include <functional>

namespace Kotek
{
	namespace ktk
	{
		template <class T>
		using function = std::function<T>;
	}
} // namespace Kotek