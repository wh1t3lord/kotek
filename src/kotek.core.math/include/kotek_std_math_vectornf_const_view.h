#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct vectornf_const_view_t
{
	vectornf_const_view_t(const float* p_values, math_id_t row_count);

	/// @brief e means element you access element by column and
	/// then by row
	/// @param column_id will be clamped to 0 if value is
	/// positive
	/// @param row_id if value is higher than you constructed
	/// (row_count arg in constructor) then it will return value
	/// of [0] element by row
	/// @return
	const float
	e(math_id_t column_id, math_id_t row_id) const noexcept;

	/// @brief
	/// @param column_id
	/// @param row_id
	/// @return
	const float& e(math_id_t column_id, math_id_t row_id) noexcept;

	/// @brief c means column and you access to only one
	/// possible column as 0 (first column by sense, because
	/// vector in column based representation is single column
	/// matrix)
	/// @param column_id will be clamped to 0 if value is
	/// positive
	/// @return just itself
	vectornf_const_view_t c(math_id_t column_id) const noexcept;


	const float operator[](math_id_t row_id) const noexcept;
	const float& operator[](math_id_t row_id) noexcept;

	math_id_t size_of(void) const noexcept;
	math_id_t get_column_count(void) const noexcept;
	math_id_t get_row_count(void) const noexcept;

	const float* data(void) const noexcept;

private:
	float _m_default;
	math_id_t m_row_count;
	const float* m_p_values;
};




KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK