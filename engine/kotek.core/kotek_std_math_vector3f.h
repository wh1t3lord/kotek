#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector3f
			{
			public:
				vector3f(float x, float y, float z) : m_base(x, y, z) {}
				~vector3f() {}

				const base_vec3_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_vec3_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek