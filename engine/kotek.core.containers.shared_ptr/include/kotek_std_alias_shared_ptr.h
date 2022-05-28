#pragma once

#include <memory>

namespace Kotek
{
	namespace ktk
	{
		template <typename T>
		using shared_ptr = std::shared_ptr<T>;
	}
} // namespace Kotek