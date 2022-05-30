#include "../include/kotek_std_utility.h"
#include <cmath>

namespace Kotek
{
	namespace ktk
	{
		bool is_equal(
			float a, float b, float relative_difference_factor) noexcept
		{
			auto difference = std::fabs(a - b);
			auto magnitude = std::max(std::abs(a), std::abs(b));
			auto factor = relative_difference_factor * magnitude;

			if (difference <= factor)
				return true;

			return false;
		}

		bool is_equal(
			double a, double b, double relative_difference_factor) noexcept
		{
			auto difference = std::fabs(a - b);
			auto magnitude = std::max(std::abs(a), std::abs(b));
			auto factor = relative_difference_factor * magnitude;

			if (difference <= factor)
				return true;

			return false;
		}

		bool is_equal(long double a, long double b,
			long double relative_difference_factor) noexcept
		{
			auto difference = std::fabs(a - b);
			auto magnitude = std::max(std::abs(a), std::abs(b));
			auto factor = relative_difference_factor * magnitude;

			if (difference <= factor)
				return true;

			return false;
		}
	} // namespace ktk
} // namespace Kotek