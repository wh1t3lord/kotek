#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector3f
			{
			public:
#pragma region Constructors
				vector3f(base_decimal_t x, base_decimal_t y, base_decimal_t z) :
					m_base(x, y, z)
				{
				}
				vector3f(const base_vec3_t& data) : m_base(data) {}
				vector3f(const vector3f& data) : m_base(data.m_base) {}
				vector3f(void) : m_base{} {};
#pragma endregion

				~vector3f(void) = default;

#pragma region Assignment operators
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
#endif
					return *this;
				}

				vector3f& operator+=(const base_vec3_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR v1 = *this;
					DirectX::XMVECTOR v2 = DirectX::XMLoadFloat3(&data);
					auto result = DirectX::XMVectorAdd(v1, v2);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				vector3f& operator-=(const vector3f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;
					auto result = DirectX::XMVectorSubtract(
						casted_original, casted_argument);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				vector3f& operator-=(const base_vec3_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument =
						DirectX::XMLoadFloat3(&data);
					auto result = DirectX::XMVectorSubtract(
						casted_original, casted_argument);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				vector3f& operator*=(const vector3f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;
					auto result = DirectX::XMVectorMultiply(
						casted_original, casted_argument);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector3f& operator*=(const base_vec3_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument =
						DirectX::XMLoadFloat3(&data);
					auto result = DirectX::XMVectorMultiply(
						casted_original, casted_argument);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector3f& operator*=(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR v1 = *this;
					auto result = DirectX::XMVectorScale(v1, value);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector3f& operator/=(const vector3f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;
					auto result = DirectX::XMVectorDivide(
						casted_original, casted_argument);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector3f& operator/=(const base_vec3_t& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument =
						DirectX::XMLoadFloat3(&data);
					auto result = DirectX::XMVectorDivide(
						casted_original, casted_argument);

					DirectX::XMStoreFloat3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				vector3f& operator/=(base_decimal_t value) noexcept
				{
					return this->operator*=(1.f / value);
				}

				vector3f& operator%=(base_decimal_t value) noexcept
				{
					this->m_base.x = std::fmod(this->m_base.x, value);
					this->m_base.y = std::fmod(this->m_base.y, value);
					this->m_base.z = std::fmod(this->m_base.z, value);

					return *this;
				}

				vector3f& operator%=(const vector3f& data) noexcept
				{
					this->m_base.x = std::fmod(this->m_base.x, data.Get_X());
					this->m_base.y = std::fmod(this->m_base.y, data.Get_Y());
					this->m_base.z = std::fmod(this->m_base.z, data.Get_Z());

					return *this;
				}
#pragma endregion

#pragma region Unary operators
				vector3f operator+() const noexcept { return *this; }
				vector3f operator-() const noexcept
				{
					return vector3f(
						-this->m_base.x, -this->m_base.y, -this->m_base.z);
				}
#pragma endregion

#pragma region Comparison operators
				bool operator==(const vector3f& data) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;

					return DirectX::XMVector3Equal(
						casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				bool operator!=(const vector3f& data) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR casted_original = *this;
					DirectX::XMVECTOR casted_argument = data;

					return DirectX::XMVector3NotEqual(
						casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}
#pragma endregion

#pragma region Cast operators
				operator DirectX::XMVECTOR() const noexcept
				{
					return DirectX::XMLoadFloat3(&this->m_base);
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

				vector3f& Set_X(base_decimal_t value) noexcept
				{
					this->m_base.x = value;
					return *this;
				}

				vector3f& Set_Y(base_decimal_t value) noexcept
				{
					this->m_base.y = value;
					return *this;
				}

				vector3f& Set_Z(base_decimal_t value) noexcept
				{
					this->m_base.z = value;
					return *this;
				}

				vector3f& Set_Base(const base_vec3_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}

			private:
				base_vec3_t m_base;
			};

#pragma region Binary operators
			inline vector3f operator+(
				const vector3f& left, const vector3f& right) noexcept
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
#endif
			}

			inline vector3f operator-(
				const vector3f& left, const vector3f& right) noexcept
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

#endif
			}

			inline vector3f operator*(
				const vector3f& left, const vector3f& right) noexcept
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

#endif
			}

			inline vector3f operator*(
				const vector3f& left, base_decimal_t right) noexcept
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

#endif
			}

			inline vector3f operator*(
				base_decimal_t left, const vector3f& right) noexcept
			{
				return operator*(right, left);
			}

			inline vector3f operator/(
				const vector3f& left, const vector3f& right) noexcept
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

#endif
			}

			inline vector3f operator/(
				const vector3f& left, base_decimal_t right) noexcept
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

#endif
			}
#pragma endregion
		} // namespace math
	}     // namespace ktk
} // namespace Kotek