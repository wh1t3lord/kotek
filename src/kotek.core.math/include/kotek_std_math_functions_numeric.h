#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

inline kun_ktk float_t convert_to_radians(
	kun_ktk float_t degrees
) KOTEK_CPP_KEYWORD_NOEXCEPT
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMConvertToRadians(degrees);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::radians(degrees);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return degrees * 0.01745329251994329576923690768489f;
#else
	#error unknown math library
#endif
}

inline kun_ktk float_t convert_to_degrees(
	kun_ktk float_t radians
) KOTEK_CPP_KEYWORD_NOEXCEPT
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMConvertToDegrees(radians);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::degrees(radians);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return radians * 57.295779513082320876798154814105f;
#else
	#error unknown math library
#endif
}

inline kun_ktk double_t convert_to_radians(
	kun_ktk double_t degrees
) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR kun_ktk double_t converter =
		3.14159265358979323846 / 180.0;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return degrees * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::radians(degrees);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return degrees * converter;
#else
	#error unknown math library
#endif
}

inline kun_ktk double_t convert_to_degrees(
	kun_ktk double_t radians
) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR kun_ktk double_t converter =
		180.0 / 3.14159265358979323846;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return radians * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::degrees(radians);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return radians * converter;
#else
	#error unknown math library
#endif
}

inline kun_ktk long_double_t convert_to_radians(
	kun_ktk long_double_t degrees
) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR kun_ktk long_double_t
		converter = 3.14159265358979323846264338327950288419716939937510L /
		180.0L;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return degrees * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::radians(degrees);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return degrees * converter;
#else
	#error unknown math library
#endif
}

inline kun_ktk long_double_t convert_to_degrees(
	kun_ktk long_double_t radians
) KOTEK_CPP_KEYWORD_NOEXCEPT
{
	KOTEK_CPP_KEYWORD_CONSTEXPR kun_ktk long_double_t converter =
		180.0L /
		3.14159265358979323846264338327950288419716939937510L;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return radians * converter;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::degrees(radians);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return radians * converter;
#else
	#error unknown math library
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
