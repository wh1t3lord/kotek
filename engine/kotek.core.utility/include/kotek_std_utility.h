#pragma once

#include <kotek.core.constants.math/include/kotek_core_constants_math.h>

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

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
