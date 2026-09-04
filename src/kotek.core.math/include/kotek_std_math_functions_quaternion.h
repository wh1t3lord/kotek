#pragma once

#include "kotek_std_math_quaternionf.h"
#include "kotek_std_math_vector3f.h"

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
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return normalize(quat.Get_Base());
#else
	#error unknown math library
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
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return slerp(
		left.Get_Base(), right.Get_Base(), factor
	);
#else
	#error unknown math library
#endif
}

/// \~english axis-angle -> quaternion (glm::angleAxis): the axis must be
/// normalized, the angle is in radians (convert_to_radians for degrees)
inline quaternionf get_math_angle_axis(
	float angle_radians, const vector3f& axis
)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_axis =
		DirectX::XMLoadFloat3(&axis.Get_Base());
	DirectX::XMVECTOR quat =
		DirectX::XMQuaternionRotationAxis(casted_axis, angle_radians);

	quaternionf result;
	DirectX::XMStoreFloat4(&result.Get_Base(), quat);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::angleAxis(angle_radians, axis.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return angle_axis(angle_radians, axis.Get_Base());
#else
	#error unknown math library
#endif
}

/// \~english rotate a vector by a quaternion (glm::rotate(q, v)); the
/// quaternion must be normalized for a pure rotation
inline vector3f get_math_rotate(
	const quaternionf& rotation, const vector3f& vec
)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR casted_vec =
		DirectX::XMLoadFloat3(&vec.Get_Base());
	DirectX::XMVECTOR casted_quat =
		DirectX::XMLoadFloat4(&rotation.Get_Base());
	DirectX::XMVECTOR rotated =
		DirectX::XMVector3Rotate(casted_vec, casted_quat);

	vector3f result;
	DirectX::XMStoreFloat3(&result.Get_Base(), rotated);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::rotate(rotation.Get_Base(), vec.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return rotate(rotation.Get_Base(), vec.Get_Base());
#else
	#error unknown math library
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
