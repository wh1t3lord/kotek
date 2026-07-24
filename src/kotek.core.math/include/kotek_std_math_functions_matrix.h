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
	return glm::lookAt(
		camera_position.Get_Base(),
		target_position.Get_Base(),
		up_vector.Get_Base()
	);
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
	return glm::perspective(
		field_of_view_angle_in_radians,
		aspect_ratio,
		plane_near_z,
		plane_far_z
	);
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

inline matrix2x2f transpose(const matrix2x2f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX casted = mat;
	DirectX::XMMATRIX transposed =
		DirectX::XMMatrixTranspose(casted);

	matrix2x2f result;
	DirectX::XMStoreFloat3x3(&result.Get_Base(), transposed);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::transpose(mat.Get_Base());
#endif
}

inline matrix3x3f transpose(const matrix3x3f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMMatrixTranspose(mat);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::transpose(mat.Get_Base());
#endif
}

inline matrix4x4f transpose(const matrix4x4f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return DirectX::XMMatrixTranspose(mat);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::transpose(mat.Get_Base());
#endif
}

inline float get_math_determinant(const matrix2x2f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	// det is transpose-invariant, the 2x2 adjugate formula reads
	// the same in the transposed storage
	return mat.e(0, 0) * mat.e(1, 1) - mat.e(1, 0) * mat.e(0, 1);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::determinant(mat.Get_Base());
#endif
}

inline float get_math_determinant(const matrix3x3f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX casted = mat;
	DirectX::XMVECTOR determinant =
		DirectX::XMMatrixDeterminant(casted);

	float result;
	DirectX::XMStoreFloat(&result, determinant);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::determinant(mat.Get_Base());
#endif
}

inline float get_math_determinant(const matrix4x4f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX casted = mat;
	DirectX::XMVECTOR determinant =
		DirectX::XMMatrixDeterminant(casted);

	float result;
	DirectX::XMStoreFloat(&result, determinant);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::determinant(mat.Get_Base());
#endif
}

inline matrix2x2f get_math_inverse(const matrix2x2f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	float determinant = get_math_determinant(mat);

	KOTEK_ASSERT(
		determinant != 0.0f, "matrix is singular, inverse is "
		"undefined"
	);

	matrix2x2f result;

	if (determinant != 0.0f)
	{
		float factor = 1.0f / determinant;

		// the 2x2 adjugate formula is transpose-symmetric, so it
		// reads identically in the transposed storage
		result.e(0, 0) = mat.e(1, 1) * factor;
		result.e(1, 0) = -mat.e(1, 0) * factor;
		result.e(0, 1) = -mat.e(0, 1) * factor;
		result.e(1, 1) = mat.e(0, 0) * factor;
	}

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::inverse(mat.Get_Base());
#endif
}

inline matrix3x3f get_math_inverse(const matrix3x3f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX casted = mat;
	DirectX::XMVECTOR determinant =
		DirectX::XMMatrixDeterminant(casted);

	float determinant_value;
	DirectX::XMStoreFloat(&determinant_value, determinant);

	KOTEK_ASSERT(
		determinant_value != 0.0f,
		"matrix is singular, inverse is undefined"
	);

	// the loaded matrix is L^T and (L^T)^-1 == (L^-1)^T, so the
	// result stores back without any transpose
	DirectX::XMMATRIX inversed =
		DirectX::XMMatrixInverse(nullptr, casted);

	matrix3x3f result(inversed);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::inverse(mat.Get_Base());
#endif
}

inline matrix4x4f get_math_inverse(const matrix4x4f& mat)
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX casted = mat;
	DirectX::XMVECTOR determinant =
		DirectX::XMMatrixDeterminant(casted);

	float determinant_value;
	DirectX::XMStoreFloat(&determinant_value, determinant);

	KOTEK_ASSERT(
		determinant_value != 0.0f,
		"matrix is singular, inverse is undefined"
	);

	// the loaded matrix is L^T and (L^T)^-1 == (L^-1)^T, so the
	// result stores back without any transpose
	DirectX::XMMATRIX inversed =
		DirectX::XMMatrixInverse(nullptr, casted);

	matrix4x4f result(inversed);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return glm::inverse(mat.Get_Base());
#endif
}

// double

KOTEK_END_NAMESPACE_MATH KOTEK_END_NAMESPACE_KTK KOTEK_END_NAMESPACE_KOTEK