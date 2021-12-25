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
				vector1f(base_decimal_t x) : m_base(x) {}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM

#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
				vector1f(const base_vec1_t& data) : m_base(data) {}
#endif

				vector1f(const vector1f& data) : m_base(data.m_base) {}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				vector1f(void) : m_base{} {}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif

				~vector1f() = default;

				vector1f& operator=(const vector1f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				vector1f& operator=(const base_vec1_t& data)
				{
					this->m_base = data;
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
				vector1f& Set_X(const base_vec1_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}
#endif

			private:
				base_vec1_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek