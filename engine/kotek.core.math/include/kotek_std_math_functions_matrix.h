#pragma once

#include "kotek_std_math_matrix_2x2_f.h"
#include "kotek_std_math_matrix_3x3_f.h"
#include "kotek_std_math_matrix_4x4_f.h"

#include "kotek_std_math_vector1f.h"
#include "kotek_std_math_vector2f.h"
#include "kotek_std_math_vector3f.h"
#include "kotek_std_math_vector4f.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

inline matrix4x4f look_at(const vector3f& camera_position,
	const vector3f& target_position, const vector3f& up_vector)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMMatrixLookAtRH(
		camera_position, target_position, up_vector);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#else
// implement yours here
#endif
}

inline matrix4x4f perspective(float_t field_of_view_angle_in_radians,
	float_t aspect_ratio, float_t plane_near_z, float_t plane_far_z)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMMatrixPerspectiveFovRH(field_of_view_angle_in_radians,
		aspect_ratio, plane_near_z, plane_far_z);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#else
// implement yours here
#endif
}

inline float const* value_ptr(const matrix2x2f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &data.Get_Base().m[0][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* value_ptr(const matrix3x3f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &data.Get_Base().m[0][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline float const* value_ptr(const matrix4x4f& data)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &data.Get_Base().m[0][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::value_ptr(data.Get_Base());
#endif
}

inline matrix3x3f transpose(const matrix3x3f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMMatrixTranspose(mat);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
}

inline matrix4x4f transpose(const matrix4x4f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMMatrixTranspose(mat);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
}

// double

KOTEK_END_NAMESPACE_MATH KOTEK_END_NAMESPACE_KTK KOTEK_END_NAMESPACE_KOTEK