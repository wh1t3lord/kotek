#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector3f
{
public:
	vector3f(float x);
	vector3f(float x, float y);
	vector3f(float x, float y, float z);
	vector3f(float x, float y, float z, float w);

	vector3f(float* p_arr3, unsigned char size = 3);
	vector3f(const float* p_arr3, unsigned char size = 3);

	vector3f(const matrix4f_view_t& view);
	vector3f(const matrix3f_view_t& view);
	vector3f(const matrix2f_view_t& view);
	vector3f(const matrix1f_view_t& view);

	vector3f(const matrix2f_view_t& view, float z);

	vector3f(const matrix1f_view_t& view, float y, float z);

	vector3f(const matrix4f_const_view_t& view);
	vector3f(const matrix3f_const_view_t& view);
	vector3f(const matrix2f_const_view_t& view);
	vector3f(const matrix1f_const_view_t& view);

	vector3f(const matrix2f_const_view_t& view, float z);

	vector3f(const matrix1f_const_view_t& view, float y, float z);

	vector3f(const base_vec3_t& data);
	vector3f(const vector3f& data);

	vector3f(void);

	~vector3f(void) = default;

	vector3f& operator=(const vector3f& data) noexcept;

	vector3f& operator+=(const vector3f& data) noexcept;
	vector3f& operator+=(const matrix4f_view_t& data) noexcept;
	vector3f& operator+=(const matrix3f_view_t& data) noexcept;
	vector3f& operator+=(const matrix2f_view_t& data) noexcept;
	vector3f& operator+=(const matrix1f_view_t& data) noexcept;
	vector3f& operator+=(const matrix4f_const_view_t& data) noexcept;
	vector3f& operator+=(const matrix3f_const_view_t& data) noexcept;
	vector3f& operator+=(const matrix2f_const_view_t& data) noexcept;
	vector3f& operator+=(const matrix1f_const_view_t& data) noexcept;
	vector3f& operator+=(const base_vec3_t& data) noexcept;

	vector3f& operator-=(const vector3f& data) noexcept;
	vector3f& operator-=(const matrix4f_view_t& data) noexcept;
	vector3f& operator-=(const matrix3f_view_t& data) noexcept;
	vector3f& operator-=(const matrix2f_view_t& data) noexcept;
	vector3f& operator-=(const matrix1f_view_t& data) noexcept;
	vector3f& operator-=(const matrix4f_const_view_t& data) noexcept;
	vector3f& operator-=(const matrix3f_const_view_t& data) noexcept;
	vector3f& operator-=(const matrix2f_const_view_t& data) noexcept;
	vector3f& operator-=(const matrix1f_const_view_t& data) noexcept;
	vector3f& operator-=(const base_vec3_t& data) noexcept;

	vector3f& operator*=(const vector3f& data) noexcept;
	vector3f& operator*=(const matrix4f_view_t& data) noexcept;
	vector3f& operator*=(const matrix3f_view_t& data) noexcept;
	vector3f& operator*=(const matrix2f_view_t& data) noexcept;
	vector3f& operator*=(const matrix1f_view_t& data) noexcept;
	vector3f& operator*=(const matrix4f_const_view_t& data) noexcept;
	vector3f& operator*=(const matrix3f_const_view_t& data) noexcept;
	vector3f& operator*=(const matrix2f_const_view_t& data) noexcept;
	vector3f& operator*=(const matrix1f_const_view_t& data) noexcept;
	vector3f& operator*=(const base_vec3_t& data) noexcept;
	vector3f& operator*=(float value) noexcept;

	vector3f& operator/=(const vector3f& data) noexcept;
	vector3f& operator/=(const matrix4f_view_t& data) noexcept;
	vector3f& operator/=(const matrix3f_view_t& data) noexcept;
	vector3f& operator/=(const matrix2f_view_t& data) noexcept;
	vector3f& operator/=(const matrix1f_view_t& data) noexcept;
	vector3f& operator/=(const matrix4f_const_view_t& data) noexcept;
	vector3f& operator/=(const matrix3f_const_view_t& data) noexcept;
	vector3f& operator/=(const matrix2f_const_view_t& data) noexcept;
	vector3f& operator/=(const matrix1f_const_view_t& data) noexcept;
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

	float x(void) const noexcept;
	float y(void) const noexcept;
	float z(void) const noexcept;

	float& x(void) noexcept;
	float& y(void) noexcept;
	float& z(void) noexcept;

	const float* data(void) const noexcept;
	float* data(void) noexcept;

	inline static constexpr unsigned char size_of(void) noexcept
	{
		static_assert(sizeof(float[3]) == sizeof(m_base) &&
			"we gurantee that base type is float[3]");
		return static_cast<unsigned char>(sizeof(float[3]));
	}

	vector3f& Set_Base(const base_vec3_t& data) noexcept;

	base_vec3_t& Get_Base(void) noexcept;
	const base_vec3_t& Get_Base(void) const noexcept;

private:
	base_vec3_t m_base;
};

inline vector3f operator+(const vector3f& left, const vector3f& right) noexcept
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

inline vector3f operator-(const vector3f& left, const vector3f& right) noexcept
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

inline vector3f operator-(
	const vector3f& left, const matrix4f_view_t& view) noexcept
{
	return operator-(left, vector3f(view));
}

inline vector3f operator-(
	const vector3f& left, const matrix3f_view_t& view) noexcept
{
	return operator-(left, vector3f(view));
}

inline vector3f operator-(
	const vector3f& left, const matrix2f_view_t& view) noexcept
{
	return operator-(left, vector3f(view));
}

inline vector3f operator-(
	const vector3f& left, const matrix1f_view_t& view) noexcept
{
	return operator-(left, vector3f(view));
}

inline vector3f operator-(
	const matrix4f_view_t& view, const vector3f& right) noexcept
{
	return operator-(vector3f(view), right);
}

inline vector3f operator-(
	const matrix3f_view_t& view, const vector3f& right) noexcept
{
	return operator-(vector3f(view), right);
}

inline vector3f operator-(
	const matrix2f_view_t& view, const vector3f& right) noexcept
{
	return operator-(vector3f(view), right);
}

inline vector3f operator-(
	const matrix1f_view_t& view, const vector3f& right) noexcept
{
	return operator-(vector3f(view), right);
}

inline vector3f operator*(const vector3f& left, const vector3f& right) noexcept
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

inline vector3f operator*(
	const vector3f& left, const matrix4f_view_t& view) noexcept
{
	return operator*(left, vector3f(view));
}

inline vector3f operator*(
	const vector3f& left, const matrix3f_view_t& view) noexcept
{
	return operator*(left, vector3f(view));
}

inline vector3f operator*(
	const vector3f& left, const matrix2f_view_t& view) noexcept
{
	return operator*(left, vector3f(view).z() = 1.0f);
}

inline vector3f operator*(
	const vector3f& left, const matrix1f_view_t& view) noexcept
{
	vector3f casted(view);
	casted.y() = 1.0f;
	casted.z() = 1.0f;
	return operator*(left, casted);
}

inline vector3f operator*(
	const matrix4f_view_t& view, const vector3f& right) noexcept
{
	return operator*(vector3f(view), right);
}

inline vector3f operator*(
	const matrix3f_view_t& view, const vector3f& right) noexcept
{
	return operator*(vector3f(view), right);
}

inline vector3f operator*(
	const matrix2f_view_t& view, const vector3f& right) noexcept
{
	vector3f casted(view);
	casted.z() = 1.0f;
	return operator*(casted, right);
}

inline vector3f operator*(
	const matrix1f_view_t& view, const vector3f& right) noexcept
{
	vector3f casted(view);
	casted.y() = 1.0f;
	casted.z() = 1.0f;
	return operator*(casted, right);
}

inline vector3f operator*(const vector3f& left, float right) noexcept
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

inline vector3f operator*(float left, const vector3f& right) noexcept
{
	return operator*(right, left);
}

inline vector3f operator/(const vector3f& left, const vector3f& right) noexcept
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

inline vector3f operator/(
	const vector3f& left, const matrix4f_view_t& view) noexcept
{
	return operator/(left, vector3f(view));
}

inline vector3f operator/(
	const vector3f& left, const matrix3f_view_t& view) noexcept
{
	return operator/(left, vector3f(view));
}

inline vector3f operator/(
	const vector3f& left, const matrix2f_view_t& view) noexcept
{
	return operator/(left, vector3f(view).z() = 1.0f);
}

inline vector3f operator/(
	const vector3f& left, const matrix1f_view_t& view) noexcept
{
	vector3f casted(view);
	casted.y() = 1.0f;
	casted.z() = 1.0f;
	return operator/(left, casted);
}

inline vector3f operator/(
	const matrix4f_view_t& view, const vector3f& right) noexcept
{
	return operator/(vector3f(view), right);
}

inline vector3f operator/(
	const matrix3f_view_t& view, const vector3f& right) noexcept
{
	return operator/(vector3f(view), right);
}

inline vector3f operator/(
	const matrix2f_view_t& view, const vector3f& right) noexcept
{
	vector3f casted(view);
	casted.z() = 1.0f;
	return operator/(casted, right);
}

inline vector3f operator/(
	const matrix1f_view_t& view, const vector3f& right) noexcept
{
	vector3f casted(view);
	casted.y() = 1.0f;
	casted.z() = 1.0f;
	return operator/(casted, right);
}

inline vector3f operator/(
	const vector3f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator/(left, vector3f(view));
}

inline vector3f operator/(
	const vector3f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator/(left, vector3f(view));
}

inline vector3f operator/(
	const vector3f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator/(left, vector3f(view).z() = 1.0f);
}

inline vector3f operator/(
	const vector3f& left, const matrix1f_const_view_t& view) noexcept
{
	vector3f casted(view);
	casted.y() = 1.0f;
	casted.z() = 1.0f;
	return operator/(left, casted);
}

inline vector3f operator/(
	const matrix4f_const_view_t& view, const vector3f& right) noexcept
{
	return operator/(vector3f(view), right);
}

inline vector3f operator/(
	const matrix3f_const_view_t& view, const vector3f& right) noexcept
{
	return operator/(vector3f(view), right);
}

inline vector3f operator/(
	const matrix2f_const_view_t& view, const vector3f& right) noexcept
{
	vector3f casted(view);
	casted.z() = 1.0f;
	return operator/(casted, right);
}

inline vector3f operator/(
	const matrix1f_const_view_t& view, const vector3f& right) noexcept
{
	vector3f casted(view);
	casted.y() = 1.0f;
	casted.z() = 1.0f;
	return operator/(casted, right);
}

inline vector3f operator/(const vector3f& left, float right) noexcept
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
