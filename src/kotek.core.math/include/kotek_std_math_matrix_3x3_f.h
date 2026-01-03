#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class matrix3x3f
{
public:
	matrix3x3f(
		float c0r0,
		float c0r1,
		float c0r2,
		float c1r0,
		float c1r1,
		float c1r2,
		float c2r0,
		float c2r1,
		float c2r2
	);
	matrix3x3f(const base_mat3x3_t& data);
	matrix3x3f(const matrix3x3f& data);
	matrix3x3f(const matrixnf_view_t& view);
	matrix3x3f(const matrixnf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	matrix3x3f(const DirectX::XMMATRIX& data);
#endif

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix3x3f(const vector1f& data);
	matrix3x3f(const vector2f& data);
	matrix3x3f(const vector3f& data);
	matrix3x3f(const vector4f& data);
	matrix3x3f(const vectornf_const_view_t& view);
	matrix3x3f(const vectornf_view_t& view);
	matrix3x3f(const matrix2x2f& data);
	matrix3x3f(const matrix4x4f& data);
#endif

	matrix3x3f(void);

	~matrix3x3f(void) = default;

	matrix3x3f& operator=(const matrix3x3f& data);
	matrix3x3f& operator=(const base_mat3x3_t& data);
	matrix3x3f& operator=(const matrixnf_view_t& view);
	matrix3x3f& operator=(const matrixnf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix3x3f& operator=(const matrix2x2f& data);
	matrix3x3f& operator=(const matrix4x4f& data);
	matrix3x3f& operator=(const vector1f& data);
	matrix3x3f& operator=(const vector2f& data);
	matrix3x3f& operator=(const vector3f& data);
	matrix3x3f& operator=(const vector4f& data);
	matrix3x3f& operator=(const vectornf_view_t& view) noexcept;
	matrix3x3f& operator=(const vectornf_const_view_t& view
	) noexcept;
#endif

	matrix3x3f& operator+=(const matrix3x3f& data) noexcept;
	matrix3x3f& operator+=(const base_mat3x3_t& data) noexcept;
	matrix3x3f& operator+=(const matrixnf_view_t& view
	) noexcept;
	matrix3x3f& operator+=(const matrixnf_const_view_t& view
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix3x3f& operator+=(const matrix2x2f& data) noexcept;
	matrix3x3f& operator+=(const matrix4x4f& data) noexcept;
	matrix3x3f& operator+=(const vector1f& data) noexcept;
	matrix3x3f& operator+=(const vector2f& data) noexcept;
	matrix3x3f& operator+=(const vector3f& data) noexcept;
	matrix3x3f& operator+=(const vector4f& data) noexcept;
	matrix3x3f& operator+=(const vectornf_view_t& view
	) noexcept;
	matrix3x3f& operator+=(const vectornf_const_view_t& view
	) noexcept;
#endif

	matrix3x3f& operator-=(const matrix3x3f& data) noexcept;
	matrix3x3f& operator-=(const base_mat3x3_t& data) noexcept;
	matrix3x3f& operator-=(const matrixnf_view_t& view
	) noexcept;
	matrix3x3f& operator-=(const matrixnf_const_view_t& view
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix3x3f& operator-=(const matrix2x2f& data) noexcept;
	matrix3x3f& operator-=(const matrix4x4f& data) noexcept;
	matrix3x3f& operator-=(const vector1f& data) noexcept;
	matrix3x3f& operator-=(const vector2f& data) noexcept;
	matrix3x3f& operator-=(const vector3f& data) noexcept;
	matrix3x3f& operator-=(const vector4f& data) noexcept;
	matrix3x3f& operator-=(const vectornf_view_t& view
	) noexcept;
	matrix3x3f& operator-=(const vectornf_const_view_t& view
	) noexcept;
#endif

	matrix3x3f& operator*=(const matrix3x3f& data) noexcept;
	matrix3x3f& operator*=(const matrixnf_view_t& view
	) noexcept;
	matrix3x3f& operator*=(const matrixnf_const_view_t& view
	) noexcept;
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix3x3f& operator*=(const matrix2x2f& data) noexcept;
	matrix3x3f& operator*=(const matrix4x4f& data) noexcept;
	matrix3x3f& operator*=(const vector1f& data) noexcept;
	matrix3x3f& operator*=(const vector2f& data) noexcept;
	matrix3x3f& operator*=(const vector3f& data) noexcept;
	matrix3x3f& operator*=(const vector4f& data) noexcept;
	matrix3x3f& operator*=(const vectornf_view_t& view
	) noexcept;
	matrix3x3f& operator*=(const vectornf_const_view_t& view
	) noexcept;
#endif

	matrix3x3f& operator*=(const base_mat3x3_t& data) noexcept;
	matrix3x3f& operator*=(float value) noexcept;

#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	matrix3x3f& operator/=(const matrix3x3f& data) noexcept;
	matrix3x3f& operator/=(const matrixnf_view_t& view
	) noexcept;
	matrix3x3f& operator/=(const matrixnf_const_view_t& view
	) noexcept;

	#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix3x3f& operator/=(const matrix2x2f& data) noexcept;
	matrix3x3f& operator/=(const matrix4x4f& data) noexcept;
	matrix3x3f& operator/=(const vector1f& data) noexcept;
	matrix3x3f& operator/=(const vector2f& data) noexcept;
	matrix3x3f& operator/=(const vector3f& data) noexcept;
	matrix3x3f& operator/=(const vector4f& data) noexcept;
	matrix3x3f& operator/=(const vectornf_view_t& view
	) noexcept;
	matrix3x3f& operator/=(const vectornf_const_view_t& view
	) noexcept;
	#endif
#endif

	matrix3x3f& operator/=(float value) noexcept;
	matrix3x3f operator+() const noexcept;
	matrix3x3f operator-() const noexcept;

	bool operator==(const matrix3x3f& data) const noexcept;
	bool operator!=(const matrix3x3f& data) noexcept;

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

	matrix3x3f& Set_Base(const base_mat3x3_t& data) noexcept;
	base_mat3x3_t& Get_Base(void) noexcept;
	const base_mat3x3_t& Get_Base(void) const noexcept;

private:
	base_mat3x3_t m_base;
};

inline matrix3x3f operator+(
	const matrix3x3f& left, const matrix3x3f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMFLOAT3 right_row_0(right[0].data());
	DirectX::XMFLOAT3 right_row_1(right[1].data());
	DirectX::XMFLOAT3 right_row_2(right[2].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat3(&left_row_2);

	DirectX::XMVECTOR row_argument_0 =
		DirectX::XMLoadFloat3(&right_row_0);
	DirectX::XMVECTOR row_argument_1 =
		DirectX::XMLoadFloat3(&right_row_1);
	DirectX::XMVECTOR row_argument_2 =
		DirectX::XMLoadFloat3(&right_row_2);

	row_original_0 =
		DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 =
		DirectX::XMVectorAdd(row_original_1, row_argument_1);
	row_original_2 =
		DirectX::XMVectorAdd(row_original_2, row_argument_2);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._21
		),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._31
		),
		row_original_2
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

inline matrix3x3f operator-(
	const matrix3x3f& left, const matrix3x3f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMFLOAT3 right_row_0(right[0].data());
	DirectX::XMFLOAT3 right_row_1(right[1].data());
	DirectX::XMFLOAT3 right_row_2(right[2].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat3(&left_row_2);

	DirectX::XMVECTOR row_argument_0 =
		DirectX::XMLoadFloat3(&right_row_0);
	DirectX::XMVECTOR row_argument_1 =
		DirectX::XMLoadFloat3(&right_row_1);
	DirectX::XMVECTOR row_argument_2 =
		DirectX::XMLoadFloat3(&right_row_2);

	row_original_0 = DirectX::XMVectorSubtract(
		row_original_0, row_argument_0
	);
	row_original_1 = DirectX::XMVectorSubtract(
		row_original_1, row_argument_1
	);
	row_original_2 = DirectX::XMVectorSubtract(
		row_original_2, row_argument_2
	);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._21
		),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._31
		),
		row_original_2
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

inline matrix3x3f operator*(
	const matrix3x3f& left, const matrix3x3f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX m1 = left;
	DirectX::XMMATRIX m2 = right;
	auto temp = DirectX::XMMatrixMultiply(m1, m2);

	matrix3x3f result;
	base_mat3x3_t data;
	DirectX::XMStoreFloat3x3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

inline matrix3x3f
operator*(const matrix3x3f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat3(&left_row_2);

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, value);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, value);
	row_original_2 =
		DirectX::XMVectorScale(row_original_2, value);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._21
		),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._31
		),
		row_original_2
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * value);
#endif
}

inline matrix3x3f
operator*(float value, const matrix3x3f& right) noexcept
{
	return operator*(right, value);
}

inline matrix3x3f
operator/(const matrix3x3f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 =
		DirectX::XMLoadFloat3(&left_row_2);

	float factor = 1.f / value;

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, factor);
	row_original_2 =
		DirectX::XMVectorScale(row_original_2, factor);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._21
		),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(
			&result.Get_Base()._31
		),
		row_original_2
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / value);
#endif
}

#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
inline matrix3x3f operator/(
	const matrix3x3f& left, const matrix3x3f& right
) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, if "
		"it is needed "
		"provide own version of a such operation"
	);
	return matrix3x3f();
}
#endif

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
