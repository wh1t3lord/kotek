#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector4f
{
public:
	vector4f(float x, float y, float z, float w);
	vector4f(float* p_arr4, math_id_t size = 4);
	vector4f(const float* p_arr4, math_id_t size = 4);
	vector4f(const vectornf_view_t& view);
	vector4f(const vectornf_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector4f(float x);
	vector4f(float x, float y);
	vector4f(float x, float y, float z);
	vector4f(const matrixnf_view_t& view_mat);
	vector4f(const matrixnf_const_view_t& view_mat);
	vector4f(const vector1f& data);
	vector4f(const vector1f& data, float y);
	vector4f(const vector1f& data, float y, float z);
	vector4f(const vector1f& data, float y, float z, float w);
	vector4f(const vector2f& data);
	vector4f(const vector2f& data, float z);
	vector4f(const vector2f& data, float z, float w);
	vector4f(const vector3f& data);
	vector4f(const vector3f& data, float w);
#endif

	vector4f(const base_vec4_t& data);
	vector4f(const vector4f& data);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	vector4f(const DirectX::XMVECTOR& vec);
#endif

	vector4f(void);

	~vector4f(void) = default;

	vector4f& operator=(const vector4f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector4f& operator=(const matrixnf_view_t& data) noexcept;
	vector4f& operator=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector4f& operator=(const vectornf_view_t& data) noexcept;
	vector4f& operator=(const vectornf_const_view_t& data
	) noexcept;

	vector4f& operator+=(const vector4f& data) noexcept;
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector4f& operator+=(const matrixnf_view_t& data) noexcept;
	vector4f& operator+=(const matrixnf_const_view_t& data
	) noexcept;
#endif
	vector4f& operator+=(const vectornf_view_t& data) noexcept;
	vector4f& operator+=(const vectornf_const_view_t& data
	) noexcept;

	vector4f& operator+=(const base_vec4_t& data) noexcept;

	vector4f& operator-=(const vector4f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector4f& operator-=(const matrixnf_view_t& data) noexcept;
	vector4f& operator-=(const matrixnf_const_view_t& data
	) noexcept;
#endif
	vector4f& operator-=(const vectornf_view_t& data) noexcept;
	vector4f& operator-=(const vectornf_const_view_t& data
	) noexcept;

	vector4f& operator-=(const base_vec4_t& data) noexcept;

	vector4f& operator*=(const vector4f& data) noexcept;
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector4f& operator*=(const matrixnf_view_t& data) noexcept;
	vector4f& operator*=(const matrixnf_const_view_t& data
	) noexcept;
#endif
	vector4f& operator*=(const vectornf_view_t& data) noexcept;
	vector4f& operator*=(const vectornf_const_view_t& data
	) noexcept;

	vector4f& operator*=(const base_vec4_t& data) noexcept;

	vector4f& operator*=(float value) noexcept;

	vector4f& operator/=(const vector4f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	vector4f& operator/=(const matrixnf_view_t& data) noexcept;
	vector4f& operator/=(const matrixnf_const_view_t& data
	) noexcept;
#endif

	vector4f& operator/=(const vectornf_view_t& data) noexcept;
	vector4f& operator/=(const vectornf_const_view_t& data
	) noexcept;

	vector4f& operator/=(const base_vec4_t& data) noexcept;

	vector4f& operator/=(float value) noexcept;

	vector4f& operator%=(float value) noexcept;

	vector4f& operator%=(const vector4f& data) noexcept;

	vector4f operator+() const noexcept;
	vector4f operator-() const noexcept;

	bool operator==(const vector4f& data) const noexcept;
	bool operator!=(const vector4f& data) const noexcept;
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

	float w(void) const noexcept;
	float& w(void) noexcept;

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	void set(float x, float y, float z, float w);

	constexpr math_id_t size_of(void) noexcept;
	constexpr math_id_t get_column_count(void) const noexcept;
	constexpr math_id_t get_row_count(void) const noexcept;

	vector4f& Set_Base(const base_vec4_t& data) noexcept;
	base_vec4_t& Get_Base(void) noexcept;
	const base_vec4_t& Get_Base(void) const noexcept;

private:
	base_vec4_t m_base;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

inline vector4f
operator+(const vector4f& left, const vector4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorAdd(v1, v2);

	vector4f result;
	base_vec4_t data;

	DirectX::XMStoreFloat4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

inline vector4f
operator-(const vector4f& left, const vector4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorSubtract(v1, v2);

	vector4f result;
	base_vec4_t data;

	DirectX::XMStoreFloat4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

inline vector4f
operator*(const vector4f& left, const vector4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorMultiply(v1, v2);

	vector4f result;
	base_vec4_t data;

	DirectX::XMStoreFloat4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

inline vector4f
operator*(const vector4f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	auto temp = DirectX::XMVectorScale(v1, right);

	vector4f result;
	base_vec4_t data;

	DirectX::XMStoreFloat4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right);
#endif
}

inline vector4f
operator*(float left, const vector4f& right) noexcept
{
	return operator*(right, left);
}

inline vector4f
operator/(const vector4f& left, const vector4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorDivide(v1, v2);

	vector4f result;
	base_vec4_t data;

	DirectX::XMStoreFloat4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / right.Get_Base());
#endif
}

inline vector4f
operator/(const vector4f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	auto temp = DirectX::XMVectorScale(v1, 1.f / right);

	vector4f result;
	base_vec4_t data;

	DirectX::XMStoreFloat4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / right);
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK