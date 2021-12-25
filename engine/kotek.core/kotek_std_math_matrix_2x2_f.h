#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class matrix2x2f
			{
			public:
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				matrix2x2f(const matrix2x2f& data) :
					m_row_1(data.m_row_1), m_row_2(data.m_row_2)
				{
				}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

				matrix2x2f(void) = default;
				~matrix2x2f(void) = default;

				base_decimal_t Get_00(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_row_1.x;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_01(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_row_1.y;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_10(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_row_2.x;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_11(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_row_2.y;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				matrix2x2f& operator=(const matrix2x2f& data)
				{
					this->m_row_1 = data.m_row_1;
					this->m_row_2 = data.m_row_2;

					return *this;
				}

			private:
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				base_vec2_t m_row_1;
				base_vec2_t m_row_2;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek