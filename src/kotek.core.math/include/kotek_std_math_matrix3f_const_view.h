#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrix3f_const_view_t
{
	matrix3f_const_view_t(const float* p_values) : m_p_values(p_values) {}

	matrix3f_const_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline const float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline const float& y(void) noexcept { return this->m_p_values[1]; }

	inline float z(void) const noexcept { return this->m_p_values[2]; }
	inline const float& z(void) noexcept { return this->m_p_values[2]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline const float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline const float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[3]);
	}

private:
	const float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK