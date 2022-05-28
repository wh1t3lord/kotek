#pragma once

#include <memory>

namespace Kotek
{
	namespace ktk
	{
		template <typename T>
		using unique_ptr = std::unique_ptr<T>;
	}
} // namespace Kotek