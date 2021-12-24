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
				vector1f(void) = default;
				vector1f(float x) : m_base(x) {}
				vector1f(const base_vec1_t& data) : m_base(data) {}

				~vector1f() {}

				const base_vec1_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

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

			private:
				base_vec1_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek