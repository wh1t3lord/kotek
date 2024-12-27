#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector3f
{
public:
	vector3f(float x) : m_base(x, 0.0f, 0.0f) {}
	vector3f(float x, float y) : m_base(x, y, 0.0f) {}
	vector3f(float x, float y, float z) : m_base(x, y, z) {}
	vector3f(float x, float y, float z, float w) : m_base(x, y, z) {}

	vector3f(float* p_arr3) : m_base(p_arr3[0], p_arr3[1], p_arr3[2]) {}
	vector3f(const float* p_arr3) : m_base(p_arr3[0], p_arr3[1], p_arr3[2]) {}

	vector3f(const matrix4_view_t& view) : m_base(view.x(), view.y(), view.z())
	{
	}
	vector3f(const matrix3_view_t& view) : m_base(view.x(), view.y(), view.z())
	{
	}
	vector3f(const matrix2_view_t& view) : m_base(view.x(), view.y(), 0.0f) {}
	vector3f(const matrix1_view_t& view) : m_base(view.x(), 0.0f, 0.0f) {}

	vector3f(const matrix2_view_t& view, float z) :
		m_base(view.x(), view.y(), z)
	{
	}

	vector3f(const matrix1_view_t& view, float y, float z) :
		m_base(view.x(), y, z)
	{
	}

	vector3f(const base_vec3_t& data) : m_base(data) {}
	vector3f(const vector3f& data) : m_base(data.m_base) {}

	vector3f(void) : m_base{} {}

	~vector3f(void) = default;

	vector3f& operator=(const vector3f& data) noexcept
	{
		this->m_base = data.m_base;
		return *this;
	}

	vector3f& operator+=(const vector3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = *this;
		DirectX::XMVECTOR v2 = data;
		auto result = DirectX::XMVectorAdd(v1, v2);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base += data.m_base;
#endif
		return *this;
	}

	vector3f& operator+=(const matrix4_view_t& data) noexcept
	{
		return this->operator+=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator+=(const matrix3_view_t& data) noexcept
	{
		return this->operator+=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator+=(const matrix2_view_t& data) noexcept
	{
		return this->operator+=(base_vec3_t(data.x(), data.y(), 0.0f));
	}

	vector3f& operator+=(const matrix1_view_t& data) noexcept
	{
		return this->operator+=(base_vec3_t(data.x(), 0.0f, 0.0f));
	}

	vector3f& operator+=(const base_vec3_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = *this;
		DirectX::XMVECTOR v2 = DirectX::XMLoadFloat3(&data);
		auto result = DirectX::XMVectorAdd(v1, v2);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base += data;
#endif
		return *this;
	}

	vector3f& operator-=(const vector3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;
		auto result =
			DirectX::XMVectorSubtract(casted_original, casted_argument);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base -= data.m_base;
#endif
		return *this;
	}

	vector3f& operator-=(const matrix4_view_t& data) noexcept
	{
		return this->operator-=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator-=(const matrix3_view_t& data) noexcept
	{
		return this->operator-=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator-=(const matrix2_view_t& data) noexcept
	{
		return this->operator-=(base_vec3_t(data.x(), data.y(), 0.0f));
	}

	vector3f& operator-=(const matrix1_view_t& data) noexcept
	{
		return this->operator-=(base_vec3_t(data.x(), 0.0f, 0.0f));
	}

	vector3f& operator-=(const base_vec3_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat3(&data);
		auto result =
			DirectX::XMVectorSubtract(casted_original, casted_argument);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base -= data;
#endif
		return *this;
	}

	vector3f& operator*=(const vector3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;
		auto result =
			DirectX::XMVectorMultiply(casted_original, casted_argument);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= data.m_base;
#endif
		return *this;
	}

	vector3f& operator*=(const matrix4_view_t& data) noexcept
	{
		return this->operator*=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator*=(const matrix3_view_t& data) noexcept
	{
		return this->operator*=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator*=(const matrix2_view_t& data) noexcept
	{
		return this->operator*=(base_vec3_t(data.x(), data.y(), 1.0f));
	}

	vector3f& operator*=(const matrix1_view_t& data) noexcept
	{
		return this->operator*=(base_vec3_t(data.x(), 1.0f, 1.0f));
	}

	vector3f& operator*=(const base_vec3_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat3(&data);
		auto result =
			DirectX::XMVectorMultiply(casted_original, casted_argument);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= data;
#endif
		return *this;
	}

	vector3f& operator*=(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = *this;
		auto result = DirectX::XMVectorScale(v1, value);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= value;
#endif
		return *this;
	}

	vector3f& operator/=(const vector3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;
		auto result = DirectX::XMVectorDivide(casted_original, casted_argument);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= data.m_base;
#endif
		return *this;
	}

	vector3f& operator/=(const matrix4_view_t& data) noexcept
	{
		return this->operator/=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator/=(const matrix3_view_t& data) noexcept
	{
		return this->operator/=(base_vec3_t(data.x(), data.y(), data.z()));
	}

	vector3f& operator/=(const matrix2_view_t& data) noexcept
	{
		return this->operator/=(base_vec3_t(data.x(), data.y(), 1.0f));
	}

	vector3f& operator/=(const matrix1_view_t& data) noexcept
	{
		return this->operator/=(base_vec3_t(data.x(), 1.0f, 1.0f));
	}

	vector3f& operator/=(const base_vec3_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat3(&data);
		auto result = DirectX::XMVectorDivide(casted_original, casted_argument);

		DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= data;
#endif
		return *this;
	}

	vector3f& operator/=(float value) noexcept
	{
		return this->operator*=(1.f / value);
	}

	vector3f& operator%=(float value) noexcept
	{
		this->m_base.x = std::fmod(this->m_base.x, value);
		this->m_base.y = std::fmod(this->m_base.y, value);
		this->m_base.z = std::fmod(this->m_base.z, value);

		return *this;
	}

	vector3f& operator%=(const vector3f& data) noexcept
	{
		this->m_base.x = std::fmod(this->m_base.x, data.x());
		this->m_base.y = std::fmod(this->m_base.y, data.y());
		this->m_base.z = std::fmod(this->m_base.z, data.z());

		return *this;
	}

	vector3f operator+() const noexcept { return *this; }
	vector3f operator-() const noexcept
	{
		return vector3f(-this->m_base.x, -this->m_base.y, -this->m_base.z);
	}

	bool operator==(const vector3f& data) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;

		return DirectX::XMVector3Equal(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base == data.m_base;
#endif
	}

	bool operator!=(const vector3f& data) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;

		return DirectX::XMVector3NotEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base != data.m_base;
#endif
	}

	float operator[](unsigned int index) const
	{
		KOTEK_ASSERT(index != unsigned int(-1),
			"out of range (probably you passed a negative number)");
		KOTEK_ASSERT(index <= 2, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		float const* p_array = reinterpret_cast<float const*>(&this->m_base);

		return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
	}

	float& operator[](unsigned int index)
	{
		KOTEK_ASSERT(index != unsigned int(-1),
			"out of range (probably you passed a negative number)");
		KOTEK_ASSERT(index <= 2, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		float* p_array = reinterpret_cast<float*>(&this->m_base);
		return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
	}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMVECTOR() const noexcept
	{
		return DirectX::XMLoadFloat3(&this->m_base);
	}
#endif

	float x(void) const noexcept { return this->m_base.x; }
	float y(void) const noexcept { return this->m_base.y; }
	float z(void) const noexcept { return this->m_base.z; }

	float& x(void) noexcept { return this->m_base.x; }
	float& y(void) noexcept { return this->m_base.y; }
	float& z(void) noexcept { return this->m_base.z; }

	vector3f& Set_Base(const base_vec3_t& data) noexcept
	{
		this->m_base = data;
		return *this;
	}

	base_vec3_t& Get_Base(void) noexcept { return this->m_base; }

	const base_vec3_t& Get_Base(void) const noexcept { return this->m_base; }

private:
	base_vec3_t m_base;
};

inline vector3f operator+(const vector3f& left, const vector3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorAdd(v1, v2);

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
	auto temp = DirectX::XMVectorSubtract(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() - right.Get_Base();
#endif
}

inline vector3f operator*(const vector3f& left, const vector3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	DirectX::XMVECTOR v2 = right;
	auto temp = DirectX::XMVectorMultiply(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() * right.Get_Base();
#endif
}

inline vector3f operator*(const vector3f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	auto temp = DirectX::XMVectorScale(v1, right);

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
	auto temp = DirectX::XMVectorDivide(v1, v2);

	vector3f result;
	base_vec3_t data;

	DirectX::XMStoreFloat3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return left.Get_Base() / right.Get_Base();
#endif
}

inline vector3f operator/(const vector3f& left, float right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR v1 = left;
	auto temp = DirectX::XMVectorScale(v1, 1.f / right);

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
