#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

KOTEK_CPP_KEYWORD_INLINE ktk::float_t convert_to_radians(
	ktk::float_t degrees) KOTEK_CPP_KEYWORD_NOEXCEPT
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMConvertToRadians(degrees);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

KOTEK_CPP_KEYWORD_INLINE ktk::float_t convert_to_degrees(
	ktk::float_t radians) KOTEK_CPP_KEYWORD_NOEXCEPT
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMConvertToDegrees(radians);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

KOTEK_CPP_KEYWORD_INLINE ktk::double_t convert_to_radians(
	ktk::double_t degrees) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR ktk::double_t converter =
		180.0 / 3.14159265358979323846;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return degrees * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

KOTEK_CPP_KEYWORD_INLINE ktk::double_t convert_to_degrees(
	ktk::double_t radians) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR ktk::double_t converter =
		3.14159265358979323846 / 180.0;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return radians * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

KOTEK_CPP_KEYWORD_INLINE ktk::long_double_t convert_to_radians(
	ktk::long_double_t degrees) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR ktk::long_double_t converter =
		180.0L / 3.14159265358979323846264338327950288419716939937510L;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return degrees * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

KOTEK_CPP_KEYWORD_INLINE ktk::long_double_t convert_to_degrees(
	ktk::long_double_t radians) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR ktk::long_double_t converter =
		3.14159265358979323846264338327950288419716939937510L / 180.0L;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return radians * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
