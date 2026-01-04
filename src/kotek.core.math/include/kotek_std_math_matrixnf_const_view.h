#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrixnf_const_view_t
{
	matrixnf_const_view_t(
		const float* p_values,
		math_id_t column_count,
		math_id_t row_count
	);

	const float
	e(math_id_t column_id, math_id_t row_id) const noexcept;
	const float& e(math_id_t column_id, math_id_t row_id) noexcept;

	vectornf_const_view_t c(math_id_t column_id) const noexcept;

	vectornf_const_view_t operator[](math_id_t column_id
	) const noexcept;

	const float* data(void) const noexcept;

	math_id_t size_of(void) const noexcept;
	math_id_t get_column_count(void) const noexcept;
	math_id_t get_row_count(void) const noexcept;

private:
	float _m_default;
	math_id_t m_column_count;
	math_id_t m_row_count;
	const float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK