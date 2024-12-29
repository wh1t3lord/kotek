#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrix2f_view_t
{
	matrix2f_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline float& y(void) noexcept { return this->m_p_values[1]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		return this->m_p_values[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		return this->m_p_values[index];
	}

	inline float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return static_cast<unsigned char>(sizeof(float[2]));
	}

private:
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK