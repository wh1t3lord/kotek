#pragma once

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector4f
			{
			public:
				vector4f(float x, float y, float z, float w) {}
				~vector4f(void) {}

				const base_vec4_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_vec4_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek