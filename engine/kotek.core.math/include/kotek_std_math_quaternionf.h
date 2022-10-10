#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace math
{
	class quaternionf
	{
	public:
		quaternionf(float x, float y, float z, float w) : m_base(x, y, z, w) {}
		quaternionf(const base_quat_t& data) : m_base(data) {}
		quaternionf(const quaternionf& data) : m_base(data.m_base) {}
		quaternionf(void) : m_base{} {}

		~quaternionf(void) = default;

		quaternionf& operator=(const quaternionf& data) noexcept
		{
			this->m_base = data.m_base;
			return *this;
		}

		quaternionf& operator=(const base_quat_t& data) noexcept
		{
			this->m_base = data;
			return *this;
		}

		quaternionf& operator+=(const quaternionf& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR v1 = *this;
			DirectX::XMVECTOR v2 = data;
			auto result = DirectX::XMVectorAdd(v1, v2);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			return *this;
		}

		quaternionf& operator+=(const base_quat_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR v1 = *this;
			DirectX::XMVECTOR v2 = DirectX::XMLoadFloat4(&data);
			auto result = DirectX::XMVectorAdd(v1, v2);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			return *this;
		}

		quaternionf& operator-=(const quaternionf& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			auto result =
				DirectX::XMVectorSubtract(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			return *this;
		}

		quaternionf& operator-=(const base_quat_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat4(&data);
			auto result =
				DirectX::XMVectorSubtract(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			return *this;
		}

		quaternionf& operator*=(const quaternionf& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			auto result =
				DirectX::XMQuaternionMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			return *this;
		}

		quaternionf& operator*=(const base_quat_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat4(&data);
			auto result =
				DirectX::XMQuaternionMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			return *this;
		}

		quaternionf& operator/=(const quaternionf& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;
			casted_argument = DirectX::XMQuaternionInverse(casted_argument);
			auto result =
				DirectX::XMQuaternionMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			return *this;
		}

		quaternionf& operator/=(const base_quat_t& data) noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = DirectX::XMLoadFloat4(&data);
			casted_argument = DirectX::XMQuaternionInverse(casted_argument);
			auto result =
				DirectX::XMQuaternionMultiply(casted_original, casted_argument);

			DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
			return *this;
		}

		quaternionf& operator%=(float value) noexcept
		{
			this->m_base.x = std::fmod(this->m_base.x, value);
			this->m_base.y = std::fmod(this->m_base.y, value);
			this->m_base.z = std::fmod(this->m_base.z, value);
			this->m_base.w = std::fmod(this->m_base.w, value);

			return *this;
		}

		quaternionf& operator%=(const quaternionf& data) noexcept
		{
			this->m_base.x = std::fmod(this->m_base.x, data.Get_X());
			this->m_base.y = std::fmod(this->m_base.y, data.Get_Y());
			this->m_base.z = std::fmod(this->m_base.z, data.Get_Z());
			this->m_base.w = std::fmod(this->m_base.w, data.Get_W());

			return *this;
		}

		quaternionf operator+() const noexcept
		{
			return *this;
		}
		quaternionf operator-() const noexcept
		{
			return quaternionf(-this->m_base.x, -this->m_base.y,
				-this->m_base.z, -this->m_base.w);
		}

		bool operator==(const quaternionf& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;

			return DirectX::XMQuaternionEqual(casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

		bool operator!=(const quaternionf& data) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			DirectX::XMVECTOR casted_original = *this;
			DirectX::XMVECTOR casted_argument = data;

			return DirectX::XMQuaternionNotEqual(
				casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
		}

		operator DirectX::XMVECTOR() const noexcept
		{
			return DirectX::XMLoadFloat4(&this->m_base);
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

		float Get_Z(void) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			return this->m_base.z;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
		}

		float Get_W(void) const noexcept
		{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
			return this->m_base.w;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		}

		quaternionf& Set_X(float value) noexcept
		{
			this->m_base.x = value;
			return *this;
		}

		quaternionf& Set_Y(float value) noexcept
		{
			this->m_base.y = value;
			return *this;
		}

		quaternionf& Set_Z(float value) noexcept
		{
			this->m_base.z = value;
			return *this;
		}

		quaternionf& Set_W(float value) noexcept
		{
			this->m_base.w = value;
			return *this;
		}

		quaternionf& Set_Base(const base_quat_t& data) noexcept
		{
			this->m_base = data;
			return *this;
		}

	private:
		base_quat_t m_base;
	};

	inline quaternionf operator+(
		const quaternionf& left, const quaternionf& right) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = left;
		DirectX::XMVECTOR v2 = right;
		auto temp = DirectX::XMVectorAdd(v1, v2);

		quaternionf result;
		base_quat_t data;

		DirectX::XMStoreFloat4(&data, temp);

		result.Set_Base(data);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
	}

	inline quaternionf operator-(
		const quaternionf& left, const quaternionf& right) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = left;
		DirectX::XMVECTOR v2 = right;
		auto temp = DirectX::XMVectorSubtract(v1, v2);

		quaternionf result;
		base_quat_t data;

		DirectX::XMStoreFloat4(&data, temp);

		result.Set_Base(data);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
	}

	inline quaternionf operator*(
		const quaternionf& left, const quaternionf& right) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = left;
		DirectX::XMVECTOR v2 = right;
		auto temp = DirectX::XMQuaternionMultiply(v1, v2);

		quaternionf result;
		base_quat_t data;

		DirectX::XMStoreFloat4(&data, temp);

		result.Set_Base(data);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
	}

	inline quaternionf operator*(const quaternionf& left, float right) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = left;
		auto temp = DirectX::XMVectorScale(v1, right);

		quaternionf result;
		base_quat_t data;

		DirectX::XMStoreFloat4(&data, temp);

		result.Set_Base(data);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
	}

	inline quaternionf operator*(float left, const quaternionf& right) noexcept
	{
		return operator*(right, left);
	}

	inline quaternionf operator/(
		const quaternionf& left, const quaternionf& right) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR v1 = left;
		DirectX::XMVECTOR v2 = right;
		v2 = DirectX::XMQuaternionInverse(v2);
		auto temp = DirectX::XMQuaternionMultiply(v1, v2);

		quaternionf result;
		base_quat_t data;

		DirectX::XMStoreFloat4(&data, temp);

		result.Set_Base(data);

		return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
	}
} // namespace math

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK