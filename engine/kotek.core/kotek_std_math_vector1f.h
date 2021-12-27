#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector1f
			{
			public:
#pragma region Constructors
				vector1f(base_decimal_t x) : m_base(x) {}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
				vector1f(const base_vec1_t& data) : m_base(data) {}
#endif
				vector1f(const vector1f& data) : m_base(data.m_base) {}
				vector1f(void) : m_base{} {}
#pragma endregion

				~vector1f() = default;

#pragma region Assigment operators
				vector1f& operator=(const vector1f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				vector1f& operator+=(base_decimal_t value)
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

				vector1f& operator-=(base_decimal_t value)
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					auto casted_original = DirectX::XMLoadFloat(&this->m_base);
					auto casted_argument = DirectX::XMLoadFloat(&value);
					auto result = DirectX::XMVectorSubtract(
						casted_original, casted_argument);

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
					this->m_base -= value;
					return *this;
				}
#endif

				vector1f& operator*=(base_decimal_t value)
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					auto casted_original = DirectX::XMLoadFloat(&this->m_base);
					auto result =
						DirectX::XMVectorScale(casted_original, value);

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
					auto result = DirectX::XMVectorMultiply(
						casted_original, casted_argument);

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
					this->m_base *= value;
					return *this;
				}
#endif

				vector1f& operator/=(base_decimal_t value)
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					KOTEK_ASSERT(
						value != 0.0f, "you can't divide if you have zero!!!");

					auto casted_original = DirectX::XMLoadFloat(&this->m_base);
					auto result =
						DirectX::XMVectorScale(casted_original, 1.f / value);
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
					auto result = DirectX::XMVectorDivide(
						casted_original, casted_argument);

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
					this->m_base /= value;
					return *this;
				}
#endif

				vector1f& operator%=(base_decimal_t value) noexcept
				{
					this->m_base = std::fmod(this->m_base, value);
					return *this;
				}

				vector1f& operator%=(const vector1f& data) noexcept
				{
					this->m_base = std::fmod(this->m_base, data.m_base);
					return *this;
				}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
				vector1f& operator%=(const base_vec1_t& data) noexcept
				{
					this->m_base %= data;
					return *this;
				}
#endif
#pragma endregion

#pragma region Unary operators
				vector1f operator+() const noexcept { return *this; }
				vector1f operator-() const noexcept
				{
					return vector1f(-this->m_base);
				}
#pragma endregion

#pragma region Comparison operators
				bool operator==(const vector1f& data) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					auto casted_original = DirectX::XMLoadFloat(&this->m_base);
					auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

					return DirectX::XMVector2Equal(
						casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				bool operator!=(const vector1f& data) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					auto casted_original = DirectX::XMLoadFloat(&this->m_base);
					auto casted_argument = DirectX::XMLoadFloat(&data.m_base);

					return DirectX::XMVector2NotEqual(
						casted_original, casted_argument);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}
#pragma endregion

#pragma region Cast operators

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				operator DirectX::XMVECTOR() const noexcept
				{
					return DirectX::XMLoadFloat(&this->m_base);
				}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

#pragma endregion

				base_decimal_t Get_X(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
				}

				vector1f& Set_X(base_decimal_t x) noexcept
				{
					this->m_base = x;
					return *this;
				}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
				vector1f& Set_Base(const base_vec1_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}
#endif

				base_vec1_t& Get_Base(void) noexcept { return this->m_base; }
				const base_vec1_t& Get_Base(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_vec1_t m_base;
			};

#pragma region Binary operators
			inline vector1f operator+(
				const vector1f& a, const vector1f& b) noexcept
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

#endif
			}

			inline vector1f operator-(
				const vector1f& a, const vector1f& b) noexcept
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
#endif
			}

			inline vector1f operator*(
				const vector1f& a, const vector1f& b) noexcept
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

#endif
			}

			inline vector1f operator*(
				const vector1f& a, base_decimal_t b) noexcept
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

#endif
			}

			inline vector1f operator*(
				base_decimal_t a, const vector1f& b) noexcept
			{
				return operator*(b, a);
			}

			inline vector1f operator/(
				const vector1f& a, const vector1f& b) noexcept
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

#endif
			}

			inline vector1f operator/(
				const vector1f& a, base_decimal_t b) noexcept
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
#endif
			}

#pragma endregion
		} // namespace math
	}     // namespace ktk
} // namespace Kotek