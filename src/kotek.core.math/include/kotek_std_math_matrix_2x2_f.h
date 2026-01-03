#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class matrix2x2f
{
public:
	matrix2x2f(float c0r0, float c0r1, float c1r0, float c1r1);
	matrix2x2f(const base_mat2x2_t& data);
	matrix2x2f(const matrix2x2f& data);
	matrix2x2f(void);

	~matrix2x2f(void) = default;

	matrix2x2f& operator=(const matrix2x2f& data);
	matrix2x2f& operator=(const base_mat2x2_t& data);

	matrix2x2f& operator+=(const matrix2x2f& data) noexcept;
	matrix2x2f& operator+=(const base_mat2x2_t& data) noexcept;

	matrix2x2f& operator-=(const matrix2x2f& data) noexcept;
	matrix2x2f& operator-=(const base_mat2x2_t& data) noexcept;

	matrix2x2f& operator*=(const matrix2x2f& data) noexcept;
	matrix2x2f& operator*=(const base_mat2x2_t& data) noexcept;
	matrix2x2f& operator*=(float value) noexcept;

	// TODO: provide preprocessor for user implementation here
	// like
	// KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	matrix2x2f& operator/=(const matrix2x2f& data) noexcept;
	matrix2x2f& operator/=(const matrix3x3f& data) noexcept;
	matrix2x2f& operator/=(const matrix4x4f& data) noexcept;
	matrix2x2f& operator/=(const vector2f& data) noexcept;
	matrix2x2f& operator/=(const vector3f& data) noexcept;
	matrix2x2f& operator/=(const vector4f& data) noexcept;

	matrix2x2f& operator/=(float value) noexcept;
	matrix2x2f& operator/=(const vector1f& vec) noexcept;

	matrix2x2f operator+() const noexcept;
	matrix2x2f operator-() const noexcept;

	bool operator==(const matrix2x2f& data) const noexcept;

	bool operator!=(const matrix2x2f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	/// \~english @brief Cast operator for compatibility with
	/// DirectX Math library (DXM)
	/// @param nothing as input for passing
	/// @return casted DirectX::XMMatrix through
	/// DirectX::XMLoadFloat3x3
	operator DirectX::XMMATRIX(void) const noexcept
	{
		return DirectX::XMLoadFloat3x3(&this->m_base);
	}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#else
	#error Unknown math library
#endif

	float
	e(math_id_t column_id, math_id_t row_id) const noexcept;
	float& e(math_id_t column_id, math_id_t row_id) noexcept;

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	constexpr math_id_t size_of(void) const noexcept;
	constexpr math_id_t get_column_count(void) const noexcept;
	constexpr math_id_t get_row_count(void) const noexcept;

	matrix2x2f& Set_Base(const base_mat2x2_t& data) noexcept;
	base_mat2x2_t& Get_Base(void) noexcept;
	const base_mat2x2_t& Get_Base(void) const noexcept;

private:
	base_mat2x2_t m_base;
};

inline matrix2x2f operator+(
	const matrix2x2f& left, const matrix2x2f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT2 left_row_0 = {
		left.Get_00(), left.Get_01()
	};
	DirectX::XMFLOAT2 left_row_1 = {
		left.Get_10(), left.Get_11()
	};

	DirectX::XMFLOAT2 right_row_0 = {
		right.Get_00(), right.Get_01()
	};
	DirectX::XMFLOAT2 right_row_1 = {
		right.Get_10(), right.Get_11()
	};

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat2(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat2(&left_row_1);

	DirectX::XMVECTOR row_argument_0 =
		DirectX::XMLoadFloat2(&right_row_0);
	DirectX::XMVECTOR row_argument_1 =
		DirectX::XMLoadFloat2(&right_row_1);

	row_original_0 =
		DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 =
		DirectX::XMVectorAdd(row_original_1, row_argument_1);

	matrix2x2f result;

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._21
		),
		row_original_1
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

inline matrix2x2f operator-(
	const matrix2x2f& left, const matrix2x2f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT2 left_row_0 = {
		left.Get_00(), left.Get_01()
	};
	DirectX::XMFLOAT2 left_row_1 = {
		left.Get_10(), left.Get_11()
	};

	DirectX::XMFLOAT2 right_row_0 = {
		right.Get_00(), right.Get_01()
	};
	DirectX::XMFLOAT2 right_row_1 = {
		right.Get_10(), right.Get_11()
	};

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat2(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat2(&left_row_1);

	DirectX::XMVECTOR row_argument_0 =
		DirectX::XMLoadFloat2(&right_row_0);
	DirectX::XMVECTOR row_argument_1 =
		DirectX::XMLoadFloat2(&right_row_1);

	row_original_0 = DirectX::XMVectorSubtract(
		row_original_0, row_argument_0
	);
	row_original_1 = DirectX::XMVectorSubtract(
		row_original_1, row_argument_1
	);

	matrix2x2f result;

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._21
		),
		row_original_1
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

inline matrix2x2f operator*(
	const matrix2x2f& left, const matrix2x2f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX m1 = left;
	DirectX::XMMATRIX m2 = right;
	auto temp = DirectX::XMMatrixMultiply(m1, m2);

	matrix2x2f result;
	base_mat3x3_t data;
	DirectX::XMStoreFloat3x3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

inline matrix2x2f
operator*(const matrix2x2f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT2 left_row_0 = {
		left.Get_00(), left.Get_01()
	};
	DirectX::XMFLOAT2 left_row_1 = {
		left.Get_10(), left.Get_11()
	};

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat2(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat2(&left_row_1);

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, value);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, value);

	matrix2x2f result;

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._21
		),
		row_original_1
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * value);
#endif
}

inline matrix2x2f
operator*(float value, const matrix2x2f& right) noexcept
{
	return operator*(right, value);
}

inline matrix2x2f
operator/(const matrix2x2f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT2 left_row_0 = {
		left.Get_00(), left.Get_01()
	};
	DirectX::XMFLOAT2 left_row_1 = {
		left.Get_10(), left.Get_11()
	};

	DirectX::XMVECTOR row_original_0 =
		DirectX::XMLoadFloat2(&left_row_0);
	DirectX::XMVECTOR row_original_1 =
		DirectX::XMLoadFloat2(&left_row_1);

	float factor = 1.f / value;

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, factor);

	matrix2x2f result;

	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._11
		),
		row_original_0
	);
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(
			&result.Get_Base()._21
		),
		row_original_1
	);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / value);
#endif
}

// TODO: provide preprocessor for user implementation here like
// KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
inline matrix2x2f operator/(
	const matrix2x2f& left, const matrix2x2f& right
) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, if "
		"it is needed "
		"provide own version of a such operation"
	);
	return matrix2x2f();
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
