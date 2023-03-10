#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

ktk::float_t convert_to_radians(ktk::float_t degree) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMConvertToRadians(degree);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
