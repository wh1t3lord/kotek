#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class quaternionf
			{
			public:
				quaternionf(base_decimal_t x, base_decimal_t y,
					base_decimal_t z, base_decimal_t w) :
					m_base(x, y, z, w)
				{
				}
				quaternionf(const base_quat_t& data) : m_base(data) {}
				quaternionf(const quaternionf& data) : m_base(data.m_base) {}

				quaternionf(void) = default;
				~quaternionf(void) = default;

				quaternionf& operator=(const quaternionf& data)
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

			private:
				base_quat_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek