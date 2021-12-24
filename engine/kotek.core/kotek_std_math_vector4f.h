#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector4f
			{
			public:
				vector4f(void) = default;
				vector4f(float x, float y, float z, float w) :
					m_base(x, y, z, w)
				{
				}

				vector4f(const base_vec4_t& data) : m_base(data) {}

				~vector4f(void) {}

				const base_vec4_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

				vector4f& operator=(const vector4f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

			private:
				base_vec4_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek