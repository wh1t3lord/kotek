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
				vector2f(base_decimal_t x, base_decimal_t y) : m_base(x, y) {}
				vector2f(const base_vec2_t& data) : m_base(data) {}
				vector2f(const vector2f& data) : m_base(data.m_base) {}

				vector2f(void) = default;
				~vector2f(void) = default;

				vector2f& operator=(const vector2f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

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

			private:
				base_vec2_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek