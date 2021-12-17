#pragma once

#include <memory>

namespace Kotek
{
	namespace ktk
	{
		template <typename T>
		T align_up(T val, T alignment) noexcept
		{
			return (val + alignment - (T)1) & ~(alignment - (T)1);
		}

		template <typename T>
		T align_down(T val, T alignment) noexcept
		{
			return val & ~(alignment - (T)1);
		}
	} // namespace ktk
} // namespace Kotek
