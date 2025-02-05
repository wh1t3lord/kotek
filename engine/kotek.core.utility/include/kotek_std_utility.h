#pragma once

#include <kotek.core.constants.math/include/kotek_core_constants_math.h>
#include "kotek_std_utility_variant.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

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
	float relative_difference_factor = ktk::kMin_Float) noexcept;

bool is_equal(double a, double b,
	double relative_difference_factor = ktk::kMin_Double) noexcept;

bool is_equal(long double a, long double b,
	long double relative_difference_factor = ktk::kMin_Long_Double) noexcept;



/// @brief returns OPPOSITE separator depends on OS. For example, if your OS is
/// windows and you pass a '\\' separator it will return a '/' separator because
/// '\\' is preferred separator on WindowsNT platforms and thus opposite
/// separator for Windows will be '/'.
/// @param separator '/' and '\\' as accepted argument values for function
/// @return depends on platform and passed separator. Function CHECKS the value
/// of separator and if it is not preferred value that expected than function
/// returns passed argument
char fs_give_opposite_to_preferred_separator(char separator);

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
