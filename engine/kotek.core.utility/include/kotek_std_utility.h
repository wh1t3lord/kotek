#pragma once

#include <kotek.core.constants.math/include/kotek_core_constants_math.h>
#include "kotek_std_utility_variant.h"
#include "kotek_std_utility_function.h"
#include "kotek_std_utility_hash.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename T>
T align_up(T val, T alignment) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return (val + alignment - (T)1) & ~(alignment - (T)1);
}

template <typename T>
T align_down(T val, T alignment) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	return val & ~(alignment - (T)1);
}

bool is_equal(
	float a, float b, float relative_difference_factor = kun_ktk kMin_Float)
	KOTEK_CPP_KEYWORD_NOEXCEPT;

bool is_equal(
	double a, double b, double relative_difference_factor = kun_ktk kMin_Double)
	KOTEK_CPP_KEYWORD_NOEXCEPT;

bool is_equal(long double a, long double b,
	long double relative_difference_factor = kun_ktk kMin_Long_Double)
	KOTEK_CPP_KEYWORD_NOEXCEPT;

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
