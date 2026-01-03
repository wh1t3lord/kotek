#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector2f
{
public:
	vector2f(float x, float y);

	vector2f(float* p_arr2, math_id_t size = 2);
	vector2f(const float* p_arr2, math_id_t size = 2);

	vector2f(const vectornf_view_t& view);
	vector2f(const vectornf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector2f(const matrixnf_view_t& view_mat);
	vector2f(const matrixnf_const_view_t& view_mat);
	vector2f(float x);
	vector2f(float x, float y, float z);
	vector2f(float x, float y, float z, float w);
	vector2f(const vector1f& data);
	vector2f(const vector1f& data, float y);
	vector2f(const vector3f& data);
	vector2f(const vector4f& data);
#endif

	vector2f(const base_vec2_t& data);
	vector2f(const vector2f& data);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	vector2f(const DirectX::XMVECTOR& vec);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

	vector2f(void);

	~vector2f(void) = default;

	vector2f& operator=(const vector2f& data) noexcept;
	vector2f& operator=(const vectornf_view_t& data) noexcept;
	vector2f& operator=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector2f& operator=(const matrixnf_view_t& data) noexcept;
	vector2f& operator=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector2f& operator+=(const vector2f& data) noexcept;

	vector2f& operator+=(const vectornf_view_t& data) noexcept;
	vector2f& operator+=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector2f& operator+=(const matrixnf_view_t& data) noexcept;
	vector2f& operator+=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector2f& operator+=(const base_vec2_t& data) noexcept;

	vector2f& operator-=(const vector2f& data) noexcept;

	vector2f& operator-=(const vectornf_view_t& data) noexcept;
	vector2f& operator-=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector2f& operator-=(const matrixnf_view_t& data) noexcept;
	vector2f& operator-=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector2f& operator-=(const base_vec2_t& data) noexcept;

	vector2f& operator*=(const vector2f& data) noexcept;

	vector2f& operator*=(const vectornf_view_t& data) noexcept;
	vector2f& operator*=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector2f& operator*=(const matrixnf_view_t& data) noexcept;
	vector2f& operator*=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector2f& operator*=(const base_vec2_t& data) noexcept;
	vector2f& operator*=(float value) noexcept;

	vector2f& operator/=(const vector2f& data) noexcept;

	vector2f& operator/=(const vectornf_view_t& data) noexcept;
	vector2f& operator/=(const vectornf_const_view_t& data
	) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector2f& operator/=(const matrixnf_view_t& data) noexcept;
	vector2f& operator/=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector2f& operator/=(const base_vec2_t& data) noexcept;
	vector2f& operator/=(float value) noexcept;
	vector2f& operator%=(float value) noexcept;
	vector2f& operator%=(const vector2f& data) noexcept;

	vector2f operator+() const noexcept;
	vector2f operator-() const noexcept;

	bool operator==(const vector2f& data) const noexcept;
	bool operator!=(const vector2f& data) const noexcept;

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

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	void set(float x, float y);

	constexpr math_id_t size_of(void) noexcept;
	constexpr math_id_t get_column_count(void) const noexcept;
	constexpr math_id_t get_row_count(void) const noexcept;

	vector2f& Set_Base(const base_vec2_t& data) noexcept;

	base_vec2_t& Get_Base(void) noexcept;

	const base_vec2_t& Get_Base(void) const noexcept;

private:
	base_vec2_t m_base;
};

inline vector2f
operator+(const vector2f& left, const vector2f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorAdd(v1, v2);

	vector2f result;
	base_vec2_t data;

	DirectX::XMStoreFloat2(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector2f operator+(
	const vector2f left, const matrixnf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator+(
	const matrixnf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator+(
	const vector2f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator+(
	const matrixnf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}
#endif

inline vector2f operator+(
	const vector2f& left, const vectornf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator+(
	const vectornf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator+(
	const vector2f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator+(
	const vectornf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f
operator-(const vector2f& left, const vector2f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorSubtract(v1, v2);

	vector2f result;
	base_vec2_t data;

	DirectX::XMStoreFloat2(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector2f operator-(
	const vector2f& left, const matrixnf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator-(
	const matrixnf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator-(
	const vector2f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator-(
	const matrixnf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}
#endif

inline vector2f operator-(
	const vector2f& left, const vectornf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator-(
	const vectornf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator-(
	const vector2f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator-(
	const vectornf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f
operator*(const vector2f& left, const vector2f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorMultiply(v1, v2);

	vector2f result;
	base_vec2_t data;

	DirectX::XMStoreFloat2(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector2f operator*(
	const vector2f& left, const matrixnf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator*(
	const matrixnf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator*(
	const vector2f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator*(
	const matrixnf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}
#endif

inline vector2f operator*(
	const vector2f& left, const vectornf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator*(
	const vectornf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator*(
	const vector2f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator*(
	const vectornf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f
operator*(const vector2f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	auto temp = DirectX::XMVectorScale(v1, right);

	vector2f result;
	base_vec2_t data;

	DirectX::XMStoreFloat2(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right);
#endif
}

inline vector2f
operator*(float left, const vector2f& right) noexcept
{
	return operator*(right, left);
}

inline vector2f
operator/(const vector2f& left, const vector2f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorDivide(v1, v2);

	vector2f result;
	base_vec2_t data;

	DirectX::XMStoreFloat2(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / right.Get_Base());
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
inline vector2f operator/(
	const vector2f& left, const matrixnf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator/(
	const matrixnf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator/(
	const vector2f& left, const matrixnf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator/(
	const matrixnf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}
#endif

inline vector2f operator/(
	const vector2f& left, const vectornf_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator/(
	const vectornf_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f operator/(
	const vector2f& left, const vectornf_const_view_t& view
) noexcept
{
	return vector2f();
}

inline vector2f operator/(
	const vectornf_const_view_t& view, const vector2f& right
) noexcept
{
	return vector2f();
}

inline vector2f
operator/(const vector2f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return operator*(left, 1.f / right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / right);
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
