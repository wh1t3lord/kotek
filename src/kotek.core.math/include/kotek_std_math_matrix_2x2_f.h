#pragma once

#include "kotek_std_alias_math.h"

#include "kotek_std_math_vector2f.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class matrix2x2f
{
public:
	matrix2x2f(float c0r0, float c0r1, float c1r0, float c1r1);
	matrix2x2f(const base_mat2x2_t& data);
	matrix2x2f(const matrix2x2f& data);
	matrix2x2f(const matrixnf_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix2x2f(const matrix3x3f& data);
	matrix2x2f(const matrix4x4f& data);
	matrix2x2f(const vector1f& data);
	matrix2x2f(const vector2f& data);
	matrix2x2f(const vector3f& data);
	matrix2x2f(const vector4f& data);
#endif

	matrix2x2f(void);

	~matrix2x2f(void) = default;

	matrix2x2f& operator=(const matrix2x2f& data);
	matrix2x2f& operator=(const matrixnf_view_t& view);
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix2x2f& operator=(const matrix3x3f& data);
	matrix2x2f& operator=(const matrix4x4f& data);
	matrix2x2f& operator=(const vector1f& data);
	matrix2x2f& operator=(const vector2f& data);
	matrix2x2f& operator=(const vector3f& data);
	matrix2x2f& operator=(const vector4f& data);
#endif

	matrix2x2f& operator=(const base_mat2x2_t& data);

	matrix2x2f& operator+=(const matrix2x2f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix2x2f& operator+=(const matrix3x3f& data) noexcept;
	matrix2x2f& operator+=(const matrix4x4f& data) noexcept;
	matrix2x2f& operator+=(const vector1f& data) noexcept;
	matrix2x2f& operator+=(const vector2f& data) noexcept;
	matrix2x2f& operator+=(const vector3f& data) noexcept;
	matrix2x2f& operator+=(const vector4f& data) noexcept;
#endif

	matrix2x2f& operator+=(const base_mat2x2_t& data) noexcept;

	matrix2x2f& operator-=(const matrix2x2f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix2x2f& operator-=(const matrix3x3f& data) noexcept;
	matrix2x2f& operator-=(const matrix4x4f& data) noexcept;
	matrix2x2f& operator-=(const vector1f& data) noexcept;
	matrix2x2f& operator-=(const vector2f& data) noexcept;
	matrix2x2f& operator-=(const vector3f& data) noexcept;
	matrix2x2f& operator-=(const vector4f& data) noexcept;
#endif

	matrix2x2f& operator-=(const base_mat2x2_t& data) noexcept;

	matrix2x2f& operator*=(const matrix2x2f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix2x2f& operator*=(const matrix3x3f& data) noexcept;
	matrix2x2f& operator*=(const matrix4x4f& data) noexcept;
	matrix2x2f& operator*=(const vector1f& data) noexcept;
	matrix2x2f& operator*=(const vector2f& data) noexcept;
	matrix2x2f& operator*=(const vector3f& data) noexcept;
	matrix2x2f& operator*=(const vector4f& data) noexcept;
#endif

	matrix2x2f& operator*=(const base_mat2x2_t& data) noexcept;
	matrix2x2f& operator*=(float value) noexcept;

	// TODO: provide preprocessor for user implementation here
	// like
	// KOTEK_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	matrix2x2f& operator/=(const matrix2x2f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	matrix2x2f& operator/=(const matrix3x3f& data) noexcept;
	matrix2x2f& operator/=(const matrix4x4f& data) noexcept;
	matrix2x2f& operator/=(const vector2f& data) noexcept;
	matrix2x2f& operator/=(const vector3f& data) noexcept;
	matrix2x2f& operator/=(const vector4f& data) noexcept;
#endif

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

#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)

#else
	#error unknown math library
#endif

	float
	e(math_id_t column_id, math_id_t row_id) const noexcept;
	float& e(math_id_t column_id, math_id_t row_id) noexcept;

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	vectornf_view_t operator[](math_id_t column_id) noexcept;
	vectornf_const_view_t operator[](math_id_t column_id
	) const noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	math_id_t size_of(void) const noexcept;
	math_id_t get_column_count(void) const noexcept;
	math_id_t get_row_count(void) const noexcept;

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
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._21
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&right.Get_Base()._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&right.Get_Base()._21
		)
	);

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
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return (left.Get_Base() + right.Get_Base());
#else
	#error unknown math library
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline matrix2x2f operator+(
	const matrix2x2f& left, const matrix3x3f& right
) noexcept
{
	return operator+(left, matrix2x2f(right));
}

inline matrix2x2f operator+(
	const matrix2x2f& left, const matrix4x4f& right
) noexcept
{
	return operator+(left, matrix2x2f(right));
}

inline matrix2x2f operator+(
	const matrix2x2f& left, const vector1f& right
) noexcept
{
	return operator+(left, matrix2x2f(right));
}

inline matrix2x2f operator+(
	const matrix2x2f& left, const vector2f& right
) noexcept
{
	return operator+(left, matrix2x2f(right));
}

inline matrix2x2f operator+(
	const matrix2x2f& left, const vector3f& right
) noexcept
{
	return operator+(left, matrix2x2f(right));
}

inline matrix2x2f operator+(
	const matrix2x2f& left, const vector4f& right
) noexcept
{
	return operator+(left, matrix2x2f(right));
}
#endif

inline matrix2x2f operator-(
	const matrix2x2f& left, const matrix2x2f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._21
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&right.Get_Base()._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&right.Get_Base()._21
		)
	);

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
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return (left.Get_Base() - right.Get_Base());
#else
	#error unknown math library
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline matrix2x2f operator-(
	const matrix2x2f& left, const matrix3x3f& right
) noexcept
{
	return operator-(left, matrix2x2f(right));
}

inline matrix2x2f operator-(
	const matrix2x2f& left, const matrix4x4f& right
) noexcept
{
	return operator-(left, matrix2x2f(right));
}

inline matrix2x2f operator-(
	const matrix2x2f& left, const vector1f& right
) noexcept
{
	return operator-(left, matrix2x2f(right));
}

inline matrix2x2f operator-(
	const matrix2x2f& left, const vector2f& right
) noexcept
{
	return operator-(left, matrix2x2f(right));
}

inline matrix2x2f operator-(
	const matrix2x2f& left, const vector3f& right
) noexcept
{
	return operator-(left, matrix2x2f(right));
}

inline matrix2x2f operator-(
	const matrix2x2f& left, const vector4f& right
) noexcept
{
	return operator-(left, matrix2x2f(right));
}
#endif

inline matrix2x2f operator*(
	const matrix2x2f& left, const matrix2x2f& right
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	// m_base stores columns contiguously (m_base.m[column][row]),
	// so a loaded XMMATRIX is the TRANSPOSE of the logical matrix;
	// (L*R)^T == R^T * L^T, hence the swapped operand order here and
	// everywhere below
	DirectX::XMMATRIX m1 = right;
	DirectX::XMMATRIX m2 = left;
	auto temp = DirectX::XMMatrixMultiply(m1, m2);

	matrix2x2f result;
	base_mat3x3_t data;
	DirectX::XMStoreFloat3x3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return (left.Get_Base() * right.Get_Base());
#else
	#error unknown math library
#endif
}

inline matrix2x2f
operator*(const matrix2x2f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._21
		)
	);

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
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return (left.Get_Base() * value);
#else
	#error unknown math library
#endif
}

inline matrix2x2f
operator*(float value, const matrix2x2f& right) noexcept
{
	return operator*(right, value);
}

inline vector2f
operator*(const matrix2x2f& left, const vector2f& vec)
{
#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	return left.Get_Base() * vec.Get_Base();
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	// logical result is M*v; with the loaded XMMATRIX being M^T the
	// same components come out of v*(M^T)
	DirectX::XMMATRIX m = left;
	DirectX::XMVECTOR v =
		DirectX::XMVectorSet(vec.x(), vec.y(), 0.0f, 0.0f);
	DirectX::XMVECTOR result = DirectX::XMVector4Transform(v, m);

	vector2f casted;
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&casted.Get_Base()),
		result
	);

	return casted;
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return left.Get_Base() * vec.Get_Base();
#else
	#error unknown math library
#endif
}

inline vector2f
operator*(const vector2f& vec, const matrix2x2f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	return vec.Get_Base() * right.Get_Base();
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	// logical result is v*M == (M^T)*v; transposing the loaded
	// M^T back to M keeps XMVector4Transform (v*M convention)
	DirectX::XMMATRIX m = right;
	DirectX::XMVECTOR v =
		DirectX::XMVectorSet(vec.x(), vec.y(), 0.0f, 0.0f);
	DirectX::XMVECTOR result = DirectX::XMVector4Transform(
		v, DirectX::XMMatrixTranspose(m)
	);

	vector2f casted;
	DirectX::XMStoreFloat2(
		reinterpret_cast<DirectX::XMFLOAT2*>(&casted.Get_Base()),
		result
	);

	return casted;
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return vec.Get_Base() * right.Get_Base();
#else
	#error unknown math library
#endif
}

inline vector2f
operator*(const matrix2x2f& left, const vectornf_view_t& view)
{
#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	return left * vector2f(view);
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	return left * vector2f(view);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return left * vector2f(view);
#else
	#error unknown math library
#endif
}

inline vector2f
operator*(const vectornf_view_t& view, const matrix2x2f& right)
{
#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	return right * vector2f(view);
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	return right * vector2f(view);
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return right * vector2f(view);
#else
	#error unknown math library
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline matrix2x2f operator*(
	const matrix2x2f& left, const matrix3x3f& right
) noexcept
{
	return operator*(left, matrix2x2f(right));
}

inline matrix2x2f operator*(
	const matrix2x2f& left, const matrix4x4f& right
) noexcept
{
	return operator*(left, matrix2x2f(right));
}

inline matrix2x2f operator*(
	const matrix2x2f& left, const vector1f& right
) noexcept
{
	return operator*(left, vector2f(right));
}

inline matrix2x2f operator*(
	const matrix2x2f& left, const vector2f& right
) noexcept
{
	#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		#error todo: impl
	#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	glm::vec2 res = left.Get_Base() * right.Get_Base();
	return matrix2x2f(res);
	#endif
}

inline matrix2x2f operator*(
	const matrix2x2f& left, const vector3f& right
) noexcept
{
	return operator*(left, vector2f(right));
}

inline matrix2x2f operator*(
	const matrix2x2f& left, const vector4f& right
) noexcept
{
	return operator*(left, vector2f(right));
}
#endif

inline matrix2x2f
operator/(const matrix2x2f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat2(
		reinterpret_cast<const DirectX::XMFLOAT2*>(
			&left.Get_Base()._21
		)
	);

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
#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)
	return (left.Get_Base() / value);
#else
	#error unknown math library
#endif
}

#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
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

	#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline matrix2x2f operator/(
	const matrix2x2f& left, const matrix3x3f& right
) noexcept
{
	return operator/(left, matrix2x2f(right));
}

inline matrix2x2f operator/(
	const matrix2x2f& left, const matrix4x4f& right
) noexcept
{
	return operator/(left, matrix2x2f(right));
}

inline matrix2x2f operator/(
	const matrix2x2f& left, const vector1f& right
) noexcept
{
	return matrix2x2f();
}

inline matrix2x2f operator/(
	const matrix2x2f& left, const vector2f& right
) noexcept
{
	return matrix2x2f();
}

inline matrix2x2f operator/(
	const matrix2x2f& left, const vector3f& right
) noexcept
{
	return matrix2x2f();
}

inline matrix2x2f operator/(
	const matrix2x2f& left, const vector4f& right
) noexcept
{
	return matrix2x2f();
}
	#endif

#endif

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
