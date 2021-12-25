#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class matrix4x4f
			{
			public:
				matrix4x4f(const base_mat4x4_t& data) : m_base(data) {}
				matrix4x4f(const matrix4x4f& data) : m_base(data.m_base) {}

				matrix4x4f(void) = default;
				~matrix4x4f(void) = default;

				base_decimal_t Get_00(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._11;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_01(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._12;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_02(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._13;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_03(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._14;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_10(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._21;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_11(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._22;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_12(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._23;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_13(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._24;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_20(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._31;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_21(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._32;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_22(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._33;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_23(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._34;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_30(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._41;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_31(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._42;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_32(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._43;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_33(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._44;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				matrix4x4f& operator=(const matrix4x4f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				matrix4x4f& operator=(const base_mat4x4_t& data)
				{
					this->m_base = data;
					return *this;
				}

			private:
				base_mat4x4_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek