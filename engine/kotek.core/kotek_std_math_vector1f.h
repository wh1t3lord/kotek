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
					this->m_base += value;
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
					this->m_base -= value;
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
					this->m_base *= value;
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
					this->m_base /= value;
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

				vector1f& operator^=(base_decimal_t value) noexcept 
				{
					this->m_base = this->m_base ^ value;
					return *this;
				}

				

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