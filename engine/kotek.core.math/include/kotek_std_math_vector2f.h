#pragma once

#include "kotek_std_alias_math.h"

#include "kotek_std_math_matrix1f_view.h"
#include "kotek_std_math_matrix2f_view.h"
#include "kotek_std_math_matrix3f_view.h"
#include "kotek_std_math_matrix4f_view.h"
#include "kotek_std_math_matrix1f_const_view.h"
#include "kotek_std_math_matrix2f_const_view.h"
#include "kotek_std_math_matrix3f_const_view.h"
#include "kotek_std_math_matrix4f_const_view.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector2f
{
public:
	vector2f(float x) : m_base(x, 0.0f) {}
	vector2f(float x, float y) : m_base(x, y) {}
	vector2f(float x, float y, float z) : m_base(x, y) {}
	vector2f(float x, float y, float z, float w) : m_base(x, y) {}

	vector2f(float* p_arr2, unsigned char size = 2) :
		m_base(p_arr2[0], p_arr2[1])
	{
		KOTEK_ASSERT(size > 0 && size <= 2,
			"something is wrong, size must be positive and less or equal to 2");

		if (size == 1)
		{
			m_base.y = 0.0f;
		}
	}

	vector2f(const float* p_arr2, unsigned char size = 2) :
		m_base(p_arr2[0], p_arr2[1])
	{
		KOTEK_ASSERT(size > 0 && size <= 2,
			"something is wrong, size must be positive and less or equal to 2");

		if (size == 1)
		{
			m_base.y = 0.0f;
		}
	}

	vector2f(const matrix4f_view_t& view) : m_base(view.x(), view.y()) {}
	vector2f(const matrix3f_view_t& view) : m_base(view.x(), view.y()) {}
	vector2f(const matrix2f_view_t& view) : m_base(view.x(), view.y()) {}
	vector2f(const matrix1f_view_t& view) : m_base(view.x(), 0.0f) {}

	vector2f(const matrix1f_view_t& view, float y) : m_base(view.x(), y) {}

	vector2f(const matrix4f_const_view_t& view) : m_base(view.x(), view.y()) {}
	vector2f(const matrix3f_const_view_t& view) : m_base(view.x(), view.y()) {}
	vector2f(const matrix2f_const_view_t& view) : m_base(view.x(), view.y()) {}
	vector2f(const matrix1f_const_view_t& view) : m_base(view.x(), 0.0f) {}

	vector2f(const matrix1f_const_view_t& view, float y) : m_base(view.x(), y) {}

	vector2f(const base_vec2_t& data) : m_base(data) {}
	vector2f(const vector2f& data) : m_base(data.m_base) {}
	vector2f(void) : m_base(0.0f,0.0f) {}

	~vector2f(void) = default;

	vector2f& operator=(const vector2f& data) noexcept
	{
		this->m_base = data.m_base;
		return *this;
	}

	vector2f& operator+=(const vector2f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = *this;
		DirectX::XMVECTOR v2 = data;
		auto result = DirectX::XMVectorAdd(v1, v2);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base += data.m_base;
#endif
		return *this;
	}

	vector2f& operator+=(const matrix4f_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator+=(const matrix3f_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator+=(const matrix2f_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator+=(const matrix1f_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), 0.0f));
	}

		vector2f& operator+=(const matrix4f_const_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator+=(const matrix3f_const_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator+=(const matrix2f_const_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator+=(const matrix1f_const_view_t& data) noexcept
	{
		return this->operator+=(base_vec2_t(data.x(), 0.0f));
	}

	vector2f& operator+=(const base_vec2_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = *this;
		DirectX::XMVECTOR v2 = DirectX::XMLoadFloat2(&data);
		auto result = DirectX::XMVectorAdd(v1, v2);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base += data;
#endif
		return *this;
	}

	vector2f& operator-=(const vector2f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;
		auto result =
			DirectX::XMVectorSubtract(casted_original, casted_argument);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base -= data.m_base;
#endif
		return *this;
	}

	vector2f& operator-=(const matrix4f_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator-=(const matrix3f_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator-=(const matrix2f_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator-=(const matrix1f_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), 0.0f));
	}

	vector2f& operator-=(const matrix4f_const_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator-=(const matrix3f_const_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator-=(const matrix2f_const_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator-=(const matrix1f_const_view_t& data) noexcept
	{
		return this->operator-=(base_vec2_t(data.x(), 0.0f));
	}

	vector2f& operator-=(const base_vec2_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat2(&data);
		auto result =
			DirectX::XMVectorSubtract(casted_original, casted_argument);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base -= data;
#endif
		return *this;
	}

	vector2f& operator*=(const vector2f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;
		auto result =
			DirectX::XMVectorMultiply(casted_original, casted_argument);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= data.m_base;
#endif
		return *this;
	}

	vector2f& operator*=(const matrix4f_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator*=(const matrix3f_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator*=(const matrix2f_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator*=(const matrix1f_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), 1.0f));
	}

	vector2f& operator*=(const matrix4f_const_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator*=(const matrix3f_const_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator*=(const matrix2f_const_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator*=(const matrix1f_const_view_t& data) noexcept
	{
		return this->operator*=(base_vec2_t(data.x(), 1.0f));
	}

	vector2f& operator*=(const base_vec2_t& data) noexcept
	{
		return this->operator*=(data);
	}

	vector2f& operator*=(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = *this;
		auto result = DirectX::XMVectorScale(v1, value);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= value;
#endif
		return *this;
	}

	vector2f& operator/=(const vector2f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;
		auto result = DirectX::XMVectorDivide(casted_original, casted_argument);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= data.m_base;
#endif
		return *this;
	}

	vector2f& operator/=(const matrix4f_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator/=(const matrix3f_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator/=(const matrix2f_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator/=(const matrix1f_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), 1.0f));
	}

	vector2f& operator/=(const matrix4f_const_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator/=(const matrix3f_const_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator/=(const matrix2f_const_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), data.y()));
	}

	vector2f& operator/=(const matrix1f_const_view_t& data) noexcept
	{
		return this->operator/=(base_vec2_t(data.x(), 1.0f));
	}

	vector2f& operator/=(const base_vec2_t& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat2(&data);
		auto result = DirectX::XMVectorDivide(casted_original, casted_argument);

		DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= data;
#endif
		return *this;
	}

	vector2f& operator/=(float value) noexcept
	{
		return this->operator*=(1.f / value);
	}

	vector2f& operator%=(float value) noexcept
	{
		this->m_base.x = std::fmod(this->m_base.x, value);
		this->m_base.y = std::fmod(this->m_base.y, value);
		return *this;
	}

	vector2f& operator%=(const vector2f& data) noexcept
	{
		this->m_base.x = std::fmod(this->m_base.x, data.x());
		this->m_base.y = std::fmod(this->m_base.y, data.y());
		return *this;
	}

	vector2f operator+() const noexcept { return *this; }
	vector2f operator-() const noexcept
	{
		return vector2f(-this->m_base.x, -this->m_base.y);
	}

	bool operator==(const vector2f& data) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;

		return DirectX::XMVector2Equal(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base == data.m_base;
#endif
	}

	bool operator!=(const vector2f& data) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR casted_original = *this;
		DirectX::XMVECTOR casted_argument = data;

		return DirectX::XMVector2NotEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base != data.m_base;
#endif
	}

	float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index != unsigned char(-1),
			"out of range (probably you passed a negative number)");
		KOTEK_ASSERT(index <= 1, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		float const* p_array = reinterpret_cast<float const*>(&this->m_base);

		return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	#error provide implementation
#endif
	}

	float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index != unsigned char(-1),
			"out of range (probably you passed a negative number)");
		KOTEK_ASSERT(index <= 1, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		float* p_array = reinterpret_cast<float*>(&this->m_base);
		return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	#error provide implementation
#endif
	}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMVECTOR() const noexcept
	{
		return DirectX::XMLoadFloat2(&this->m_base);
	}
#endif

	inline float x(void) const noexcept { return this->m_base.x; }
	inline float y(void) const noexcept { return this->m_base.y; }

	inline float& x(void) noexcept { return this->m_base.x; }
	inline float& y(void) noexcept { return this->m_base.y; }

	inline const float* data(void) const noexcept { return &this->m_base.x; }
	inline float* data(void) noexcept { return &this->m_base.x; }

	vector2f& Set_Base(const base_vec2_t& data) noexcept
	{
		this->m_base = data;
		return *this;
	}

	base_vec2_t& Get_Base(void) noexcept { return this->m_base; }

	const base_vec2_t& Get_Base(void) const noexcept { return this->m_base; }

private:
	base_vec2_t m_base;
};

inline vector2f operator+(const vector2f& left, const vector2f& right) noexcept
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

inline vector2f operator+(
	const vector2f& left, const matrix4f_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const vector2f& left, const matrix3f_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const vector2f& left, const matrix2f_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const vector2f& left, const matrix1f_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const matrix4f_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const matrix3f_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const matrix2f_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const matrix1f_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const vector2f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const vector2f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const vector2f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const vector2f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator+(left, vector2f(view));
}

inline vector2f operator+(
	const matrix4f_const_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const matrix3f_const_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const matrix2f_const_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator+(
	const matrix1f_const_view_t& view, const vector2f& right) noexcept
{
	return operator+(vector2f(view), right);
}

inline vector2f operator-(const vector2f& left, const vector2f& right) noexcept
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

inline vector2f operator-(
	const vector2f& left, const matrix4f_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const vector2f& left, const matrix3f_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const vector2f& left, const matrix2f_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const vector2f& left, const matrix1f_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const matrix4f_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const matrix3f_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const matrix2f_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const matrix1f_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const vector2f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const vector2f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const vector2f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const vector2f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator-(left, vector2f(view));
}

inline vector2f operator-(
	const matrix4f_const_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const matrix3f_const_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const matrix2f_const_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator-(
	const matrix1f_const_view_t& view, const vector2f& right) noexcept
{
	return operator-(vector2f(view), right);
}

inline vector2f operator*(const vector2f& left, const vector2f& right) noexcept
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

inline vector2f operator*(
	const vector2f& left, const matrix4f_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const vector2f& left, const matrix3f_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const vector2f& left, const matrix2f_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const vector2f& left, const matrix1f_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const matrix4f_view_t& view, const vector2f& right) noexcept
{
	return operator*(vector2f(view), right);
}

inline vector2f operator*(
	const matrix3f_view_t& view, const vector2f& right) noexcept
{
	return operator*(vector2f(view), right);
}

inline vector2f operator*(
	const matrix2f_view_t& view, const vector2f& right) noexcept
{
	return operator*(vector2f(view), right);
}

inline vector2f operator*(
	const matrix1f_view_t& view, const vector2f& right) noexcept
{
	vector2f casted(view);
	casted.y() = 1.0f;
	return operator*(casted, right);
}


inline vector2f operator*(
	const vector2f& left, const matrix4f_const_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const vector2f& left, const matrix3f_const_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const vector2f& left, const matrix2f_const_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const vector2f& left, const matrix1f_const_view_t& view) noexcept
{
	return operator*(left, vector2f(view));
}

inline vector2f operator*(
	const matrix4f_const_view_t& view, const vector2f& right) noexcept
{
	return operator*(vector2f(view), right);
}

inline vector2f operator*(
	const matrix3f_const_view_t& view, const vector2f& right) noexcept
{
	return operator*(vector2f(view), right);
}

inline vector2f operator*(
	const matrix2f_const_view_t& view, const vector2f& right) noexcept
{
	return operator*(vector2f(view), right);
}

inline vector2f operator*(
	const matrix1f_const_view_t& view, const vector2f& right) noexcept
{
	vector2f casted(view);
	casted.y() = 1.0f;
	return operator*(casted, right);
}

inline vector2f operator*(const vector2f& left, float right) noexcept
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

inline vector2f operator*(float left, const vector2f& right) noexcept
{
	return operator*(right, left);
}

inline vector2f operator/(const vector2f& left, const vector2f& right) noexcept
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

inline vector2f operator/(const vector2f& left, float right) noexcept
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
