#pragma once

#include "kotek_std_math_quaternionf.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

inline quaternionf get_math_normalize(const quaternionf& quat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted = quat;
	DirectX::XMVECTOR normalized =
		DirectX::XMQuaternionNormalize(casted);

	quaternionf result;
	DirectX::XMStoreFloat4(&result.Get_Base(), normalized);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::normalize(quat.Get_Base());
#endif
}

inline quaternionf get_math_slerp(
	const quaternionf& left, const quaternionf& right, float factor
)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_left = left;
	DirectX::XMVECTOR casted_right = right;
	DirectX::XMVECTOR interpolated = DirectX::XMQuaternionSlerp(
		casted_left, casted_right, factor
	);

	quaternionf result;
	DirectX::XMStoreFloat4(&result.Get_Base(), interpolated);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::slerp(
		left.Get_Base(), right.Get_Base(), factor
	);
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
