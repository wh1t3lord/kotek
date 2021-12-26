#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector2f
			{
			public:
#pragma region Constructors
				vector2f(base_decimal_t x, base_decimal_t y) : m_base(x, y) {}
				vector2f(const base_vec2_t& data) : m_base(data) {}
				vector2f(const vector2f& data) : m_base(data.m_base) {}
				vector2f(void) : m_base{} {};
#pragma endregion

				~vector2f(void) = default;

#pragma region Assignment operators
				vector2f& operator=(const vector2f& data) noexcept
				{
					this->m_base = data.m_base;
					return *this;
				}

				vector2f& operator=(const base_vec2_t& data) noexcept
				{
					this->m_base = data;
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
#pragma endregion

#pragma region Unary operators

#pragma endregion

#pragma region Comparison operators

#pragma endregion

#pragma region Cast operators
				operator DirectX::XMVECTOR() const noexcept
				{
					return DirectX::XMLoadFloat2(&this->m_base);
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

				vector2f& Set_X(base_decimal_t value) noexcept
				{
					this->m_base.x = value;
					return *this;
				}

				vector2f& Set_Y(base_decimal_t value) noexcept
				{
					this->m_base.y = value;
					return *this;
				}

			private:
				base_vec2_t m_base;
			};

#pragma region Binary operators

#pragma endregion

		} // namespace math
	}     // namespace ktk
} // namespace Kotek