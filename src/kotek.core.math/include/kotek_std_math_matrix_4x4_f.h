#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class matrix4x4f
{
public:
	matrix4x4f(
		float c0r0,
		float c0r1,
		float c0r2,
		float c0r3,
		float c1r0,
		float c1r1,
		float c1r2,
		float c1r3,
		float c2r0,
		float c2r1,
		float c2r2,
		float c2r3,
		float c3r0,
		float c3r1,
		float c3r2,
		float c3r3
	);
	matrix4x4f(const base_mat4x4_t& data);
	matrix4x4f(const matrix4x4f& data);
	matrix4x4f(const matrixnf_view_t& view);
	matrix4x4f(const matrixnf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	matrix4x4f(const DirectX::XMMATRIX& data);
#endif

	matrix4x4f(void);

	~matrix4x4f(void) = default;

	matrix4x4f& operator=(const matrix4x4f& data);
	matrix4x4f& operator=(const matrixnf_view_t& view);
	matrix4x4f& operator=(const matrixnf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix4x4f& operator=(const matrix2x2f& data);
	matrix4x4f& operator=(const matrix3x3f& data);
	matrix4x4f& operator=(const vector1f& data);
	matrix4x4f& operator=(const vector2f& data);
	matrix4x4f& operator=(const vector3f& data);
	matrix4x4f& operator=(const vector4f& data);
#endif

	matrix4x4f& operator+=(const matrix4x4f& data) noexcept;
	matrix4x4f& operator+=(const matrixnf_view_t& view);
	matrix4x4f& operator+=(const matrixnf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix4x4f& operator+=(const matrix2x2f& data);
	matrix4x4f& operator+=(const matrix3x3f& data);
	matrix4x4f& operator+=(const vector1f& data);
	matrix4x4f& operator+=(const vector2f& data);
	matrix4x4f& operator+=(const vector3f& data);
	matrix4x4f& operator+=(const vector4f& data);
	matrix4x4f& operator+=(const vectornf_const_view_t& view);
	matrix4x4f& operator+=(const vectornf_view_t& view);
#endif

	matrix4x4f& operator-=(const matrix4x4f& data) noexcept;
	matrix4x4f& operator-=(const matrixnf_view_t& view);
	matrix4x4f& operator-=(const matrixnf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix4x4f& operator-=(const matrix2x2f& data);
	matrix4x4f& operator-=(const matrix3x3f& data);
	matrix4x4f& operator-=(const vector1f& data);
	matrix4x4f& operator-=(const vector2f& data);
	matrix4x4f& operator-=(const vector3f& data);
	matrix4x4f& operator-=(const vector4f& data);
	matrix4x4f& operator-=(const vectornf_const_view_t& view);
	matrix4x4f& operator-=(const vectornf_view_t& view);
#endif

	matrix4x4f& operator*=(const matrix4x4f& data) noexcept;
	matrix4x4f& operator*=(const matrixnf_view_t& data
	) noexcept;
	matrix4x4f& operator*=(const matrixnf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix4x4f& operator*=(const matrix2x2f& data);
	matrix4x4f& operator*=(const matrix3x3f& data);
	matrix4x4f& operator*=(const vector1f& data);
	matrix4x4f& operator*=(const vector2f& data);
	matrix4x4f& operator*=(const vector3f& data);
	matrix4x4f& operator*=(const vector4f& data);
	matrix4x4f& operator*=(const vectornf_const_view_t& view);
	matrix4x4f& operator*=(const vectornf_view_t& view);
#endif

	matrix4x4f& operator*=(float value) noexcept;

#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	matrix4x4f& operator/=(const matrix4x4f& data) noexcept;
	matrix4x4f& operator/=(const matrixnf_view_t& view
	) noexcept;
	matrix4x4f& operator/=(const matrixnf_const_view_t& view
	) noexcept;

	#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix4x4f& operator/=(const matrix2x2f& data);
	matrix4x4f& operator/=(const matrix3x3f& data);
	matrix4x4f& operator/=(const vector1f& data);
	matrix4x4f& operator/=(const vector2f& data);
	matrix4x4f& operator/=(const vector3f& data);
	matrix4x4f& operator/=(const vector4f& data);
	matrix4x4f& operator/=(const vectornf_const_view_t& view);
	matrix4x4f& operator/=(const vectornf_view_t& view);
	#endif
#endif

	matrix4x4f& operator/=(float value) noexcept;

	matrix4x4f operator+() const noexcept;

	matrix4x4f operator-() const noexcept;

	bool operator==(const matrix4x4f& data) const noexcept;

	bool operator!=(const matrix4x4f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMMATRIX(void) const noexcept;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

	float
	e(math_id_t column_id, math_id_t row_id) const noexcept;
	float& e(math_id_t column_id, math_id_t row_id) noexcept;

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	float* data(void) noexcept;
	const float* data(void) const noexcept;

	constexpr math_id_t size_of(void) const noexcept;
	constexpr math_id_t get_column_count(void) const noexcept;
	constexpr math_id_t get_row_count(void) const noexcept;

	matrix4x4f& Set_Base(const base_mat4x4_t& data) noexcept;
	base_mat4x4_t& Get_Base(void) noexcept;
	const base_mat4x4_t& Get_Base(void) const noexcept;

private:
	base_mat4x4_t m_base;
};

inline matrix4x4f operator+(
	const matrix4x4f& left, const matrix4x4f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0(left[0].data());
	DirectX::XMFLOAT4 left_row_1(left[1].data());
	DirectX::XMFLOAT4 left_row_2(left[2].data());
	DirectX::XMFLOAT4 left_row_3(left[3].data());

	DirectX::XMFLOAT4 right_row_0(right[0].data());
	DirectX::XMFLOAT4 right_row_1(right[1].data());
	DirectX::XMFLOAT4 right_row_2(right[2].data());
	DirectX::XMFLOAT4 right_row_3(right[3].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 =
		DirectX::XMLoadFloat4(&left_row_3);

	DirectX::XMVECTOR row_argument_0 =
		DirectX::XMLoadFloat4(&right_row_0);
	DirectX::XMVECTOR row_argument_1 =
		DirectX::XMLoadFloat4(&right_row_1);
	DirectX::XMVECTOR row_argument_2 =
		DirectX::XMLoadFloat4(&right_row_2);
	DirectX::XMVECTOR row_argument_3 =
		DirectX::XMLoadFloat4(&right_row_3);

	row_original_0 =
		DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 =
		DirectX::XMVectorAdd(row_original_1, row_argument_1);
	row_original_2 =
		DirectX::XMVectorAdd(row_original_2, row_argument_2);
	row_original_3 =
		DirectX::XMVectorAdd(row_original_3, row_argument_3);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[0][0]
		),
		row_original_0
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[1][0]
		),
		row_original_1
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[2][0]
		),
		row_original_2
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[3][0]
		),
		row_original_3
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

inline matrix4x4f operator-(
	const matrix4x4f& left, const matrix4x4f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0(left[0].data());
	DirectX::XMFLOAT4 left_row_1(left[1].data());
	DirectX::XMFLOAT4 left_row_2(left[2].data());
	DirectX::XMFLOAT4 left_row_3(left[3].data());

	DirectX::XMFLOAT4 right_row_0(right[0].data());
	DirectX::XMFLOAT4 right_row_1(right[1].data());
	DirectX::XMFLOAT4 right_row_2(right[2].data());
	DirectX::XMFLOAT4 right_row_3(right[3].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 =
		DirectX::XMLoadFloat4(&left_row_3);

	DirectX::XMVECTOR row_argument_0 =
		DirectX::XMLoadFloat4(&right_row_0);
	DirectX::XMVECTOR row_argument_1 =
		DirectX::XMLoadFloat4(&right_row_1);
	DirectX::XMVECTOR row_argument_2 =
		DirectX::XMLoadFloat4(&right_row_2);
	DirectX::XMVECTOR row_argument_3 =
		DirectX::XMLoadFloat4(&right_row_3);

	row_original_0 = DirectX::XMVectorSubtract(
		row_original_0, row_argument_0
	);
	row_original_1 = DirectX::XMVectorSubtract(
		row_original_1, row_argument_1
	);
	row_original_2 = DirectX::XMVectorSubtract(
		row_original_2, row_argument_2
	);
	row_original_3 = DirectX::XMVectorSubtract(
		row_original_3, row_argument_3
	);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[0][0]
		),
		row_original_0
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[1][0]
		),
		row_original_1
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[2][0]
		),
		row_original_2
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[3][0]
		),
		row_original_3
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

inline matrix4x4f operator*(
	const matrix4x4f& left, const matrix4x4f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	const DirectX::XMMATRIX& m1 = left;
	const DirectX::XMMATRIX& m2 = right;
	auto temp = DirectX::XMMatrixMultiply(m1, m2);

	matrix4x4f result;
	base_mat4x4_t data;
	DirectX::XMStoreFloat4x4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

inline matrix4x4f
operator*(const matrix4x4f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0(left[0].data());
	DirectX::XMFLOAT4 left_row_1(left[1].data());
	DirectX::XMFLOAT4 left_row_2(left[2].data());
	DirectX::XMFLOAT4 left_row_3(left[3].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 =
		DirectX::XMLoadFloat4(&left_row_3);

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, value);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, value);
	row_original_2 =
		DirectX::XMVectorScale(row_original_2, value);
	row_original_3 =
		DirectX::XMVectorScale(row_original_3, value);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[0][0]
		),
		row_original_0
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[1][0]
		),
		row_original_1
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[2][0]
		),
		row_original_2
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[3][0]
		),
		row_original_3
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * value);
#endif
}

inline matrix4x4f
operator*(float value, const matrix4x4f& right) noexcept
{
	return operator*(right, value);
}

inline matrix4x4f
operator/(const matrix4x4f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0(left[0].data());
	DirectX::XMFLOAT4 left_row_1(left[1].data());
	DirectX::XMFLOAT4 left_row_2(left[2].data());
	DirectX::XMFLOAT4 left_row_3(left[3].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 =
		DirectX::XMLoadFloat4(&left_row_3);

	float factor = 1.f / value;

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, factor);
	row_original_2 =
		DirectX::XMVectorScale(row_original_2, factor);
	row_original_3 =
		DirectX::XMVectorScale(row_original_3, factor);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[0][0]
		),
		row_original_0
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[1][0]
		),
		row_original_1
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[2][0]
		),
		row_original_2
	);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(
			&result.Get_Base().m[3][0]
		),
		row_original_3
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / value);
#endif
}

// TODO: provide preprocessor for user implementation here like
// KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
inline matrix4x4f operator/(
	const matrix4x4f& left, const matrix4x4f& right
) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, if "
		"it is needed "
		"provide own version of a such operation"
	);
	return matrix4x4f();
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
