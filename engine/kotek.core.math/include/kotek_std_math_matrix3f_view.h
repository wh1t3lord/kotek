#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

/// \~english @brief universal representation of matrix's column or row. Sadly
/// but some math libraries doesn't have matrix representation as set of
/// vectors. This class is a representation of row or column for matrix which
/// dimension size is 3 for a row or a column respectively. In order to bind
/// data you just can call method data(void) and call static class method
/// size_of(void). If you just apply sizeof for this class as regulary sizeof
/// works you won't get the real size of expected vector's dimension size so you
/// can't map data with method data and compiler's sizeof operator keep this in
/// mind.
struct matrix3f_view_t
{
	matrix3f_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline float& y(void) noexcept { return this->m_p_values[1]; }

	inline float z(void) const noexcept { return this->m_p_values[2]; }
	inline float& z(void) noexcept { return this->m_p_values[2]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[3]);
	}

private:
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK