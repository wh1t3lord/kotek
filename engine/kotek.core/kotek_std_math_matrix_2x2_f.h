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
				matrix2x2f(void) {}
				~matrix2x2f(void) {}

				const base_mat2x2_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

				matrix2x2f& operator=(const matrix2x2f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				matrix2x2f& operator=(const base_mat2x2_t& data)
				{
					this->m_base = data;
					return *this;
				}

			private:
				base_mat2x2_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek