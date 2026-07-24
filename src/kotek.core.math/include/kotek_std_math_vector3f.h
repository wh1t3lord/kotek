#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector3f
{
public:
	vector3f(float x, float y, float z);
	vector3f(float* p_arr3, math_id_t size = 3);
	vector3f(const float* p_arr3, math_id_t size = 3);
	vector3f(const vectornf_view_t& view);
	vector3f(const vectornf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector3f(float x);
	vector3f(float x, float y);
	vector3f(float x, float y, float z, float w);
	vector3f(const matrixnf_view_t& view_mat);
	vector3f(const matrixnf_const_view_t& view_mat);
	vector3f(const vector1f& data);
	vector3f(const vector2f& data);
	vector3f(const vector4f& data);
	vector3f(const vector1f& data, float y);
	vector3f(const vector1f& data, float y, float z);
	vector3f(const vector2f& data, float z);
#endif

	vector3f(const base_vec3_t& data);
	vector3f(const vector3f& data);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	vector3f(const DirectX::XMVECTOR& xmvec);
#endif

	vector3f(void);

	~vector3f(void) = default;

	vector3f& operator=(const vector3f& data) noexcept;
	vector3f& operator=(const vectornf_view_t& data) noexcept;
	vector3f& operator=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector3f& operator=(const matrixnf_view_t& data) noexcept;
	vector3f& operator=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector3f& operator+=(const vector3f& data) noexcept;

	vector3f& operator+=(const vectornf_view_t& data) noexcept;
	vector3f& operator+=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector3f& operator+=(const matrixnf_view_t& data) noexcept;
	vector3f& operator+=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector3f& operator+=(const base_vec3_t& data) noexcept;

	vector3f& operator-=(const vector3f& data) noexcept;

	vector3f& operator-=(const vectornf_view_t& data) noexcept;
	vector3f& operator-=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector3f& operator-=(const matrixnf_view_t& data) noexcept;
	vector3f& operator-=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector3f& operator-=(const base_vec3_t& data) noexcept;

	vector3f& operator*=(const vector3f& data) noexcept;

	vector3f& operator*=(const vectornf_view_t& data) noexcept;
	vector3f& operator*=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector3f& operator*=(const matrixnf_view_t& data) noexcept;
	vector3f& operator*=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector3f& operator*=(const base_vec3_t& data) noexcept;
	vector3f& operator*=(float value) noexcept;

	vector3f& operator/=(const vector3f& data) noexcept;

	vector3f& operator/=(const vectornf_view_t& data) noexcept;
	vector3f& operator/=(const vectornf_const_view_t& data
	) noexcept;
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector3f& operator/=(const matrixnf_view_t& data) noexcept;
	vector3f& operator/=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector3f& operator/=(const base_vec3_t& data) noexcept;

	vector3f& operator/=(float value) noexcept;

	vector3f& operator%=(float value) noexcept;
	vector3f& operator%=(const vector3f& data) noexcept;

	vector3f operator+() const noexcept;
	vector3f operator-() const noexcept;

	bool operator==(const vector3f& data) const noexcept;
	bool operator!=(const vector3f& data) const noexcept;

	float operator[](unsigned char index) const;
	float& operator[](unsigned char index);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMVECTOR() const noexcept;
#endif

	float
	e(math_id_t column_id, math_id_t row_id) const noexcept;
	float& e(math_id_t column_id, math_id_t row_id) noexcept;

	float x(void) const noexcept;
	float& x(void) noexcept;

	float y(void) const noexcept;
	float& y(void) noexcept;

	float z(void) const noexcept;
	float& z(void) noexcept;

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	void set(float x, float y, float z) noexcept;

	constexpr math_id_t size_of(void) noexcept;
	constexpr math_id_t get_column_count(void) const noexcept;
	constexpr math_id_t get_row_count(void) const noexcept;

	vector3f& Set_Base(const base_vec3_t& data) noexcept;

	base_vec3_t& Get_Base(void) noexcept;
	const base_vec3_t& Get_Base(void) const noexcept;

private:
	base_vec3_t m_base;
};

inline vector3f
operator+(const vector3f& left, const vector3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	const auto& temp = DirectX::XMVectorAdd(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() + right.Get_Base();
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector3f operator+(
	const vector3f left, const matrixnf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator+(
	const matrixnf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator+(
	const vector3f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator+(
	const matrixnf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}
#endif

inline vector3f operator+(
	const vector3f& left, const vectornf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator+(
	const vectornf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator+(
	const vector3f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator+(
	const vectornf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f
operator-(const vector3f& left, const vector3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	const auto& temp = DirectX::XMVectorSubtract(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() - right.Get_Base();
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector3f operator-(
	const vector3f left, const matrixnf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator-(
	const matrixnf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator-(
	const vector3f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator-(
	const matrixnf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}
#endif

inline vector3f operator-(
	const vector3f& left, const vectornf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator-(
	const vectornf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator-(
	const vector3f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator-(
	const vectornf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f
operator*(const vector3f& left, const vector3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	const auto& temp = DirectX::XMVectorMultiply(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() * right.Get_Base();
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector3f operator*(
	const vector3f left, const matrixnf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator*(
	const matrixnf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator*(
	const vector3f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator*(
	const matrixnf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}
#endif

inline vector3f operator*(
	const vector3f& left, const vectornf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator*(
	const vectornf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator*(
	const vector3f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator*(
	const vectornf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f
operator*(const vector3f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	const auto& temp = DirectX::XMVectorScale(v1, right);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() * right;
#endif
}

inline vector3f
operator*(float left, const vector3f& right) noexcept
{
	return operator*(right, left);
}

inline vector3f
operator/(const vector3f& left, const vector3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	const auto& temp = DirectX::XMVectorDivide(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() / right.Get_Base();
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector3f operator/(
	const vector3f left, const matrixnf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator/(
	const matrixnf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator/(
	const vector3f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator/(
	const matrixnf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}
#endif

inline vector3f operator/(
	const vector3f& left, const vectornf_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator/(
	const vectornf_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f operator/(
	const vector3f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector3f();
}

inline vector3f operator/(
	const vectornf_const_view_t& view, const vector3f& right
) noexcept
{
	return vector3f();
}

inline vector3f
operator/(const vector3f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	const auto& temp = DirectX::XMVectorScale(v1, 1.f / right);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() / right;
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
