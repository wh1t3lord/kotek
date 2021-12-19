#pragma once

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class vector1f
			{
			public:
				vector1f(float x) : m_base(x) {}
				~vector1f() {}

				const base_vec1_t& GetBaseType(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_vec1_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek