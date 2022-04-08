#pragma once

#include "kotek_std_alias_math.h"
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

		bool is_equal(float a, float b,
			float relative_difference_factor = math::kMin_Float) noexcept;

		bool is_equal(double a, double b,
			double relative_difference_factor = math::kMin_Double) noexcept;

		bool is_equal(long double a, long double b,
			long double relative_difference_factor =
				math::kMin_LongDouble) noexcept;
	} // namespace ktk
} // namespace Kotek
