#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace math
{
	class vector2f
	{
	public:
		vector2f(float x, float y) : m_base(x, y) {}
		vector2f(const Kotek::ktk::math::base_vec2_t& data) : m_base(data) {}
		vector2f(const vector2f& data) : m_base(data.m_base) {}
		vector2f(void) : m_base{} {}

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
#endif
			return *this;
		}

		vector2f& operator+=(const base_vec2_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR v1 = *this;
			DirectX::XMVECTOR v2 = DirectX::XMLoadFloat2(&data);
			auto result = DirectX::XMVectorAdd(v1, v2);

			DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
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
#endif
			return *this;
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

#endif
			return *this;
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

#endif
			return *this;
		}

		vector2f& operator/=(const vector2f& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			auto result =
				DirectX::XMVectorDivide(casted_original, casted_argument);

			DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			return *this;
		}

		vector2f& operator/=(const base_vec2_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat2(&data);
			auto result =
				DirectX::XMVectorDivide(casted_original, casted_argument);

			DirectX::XMStoreFloat2(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

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
			this->m_base.x = std::fmod(this->m_base.x, data.Get_X());
			this->m_base.y = std::fmod(this->m_base.y, data.Get_Y());
			return *this;
		}

		vector2f operator+() const noexcept
		{
			return *this;
		}
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
#endif
		}

		bool operator!=(const vector2f& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;

			return DirectX::XMVector2NotEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
		}

		operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMLoadFloat2(&this->m_base);
		}

		float Get_X(void) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			return this->m_base.x;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

		float Get_Y(void) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			return this->m_base.y;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

		vector2f& Set_X(float value) noexcept
		{
			this->m_base.x = value;
			return *this;
		}

		vector2f& Set_Y(float value) noexcept
		{
			this->m_base.y = value;
			return *this;
		}

		vector2f& Set_Base(const base_vec2_t& data) noexcept
		{
			this->m_base = data;
			return *this;
		}

	private:
		base_vec2_t m_base;
	};

	inline vector2f operator+(
		const vector2f& left, const vector2f& right) noexcept
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
#endif
	}

	inline vector2f operator-(
		const vector2f& left, const vector2f& right) noexcept
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

#endif
	}

	inline vector2f operator*(
		const vector2f& left, const vector2f& right) noexcept
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

#endif
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

#endif
	}

	inline vector2f operator*(float left, const vector2f& right) noexcept
	{
		return operator*(right, left);
	}

	inline vector2f operator/(
		const vector2f& left, const vector2f& right) noexcept
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

#endif
	}

	inline vector2f operator/(const vector2f& left, float right) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return operator*(left, 1.f / right);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
	}
} // namespace math

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK