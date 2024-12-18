#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

	class vector1f
	{
	public:
        vector1f(float x) : m_base{x} {}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		vector1f(const base_vec1_t& data) : m_base(data) {}
#endif
		vector1f(const vector1f& data) : m_base(data.m_base) {}
		vector1f(void) : m_base{} {}

		~vector1f() = default;

		vector1f& operator=(const vector1f& data)
		{
			this->m_base = data.m_base;
			return *this;
		}

		vector1f& operator+=(float value)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto v1 = DirectX::XMLoadFloat(&this->m_base);
			auto v2 = DirectX::XMLoadFloat(&value);
			auto result = DirectX::XMVectorAdd(v1, v2);

			DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base += value;
#endif
			return *this;
		}

		vector1f& operator+=(const vector1f& data)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			this->operator+=(data.m_base);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base += data.m_base;
#endif
			return *this;
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		vector1f& operator+=(const base_vec1_t& data)
		{
			this->m_base += data;
			return *this;
		}
#endif

		vector1f& operator-=(float value)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto casted_argument = DirectX::XMLoadFloat(&value);
			auto result =
				DirectX::XMVectorSubtract(casted_original, casted_argument);

			DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base -= value;
#endif
			return *this;
		}

		vector1f& operator-=(const vector1f& data)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			this->operator-=(data.m_base);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base -= data.m_base;
#endif
			return *this;
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		vector1f& operator-=(const base_vec1_t& data)
		{
            this->m_base -= data;
			return *this;
		}
#endif

		vector1f& operator*=(float value)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto result = DirectX::XMVectorScale(casted_original, value);

			DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base *= value;
#endif
			return *this;
		}

		vector1f& operator*=(const vector1f& data)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto casted_argument = DirectX::XMLoadFloat(&data.m_base);
			auto result =
				DirectX::XMVectorMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base *= data.m_base;
#endif
			return *this;
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		vector1f& operator*=(const base_vec1_t& data)
		{
            this->m_base *= data;
			return *this;
		}
#endif

		vector1f& operator/=(float value)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			KOTEK_ASSERT(value != 0.0f, "you can't divide if you have zero!!!");

			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto result = DirectX::XMVectorScale(casted_original, 1.f / value);
			DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base /= value;
#endif
			return *this;
		}

		vector1f& operator/=(const vector1f& data)
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto casted_argument = DirectX::XMLoadFloat(&data.m_base);
			auto result =
				DirectX::XMVectorDivide(casted_original, casted_argument);

			DirectX::XMStoreFloat(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
			this->m_base /= data.m_base;
#endif
			return *this;
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		vector1f& operator/=(const base_vec1_t& data)
		{
            this->m_base /= data;
			return *this;
		}
#endif

		vector1f& operator%=(float value) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
            this->m_base = std::fmod(this->m_base, value);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base.x = std::fmod(this->m_base.x, value);
#endif

			return *this;
		}

		vector1f& operator%=(const vector1f& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
            this->m_base = std::fmod(this->m_base, data.m_base);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base.x = std::fmod(this->m_base.x, data.m_base.x);
#endif
			return *this;
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
        vector1f& operator%=(const base_vec1_t& data) noexcept
        {
            this->m_base.x = std::fmod(this->m_base.x, data.x);
            return *this;
        }
#endif

		vector1f operator+() const noexcept
		{
			return *this;
		}

		vector1f operator-() const noexcept
		{
			return vector1f(-this->m_base);
		}

		bool operator==(const vector1f& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

			return DirectX::XMVector2Equal(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            return this->m_base == data.m_base;
#endif
		}

		bool operator!=(const vector1f& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			auto casted_original = DirectX::XMLoadFloat(&this->m_base);
			auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

			return DirectX::XMVector2NotEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            return this->m_base != data.m_base;
#endif
		}

		float operator[](unsigned int index) const
		{
			KOTEK_ASSERT(index == 0, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			float const* p_array =
				reinterpret_cast<float const*>(&this->m_base);

			return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

		float& operator[](unsigned int index)
		{
			KOTEK_ASSERT(index == 0, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			float* p_array = reinterpret_cast<float*>(&this->m_base);
			return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMLoadFloat(&this->m_base);
		}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

		float Get_X(void) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			return this->m_base;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            return this->m_base.x;
#endif
		}

		vector1f& Set_X(float x) noexcept
		{
            return this->operator=(x);
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		vector1f& Set_Base(const base_vec1_t& data) noexcept
		{
			this->m_base = data;
			return *this;
		}
#endif

		base_vec1_t& Get_Base(void) noexcept
		{
			return this->m_base;
		}
		const base_vec1_t& Get_Base(void) const noexcept
		{
			return this->m_base;
		}

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

		result.Set_X(value);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
        return (a.Get_Base() + b.Get_Base());
#endif
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

		result.Set_X(value);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
        return (a.Get_Base() - b.Get_Base());
#endif
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

		result.Set_X(value);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
        return (a.Get_Base() * b.Get_Base());
#endif
	}

	inline vector1f operator*(const vector1f& a, float b) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = a;
		auto temp = DirectX::XMVectorScale(v1, b);

		vector1f result;
		float value;

		DirectX::XMStoreFloat(&value, temp);

		result.Set_X(value);

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

		result.Set_X(value);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
        return (a.Get_Base() / b.Get_Base());
#endif
	}

	inline vector1f operator/(const vector1f& a, float b) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = a;
		auto temp = DirectX::XMVectorScale(v1, 1.f / b);

		vector1f result;
		float value;

		DirectX::XMStoreFloat(&value, temp);

		result.Set_X(value);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
        return (a.Get_Base() / b);
#endif
	}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
