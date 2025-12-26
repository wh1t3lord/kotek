#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrixnf_view_t
{
	matrixnf_view_t(float* p_values, size_t column_count, size_t row_count);

	// PLUS

	// MINUS

	// MULTIPLY

	// DIVISION

	float* data(void) const noexcept;

	size_t size_of(void) const noexcept;
	size_t get_column_count(void) const noexcept;
	size_t get_row_count(void) const noexcept;

private:
	float _m_default;
	size_t m_column_count;
	size_t m_row_count;
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK