#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector4f
{
public:
	vector4f(float x);
	vector4f(float x, float y);
	vector4f(float x, float y, float z);
	vector4f(float x, float y, float z, float w);

	vector4f(float* p_arr4, unsigned char size = 4);
	vector4f(const float* p_arr4, unsigned char size = 4);

	vector4f(const matrix4f_view_t& view);
	vector4f(const matrix3f_view_t& view);
	vector4f(const matrix2f_view_t& view);
	vector4f(const matrix1f_view_t& view);
	vector4f(const matrix3f_view_t& view, float w);
	vector4f(const matrix2f_view_t& view, float z, float w);
	vector4f(const matrix1f_view_t& view, float y, float z, float w);
	vector4f(const matrix1f_view_t& view, float y, float z);
	vector4f(const matrix1f_view_t& view, float y);
	vector4f(const matrix2f_view_t& view, float z);

	vector4f(const matrix1f_const_view_t& view);
	vector4f(const matrix1f_const_view_t& view, float y);
	vector4f(const matrix1f_const_view_t& view, float y, float z);
	vector4f(const matrix1f_const_view_t& view, float y, float z, float w);

	vector4f(const matrix2f_const_view_t& view);
	vector4f(const matrix2f_const_view_t& view, float z);
	vector4f(const matrix2f_const_view_t& view, float z, float w);

	vector4f(const matrix3f_const_view_t& view);
	vector4f(const matrix3f_const_view_t& view, float w);

	vector4f(const matrix4f_const_view_t& view);

	vector4f(const vector1f& data);
	vector4f(const vector1f& data, float y);
	vector4f(const vector1f& data, float y, float z);
	vector4f(const vector1f& data, float y, float z, float w);
	
	vector4f(const vector2f& data);
	vector4f(const vector2f& data, float z);
	vector4f(const vector2f& data, float z, float w);

	vector4f(const vector3f& data);
	vector4f(const vector3f& data, float w);

	vector4f(const base_vec4_t& data);
	vector4f(const vector4f& data);
	vector4f(void);

	~vector4f(void) = default;

	vector4f& operator=(const vector4f& data) noexcept;

	vector4f& operator=(const matrix4f_view_t& data) noexcept;
	vector4f& operator=(const matrix3f_view_t& data) noexcept;
	vector4f& operator=(const matrix2f_view_t& data) noexcept;
	vector4f& operator=(const matrix1f_view_t& data) noexcept;

	vector4f& operator+=(const vector4f& data) noexcept;
	vector4f& operator+=(const matrix4f_view_t& data) noexcept;
	vector4f& operator+=(const matrix3f_view_t& data) noexcept;
	vector4f& operator+=(const matrix2f_view_t& data) noexcept;
	vector4f& operator+=(const matrix1f_view_t& data) noexcept;

	vector4f& operator+=(const matrix4f_const_view_t& data) noexcept;
	vector4f& operator+=(const matrix3f_const_view_t& data) noexcept;
	vector4f& operator+=(const matrix2f_const_view_t& data) noexcept;
	vector4f& operator+=(const matrix1f_const_view_t& data) noexcept;

	vector4f& operator+=(const base_vec4_t& data) noexcept;

	vector4f& operator-=(const vector4f& data) noexcept;

	vector4f& operator-=(const matrix4f_view_t& data) noexcept;
	vector4f& operator-=(const matrix3f_view_t& data) noexcept;
	vector4f& operator-=(const matrix2f_view_t& data) noexcept;
	vector4f& operator-=(const matrix1f_view_t& data) noexcept;

	vector4f& operator-=(const matrix4f_const_view_t& data) noexcept;
	vector4f& operator-=(const matrix3f_const_view_t& data) noexcept;
	vector4f& operator-=(const matrix2f_const_view_t& data) noexcept;
	vector4f& operator-=(const matrix1f_const_view_t& data) noexcept;

	vector4f& operator-=(const base_vec4_t& data) noexcept;

	vector4f& operator*=(const vector4f& data) noexcept;

	vector4f& operator*=(const matrix4f_view_t& data) noexcept;
	vector4f& operator*=(const matrix3f_view_t& data) noexcept;
	vector4f& operator*=(const matrix2f_view_t& data) noexcept;
	vector4f& operator*=(const matrix1f_view_t& data) noexcept;

	vector4f& operator*=(const matrix4f_const_view_t& data) noexcept;
	vector4f& operator*=(const matrix3f_const_view_t& data) noexcept;
	vector4f& operator*=(const matrix2f_const_view_t& data) noexcept;
	vector4f& operator*=(const matrix1f_const_view_t& data) noexcept;

	vector4f& operator*=(const base_vec4_t& data) noexcept;

	vector4f& operator*=(float value) noexcept;

	vector4f& operator/=(const vector4f& data) noexcept;

	vector4f& operator/=(const matrix4f_view_t& data) noexcept;
	vector4f& operator/=(const matrix3f_view_t& data) noexcept;
	vector4f& operator/=(const matrix2f_view_t& data) noexcept;
	vector4f& operator/=(const matrix1f_view_t& data) noexcept;

	vector4f& operator/=(const matrix4f_const_view_t& data) noexcept;
	vector4f& operator/=(const matrix3f_const_view_t& data) noexcept;
	vector4f& operator/=(const matrix2f_const_view_t& data) noexcept;
	vector4f& operator/=(const matrix1f_const_view_t& data) noexcept;

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

	float x(void) const noexcept;
	float y(void) const noexcept;
	float z(void) const noexcept;
	float w(void) const noexcept;

	float& x(void) noexcept;
	float& y(void) noexcept;
	float& z(void) noexcept;
	float& w(void) noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	inline static constexpr unsigned char size_of(void) noexcept
	{
		static_assert(sizeof(float[4]) == sizeof(m_base) &&
			"we gurantee that base is equal to float[4] by size");
		return static_cast<unsigned char>(sizeof(float[4]));
	}

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

inline vector4f operator+(const vector4f& left, const vector4f& right) noexcept
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

inline vector4f operator+(const vector4f& left, const matrix4f_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const vector4f& left, const matrix3f_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const vector4f& left, const matrix2f_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const vector4f& left, const matrix1f_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const matrix4f_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const matrix3f_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const matrix2f_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const matrix1f_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const vector4f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const vector4f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const vector4f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const vector4f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator+(left, vector4f(view));
}

inline vector4f operator+(
	const matrix4f_const_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const matrix3f_const_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const matrix2f_const_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator+(
	const matrix1f_const_view_t& view, const vector4f& right) noexcept
{
	return operator+(vector4f(view), right);
}

inline vector4f operator-(const vector4f& left, const vector4f& right) noexcept
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

inline vector4f operator-(
	const vector4f& left, const matrix4f_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const vector4f& left, const matrix3f_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const vector4f& left, const matrix2f_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const vector4f& left, const matrix1f_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const matrix4f_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const matrix3f_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const matrix2f_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const matrix1f_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const vector4f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const vector4f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const vector4f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const vector4f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator-(left, vector4f(view));
}

inline vector4f operator-(
	const matrix4f_const_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const matrix3f_const_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const matrix2f_const_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator-(
	const matrix1f_const_view_t& view, const vector4f& right) noexcept
{
	return operator-(vector4f(view), right);
}

inline vector4f operator*(const vector4f& left, const vector4f& right) noexcept
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

inline vector4f operator*(
	const vector4f& left, const matrix4f_view_t& view) noexcept
{
	return operator*(left, vector4f(view));
}

inline vector4f operator*(
	const vector4f& left, const matrix3f_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	return operator*(left, casted);
}

inline vector4f operator*(
	const vector4f& left, const matrix2f_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator*(left, casted);
}

inline vector4f operator*(
	const vector4f& left, const matrix1f_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;
	return operator*(left, casted);
}

inline vector4f operator*(
	const matrix4f_view_t& view, const vector4f& right) noexcept
{
	return operator*(vector4f(view), right);
}

inline vector4f operator*(
	const matrix3f_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;

	return operator*(casted, right);
}

inline vector4f operator*(
	const matrix2f_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator*(casted, right);
}

inline vector4f operator*(
	const matrix1f_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;
	return operator*(casted, right);
}

inline vector4f operator*(
	const vector4f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator*(left, vector4f(view));
}

inline vector4f operator*(
	const vector4f& left, const matrix3f_const_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	return operator*(left, casted);
}

inline vector4f operator*(
	const vector4f& left, const matrix2f_const_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator*(left, casted);
}

inline vector4f operator*(
	const vector4f& left, const matrix1f_const_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;
	return operator*(left, casted);
}

inline vector4f operator*(
	const matrix4f_const_view_t& view, const vector4f& right) noexcept
{
	return operator*(vector4f(view), right);
}

inline vector4f operator*(
	const matrix3f_const_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;

	return operator*(casted, right);
}

inline vector4f operator*(
	const matrix2f_const_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator*(casted, right);
}

inline vector4f operator*(
	const matrix1f_const_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;
	return operator*(casted, right);
}

inline vector4f operator*(const vector4f& left, float right) noexcept
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

inline vector4f operator*(float left, const vector4f& right) noexcept
{
	return operator*(right, left);
}

inline vector4f operator/(const vector4f& left, const vector4f& right) noexcept
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

inline vector4f operator/(
	const vector4f& left, const matrix4f_view_t& view) noexcept
{
	return operator/(left, vector4f(view));
}

inline vector4f operator/(
	const vector4f& left, const matrix3f_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	return operator/(left,casted);
}

inline vector4f operator/(
	const vector4f& left, const matrix2f_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator/(left, casted);
}

inline vector4f operator/(
	const vector4f& left, const matrix1f_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;
	return operator/(left, casted);
}

inline vector4f operator/(
	const matrix4f_view_t& view, const vector4f& right) noexcept
{
	return operator/(vector4f(view), right);
}

inline vector4f operator/(
	const matrix3f_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	return operator/(casted, right);
}

inline vector4f operator/(
	const matrix2f_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator/(casted, right);
}

inline vector4f operator/(
	const matrix1f_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;

	return operator/(casted, right);
}

inline vector4f operator/(
	const vector4f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator/(left, vector4f(view));
}

inline vector4f operator/(
	const vector4f& left, const matrix3f_const_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	return operator/(left, casted);
}

inline vector4f operator/(
	const vector4f& left, const matrix2f_const_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator/(left, casted);
}

inline vector4f operator/(
	const vector4f& left, const matrix1f_const_view_t& view) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;
	return operator/(left, casted);
}

inline vector4f operator/(
	const matrix4f_const_view_t& view, const vector4f& right) noexcept
{
	return operator/(vector4f(view), right);
}

inline vector4f operator/(
	const matrix3f_const_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	return operator/(casted, right);
}

inline vector4f operator/(
	const matrix2f_const_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	return operator/(casted, right);
}

inline vector4f operator/(
	const matrix1f_const_view_t& view, const vector4f& right) noexcept
{
	vector4f casted(view);
	casted.w() = 1.0f;
	casted.z() = 1.0f;
	casted.y() = 1.0f;

	return operator/(casted, right);
}

inline vector4f operator/(const vector4f& left, float right) noexcept
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