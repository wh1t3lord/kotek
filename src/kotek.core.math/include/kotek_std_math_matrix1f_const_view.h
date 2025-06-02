#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrix1f_const_view_t
{
	matrix1f_const_view_t(const float* p_values) : m_p_values(p_values) {}
	matrix1f_const_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline const float& x(void) noexcept { return this->m_p_values[0]; }

	inline float operator[](unsigned char index) const noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return this->m_p_values[0];
	}

	inline const float& operator[](unsigned char index) noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return this->m_p_values[0];
	}

	inline const float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[1]);
	}

private:
	const float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK