#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace math
{
	class vector4f
	{
	public:
		vector4f(float x, float y, float z, float w) : m_base(x, y, z, w) {}
		vector4f(const base_vec4_t& data) : m_base(data) {}
		vector4f(const vector4f& data) : m_base(data.m_base) {}
		vector4f(void) : m_base{} {}

		~vector4f(void) = default;

		vector4f& operator=(const vector4f& data) noexcept
		{
			this->m_base = data.m_base;
			return *this;
		}

		vector4f& operator+=(const vector4f& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR v1 = *this;
			DirectX::XMVECTOR v2 = data;
			auto result = DirectX::XMVectorAdd(v1, v2);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base += data.m_base;
#endif
			return *this;
		}

		vector4f& operator+=(const base_vec4_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR v1 = *this;
			DirectX::XMVECTOR v2 = DirectX::XMLoadFloat4(&data);
			auto result = DirectX::XMVectorAdd(v1, v2);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base += data;
#endif
			return *this;
		}

		vector4f& operator-=(const vector4f& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			auto result =
				DirectX::XMVectorSubtract(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base -= data.m_base;
#endif
			return *this;
		}

		vector4f& operator-=(const base_vec4_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat4(&data);
			auto result =
				DirectX::XMVectorSubtract(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base -= data;
#endif
			return *this;
		}

		vector4f& operator*=(const vector4f& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			auto result =
				DirectX::XMVectorMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base *= data.m_base;
#endif
			return *this;
		}

		vector4f& operator*=(const base_vec4_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat4(&data);
			auto result =
				DirectX::XMVectorMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base *= data;
#endif
			return *this;
		}

		vector4f& operator*=(float value) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR v1 = *this;
			auto result = DirectX::XMVectorScale(v1, value);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base *= value;
#endif
			return *this;
		}

		vector4f& operator/=(const vector4f& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			auto result =
				DirectX::XMVectorDivide(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base /= data.m_base;
#endif
			return *this;
		}

		vector4f& operator/=(const base_vec4_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat4(&data);
			auto result =
				DirectX::XMVectorDivide(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            this->m_base /= data;
#endif
			return *this;
		}

		vector4f& operator/=(float value) noexcept
		{
			return this->operator*=(1.f / value);
		}

		vector4f& operator%=(float value) noexcept
		{
			this->m_base.x = std::fmod(this->m_base.x, value);
			this->m_base.y = std::fmod(this->m_base.y, value);
			this->m_base.z = std::fmod(this->m_base.z, value);
			this->m_base.w = std::fmod(this->m_base.w, value);

			return *this;
		}

		vector4f& operator%=(const vector4f& data) noexcept
		{
			this->m_base.x = std::fmod(this->m_base.x, data.Get_X());
			this->m_base.y = std::fmod(this->m_base.y, data.Get_Y());
			this->m_base.z = std::fmod(this->m_base.z, data.Get_Z());
			this->m_base.w = std::fmod(this->m_base.w, data.Get_W());

			return *this;
		}

		vector4f operator+() const noexcept
		{
			return *this;
		}
		vector4f operator-() const noexcept
		{
			return vector4f(-this->m_base.x, -this->m_base.y, -this->m_base.z,
				-this->m_base.w);
		}

		bool operator==(const vector4f& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;

			return DirectX::XMVector4Equal(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            return this->m_base == data.m_base;
#endif
		}

		bool operator!=(const vector4f& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;

			return DirectX::XMVector4NotEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
            return this->m_base != data.m_base;
#endif
		}

		float operator[](unsigned int index) const
		{
			KOTEK_ASSERT(index <= 3, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			float const* p_array =
				reinterpret_cast<float const*>(&this->m_base);

			return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

		float& operator[](unsigned int index)
		{
			KOTEK_ASSERT(index <= 3, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			float* p_array = reinterpret_cast<float*>(&this->m_base);
			return p_array[index];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMLoadFloat4(&this->m_base);
		}
#endif

		float Get_X(void) const noexcept
		{
			return this->m_base.x;
		}

		float Get_Y(void) const noexcept
		{
			return this->m_base.y;
		}

		float Get_Z(void) const noexcept
		{
			return this->m_base.z;
		}

		float Get_W(void) const noexcept
		{
			return this->m_base.w;
		}

		vector4f& Set_X(float value) noexcept
		{
			this->m_base.x = value;
			return *this;
		}

		vector4f& Set_Y(float value) noexcept
		{
			this->m_base.y = value;
			return *this;
		}

		vector4f& Set_Z(float value) noexcept
		{
			this->m_base.z = value;
			return *this;
		}

		vector4f& Set_W(float value) noexcept
		{
			this->m_base.w = value;
			return *this;
		}

		vector4f& Set_Base(const base_vec4_t& data) noexcept
		{
			this->m_base = data;
			return *this;
		}

        base_vec4_t& Get_Base(void) noexcept
        {
            return this->m_base;
        }

        const base_vec4_t& Get_Base(void) const noexcept
        {
            return this->m_base;
        }

	private:
		base_vec4_t m_base;
	};

	inline vector4f operator+(
		const vector4f& left, const vector4f& right) noexcept
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

	inline vector4f operator-(
		const vector4f& left, const vector4f& right) noexcept
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

	inline vector4f operator*(
		const vector4f& left, const vector4f& right) noexcept
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

	inline vector4f operator/(
		const vector4f& left, const vector4f& right) noexcept
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
} // namespace math

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
