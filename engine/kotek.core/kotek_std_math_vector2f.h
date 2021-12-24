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
				vector2f(void) = default;
				vector2f(float x, float y) : m_base(x, y) {}
				vector2f(const base_vec2_t& data) : m_base(data) {}

				~vector2f(void) {}

				const base_vec2_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

				vector2f& operator=(const vector2f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

			private:
				base_vec2_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek