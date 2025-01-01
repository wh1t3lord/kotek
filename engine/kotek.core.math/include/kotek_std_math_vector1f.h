#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector1f
{
public:
	vector1f(void);
	vector1f(float x);

	vector1f(float x, float y);
	vector1f(float x, float y, float z);
	vector1f(float x, float y, float z, float w);

	vector1f(float* p_arr1, unsigned char size = 1);
	vector1f(const float* p_arr1, unsigned char size = 1);

	vector1f(const matrix4f_view_t& view);
	vector1f(const matrix3f_view_t& view);
	vector1f(const matrix2f_view_t& view);
	vector1f(const matrix1f_view_t& view);

	vector1f(const matrix4f_const_view_t& view);
	vector1f(const matrix3f_const_view_t& view);
	vector1f(const matrix2f_const_view_t& view);
	vector1f(const matrix1f_const_view_t& view);

	vector1f(const vector2f& data);
	vector1f(const vector3f& data);
	vector1f(const vector4f& data);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vector1f(const base_vec1_t& data);
#endif
	vector1f(const vector1f& data);

	~vector1f() = default;

	vector1f& operator=(const vector1f& data);
	vector1f& operator+=(float value);
	vector1f& operator+=(const vector1f& data);
	vector1f& operator+=(const matrix4f_view_t& view);
	vector1f& operator+=(const matrix3f_view_t& view);
	vector1f& operator+=(const matrix2f_view_t& view);
	vector1f& operator+=(const matrix1f_view_t& view);
	vector1f& operator+=(const matrix4f_const_view_t& view);
	vector1f& operator+=(const matrix3f_const_view_t& view);
	vector1f& operator+=(const matrix2f_const_view_t& view);
	vector1f& operator+=(const matrix1f_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vector1f& operator+=(const base_vec1_t& data);
#endif

	vector1f& operator-=(float value);

	vector1f& operator-=(const vector1f& data);
	vector1f& operator-=(const matrix4f_view_t& view);
	vector1f& operator-=(const matrix3f_view_t& view);
	vector1f& operator-=(const matrix2f_view_t& view);
	vector1f& operator-=(const matrix1f_view_t& view);
	vector1f& operator-=(const matrix4f_const_view_t& view);
	vector1f& operator-=(const matrix3f_const_view_t& view);
	vector1f& operator-=(const matrix2f_const_view_t& view);
	vector1f& operator-=(const matrix1f_const_view_t& view);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vector1f& operator-=(const base_vec1_t& data);
#endif

	vector1f& operator*=(float value);
	vector1f& operator*=(const matrix4f_view_t& view);
	vector1f& operator*=(const matrix3f_view_t& view);
	vector1f& operator*=(const matrix2f_view_t& view);
	vector1f& operator*=(const matrix1f_view_t& view);
	vector1f& operator*=(const matrix4f_const_view_t& view);
	vector1f& operator*=(const matrix3f_const_view_t& view);
	vector1f& operator*=(const matrix2f_const_view_t& view);
	vector1f& operator*=(const matrix1f_const_view_t& view);
	vector1f& operator*=(const vector1f& data);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vector1f& operator*=(const base_vec1_t& data);
#endif

	vector1f& operator/=(float value);
	vector1f& operator/=(const matrix4f_view_t& view);
	vector1f& operator/=(const matrix3f_view_t& view);
	vector1f& operator/=(const matrix2f_view_t& view);
	vector1f& operator/=(const matrix1f_view_t& view);
	vector1f& operator/=(const matrix4f_const_view_t& view);
	vector1f& operator/=(const matrix3f_const_view_t& view);
	vector1f& operator/=(const matrix2f_const_view_t& view);
	vector1f& operator/=(const matrix1f_const_view_t& view);
	vector1f& operator/=(const vector1f& data);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vector1f& operator/=(const base_vec1_t& data);
#endif

	vector1f& operator%=(float value) noexcept;

	vector1f& operator%=(const vector1f& data) noexcept;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vector1f& operator%=(const base_vec1_t& data) noexcept;
#endif

	vector1f operator+() const noexcept;

	vector1f operator-() const noexcept;

	bool operator==(const vector1f& data) const noexcept;

	bool operator!=(const vector1f& data) const noexcept;

	float operator[](unsigned int index) const;

	float& operator[](unsigned int index);

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMVECTOR() const noexcept;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

	float x(void) const noexcept;

	float& x(void) noexcept;

	const float* data(void) const noexcept;

	float* data(void) noexcept;

	inline static constexpr unsigned char size_of(void) noexcept
	{
		static_assert(sizeof(float[1]) == sizeof(m_base) &&
			"we gurantee that base type is float[1] by size");
		return static_cast<unsigned char>(sizeof(float[1]));
	}

	vector1f& Set_Base(const base_vec1_t& data) noexcept;

	base_vec1_t& Get_Base(void) noexcept;
	const base_vec1_t& Get_Base(void) const noexcept;

private:
	base_vec1_t m_base;
};

inline vector1f operator+(const vector1f& a, const vector1f& b) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = a;
	DirectX::XMVECTOR v2 = b;
	auto temp = DirectX::XMVectorAdd(v1, v2);

	vector1f result;
	float value;
	DirectX::XMStoreFloat(&value, temp);

	result.x() = value;

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (a.Get_Base() + b.Get_Base());
#endif
}

inline vector1f operator+(
	const vector1f& left, const matrix4f_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const vector1f& left, const matrix3f_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const vector1f& left, const matrix2f_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const vector1f& left, const matrix1f_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const matrix4f_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const matrix3f_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const matrix2f_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const matrix1f_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const vector1f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const vector1f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const vector1f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const vector1f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator+(left, vector1f(view));
}

inline vector1f operator+(
	const matrix4f_const_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const matrix3f_const_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const matrix2f_const_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator+(
	const matrix1f_const_view_t& view, const vector1f& right) noexcept
{
	return operator+(vector1f(view), right);
}

inline vector1f operator-(const vector1f& a, const vector1f& b) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = a;
	DirectX::XMVECTOR v2 = b;
	auto temp = DirectX::XMVectorSubtract(v1, v2);

	vector1f result;
	float value;
	DirectX::XMStoreFloat(&value, temp);

	result.x() = value;

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (a.Get_Base() - b.Get_Base());
#endif
}

inline vector1f operator-(
	const vector1f& left, const matrix4f_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const vector1f& left, const matrix3f_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const vector1f& left, const matrix2f_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const vector1f& left, const matrix1f_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const matrix4f_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const matrix3f_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const matrix2f_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const matrix1f_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const vector1f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const vector1f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const vector1f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const vector1f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator-(left, vector1f(view));
}

inline vector1f operator-(
	const matrix4f_const_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const matrix3f_const_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const matrix2f_const_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator-(
	const matrix1f_const_view_t& view, const vector1f& right) noexcept
{
	return operator-(vector1f(view), right);
}

inline vector1f operator*(const vector1f& a, const vector1f& b) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = a;
	DirectX::XMVECTOR v2 = b;
	auto temp = DirectX::XMVectorMultiply(v1, v2);

	vector1f result;
	float value;

	DirectX::XMStoreFloat(&value, temp);

	result.x() = value;

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (a.Get_Base() * b.Get_Base());
#endif
}

inline vector1f operator*(
	const vector1f& left, const matrix4f_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const vector1f& left, const matrix3f_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const vector1f& left, const matrix2f_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const vector1f& left, const matrix1f_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const matrix4f_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const matrix3f_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const matrix2f_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const matrix1f_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const vector1f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const vector1f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const vector1f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const vector1f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator*(left, vector1f(view));
}

inline vector1f operator*(
	const matrix4f_const_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const matrix3f_const_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const matrix2f_const_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(
	const matrix1f_const_view_t& view, const vector1f& right) noexcept
{
	return operator*(vector1f(view), right);
}

inline vector1f operator*(const vector1f& a, float b) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = a;
	auto temp = DirectX::XMVectorScale(v1, b);

	vector1f result;
	float value;

	DirectX::XMStoreFloat(&value, temp);

	result.x() = value;

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (a.Get_Base() * b);
#endif
}

inline vector1f operator*(float a, const vector1f& b) noexcept
{
	return operator*(b, a);
}

inline vector1f operator/(const vector1f& a, const vector1f& b) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = a;
	DirectX::XMVECTOR v2 = b;
	auto temp = DirectX::XMVectorDivide(v1, v2);

	vector1f result;
	float value;

	DirectX::XMStoreFloat(&value, temp);

	result.x() = value;

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (a.Get_Base() / b.Get_Base());
#endif
}

inline vector1f operator/(
	const vector1f& left, const matrix4f_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const vector1f& left, const matrix3f_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const vector1f& left, const matrix2f_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const vector1f& left, const matrix1f_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const matrix4f_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const matrix3f_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const matrix2f_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const matrix1f_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const vector1f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const vector1f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const vector1f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const vector1f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator/(left, vector1f(view));
}

inline vector1f operator/(
	const matrix4f_const_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const matrix3f_const_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const matrix2f_const_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(
	const matrix1f_const_view_t& view, const vector1f& right) noexcept
{
	return operator/(vector1f(view), right);
}

inline vector1f operator/(const vector1f& a, float b) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = a;
	auto temp = DirectX::XMVectorScale(v1, 1.f / b);

	vector1f result;
	float value;

	DirectX::XMStoreFloat(&value, temp);

	result.x() = value;

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (a.Get_Base() / b);
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
