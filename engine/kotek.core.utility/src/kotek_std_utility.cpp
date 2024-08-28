#include "../include/kotek_std_utility.h"
#include "../../kotek.core.defines.static.os/include/kotek_core_defines_static_os.h"
#include <cmath>
#include <utility>

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#ifdef KOTEK_USE_PLATFORM_WINDOWS
		#include <Windows.h>
		#undef max
	#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#elif defined(KOTEK_USE_PLATFORM_MACOS)
	#else
		#error unknown platform please report to developers or community for implementation request ^_^
	#endif
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

bool is_equal(float a, float b, float relative_difference_factor) noexcept
{
	auto difference = std::fabs(a - b);
	auto magnitude = std::max(std::abs(a), std::abs(b));
	auto factor = relative_difference_factor * magnitude;

	if (difference <= factor)
		return true;

	return false;
}

bool is_equal(double a, double b, double relative_difference_factor) noexcept
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

char fs_give_opposite_to_preferred_separator(char separator)
{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
	if (separator == '\\')
		return '/';
	else
		return separator;
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#error implement
#elif defined(KOTEK_USE_PLATFORM_MACOS)
#else
	#error unknown platform, report to developers or community
	return 0;
#endif
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK