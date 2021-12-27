#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector4f
			{
			public:
#pragma region Constructors
				vector4f(base_decimal_t x, base_decimal_t y, base_decimal_t z,
					base_decimal_t w) :
					m_base(x, y, z, w)
				{
				}
				vector4f(const base_vec4_t& data) : m_base(data) {}
				vector4f(const vector4f& data) : m_base(data.m_base) {}
				vector4f(void) : m_base{} {};
#pragma endregion

				~vector4f(void) = default;

#pragma region Assignment operators
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
#endif
					return *this;
				}

				vector4f& operator-=(const vector4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;
					auto result = DirectX::XMVectorSubtract(
						casted_original, casted_argument);

					DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				vector4f& operator-=(const base_vec4_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument =
						DirectX::XMLoadFloat4(&data);
					auto result = DirectX::XMVectorSubtract(
						casted_original, casted_argument);

					DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				vector4f& operator*=(const vector4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;
					auto result = DirectX::XMVectorMultiply(
						casted_original, casted_argument);

					DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector4f& operator*=(const base_vec4_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument =
						DirectX::XMLoadFloat4(&data);
					auto result = DirectX::XMVectorMultiply(
						casted_original, casted_argument);

					DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector4f& operator/=(const vector4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;
					auto result = DirectX::XMVectorDivide(
						casted_original, casted_argument);

					DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector4f& operator/=(const base_vec4_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument =
						DirectX::XMLoadFloat4(&data);
					auto result = DirectX::XMVectorDivide(
						casted_original, casted_argument);

					DirectX::XMStoreFloat4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector4f& operator%=(base_decimal_t value) noexcept
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
#pragma endregion

#pragma region Unary operators
				vector4f operator+() const noexcept { return *this; }
				vector4f operator-() const noexcept
				{
					return vector4f(-this->m_base.x, -this->m_base.y,
						-this->m_base.z, -this->m_base.w);
				}
#pragma endregion

#pragma region Comparison operators
				bool operator==(const vector4f& data) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;

					return DirectX::XMVector4Equal(
						casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				bool operator!=(const vector4f& data) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;

					return DirectX::XMVector4NotEqual(
						casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}
#pragma endregion

#pragma region Cast operators
				operator DirectX::XMVECTOR() const noexcept
				{
					return DirectX::XMLoadFloat4(&this->m_base);
				}
#pragma endregion

				base_decimal_t Get_X(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base.x;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				base_decimal_t Get_Y(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base.y;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				base_decimal_t Get_Z(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base.z;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_W(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base.w;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				vector4f& Set_X(base_decimal_t value) noexcept
				{
					this->m_base.x = value;
					return *this;
				}

				vector4f& Set_Y(base_decimal_t value) noexcept
				{
					this->m_base.y = value;
					return *this;
				}

				vector4f& Set_Z(base_decimal_t value) noexcept
				{
					this->m_base.z = value;
					return *this;
				}

				vector4f& Set_W(base_decimal_t value) noexcept 
				{ 
					this->m_base.w = value;
					return *this;
				}

				vector4f& Set_Base(const base_vec4_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}

			private:
				base_vec4_t m_base;
			};

#pragma region Binary operators
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

#endif
			}

			inline vector4f operator*(
				const vector4f& left, base_decimal_t right) noexcept
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

#endif
			}

			inline vector4f operator*(
				base_decimal_t left, const vector4f& right) noexcept
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

#endif
			}

			inline vector4f operator/(
				const vector4f& left, base_decimal_t right) noexcept
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

#endif
			}
#pragma endregion
		} // namespace math
	}     // namespace ktk
} // namespace Kotek