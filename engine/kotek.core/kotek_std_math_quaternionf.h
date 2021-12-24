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
				quaternionf(void) = default;
				quaternionf(float x, float y, float z, float w) :
					m_base(x, y, z, w)
				{
				}

				quaternionf(const base_quat_t& data) : m_base(data) {}

				~quaternionf(void) {}

				const base_quat_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

				quaternionf& operator=(const quaternionf& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

			private:
				base_quat_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek