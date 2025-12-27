#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct vectornf_view_t
{
	vectornf_view_t();
	vectornf_view_t(float* p_values, math_id_t row_count);

	/// @brief e means element you access element by column and
	/// then by row
	/// @param column_id will be clamped to 0 if value is
	/// positive
	/// @param row_id if value is higher than you constructed
	/// (row_count arg in constructor) then it will return value
	/// of [0] element by row
	/// @return
	float e(math_id_t column_id, math_id_t row_id) const noexcept;

	/// @brief
	/// @param column_id
	/// @param row_id
	/// @return
	float& e(math_id_t column_id, math_id_t row_id) noexcept;

	/// @brief c means column and you access to only one
	/// possible column as 0 (first column by sense, because
	/// vector in column based representation is single column
	/// matrix)
	/// @param column_id will be clamped to 0 if value is
	/// positive
	/// @return just itself
	vectornf_view_t c(math_id_t column_id) const noexcept;

	/// @brief 
	/// @param c 
	/// @param element_count 
	void set(float* p_data, math_id_t element_count) noexcept;

	void set(const vectornf_view_t& view) noexcept;

	void set(const matrixnf_view_t& view) noexcept;

	void set(const vector1f& vec) noexcept;
	void set(const vector2f& vec) noexcept;
	void set(const vector3f& vec) noexcept;
	void set(const vector4f& vec) noexcept;

	void set(const matrix2x2f& mat) noexcept;
	void set(const matrix3x3f& mat) noexcept;
	void set(const matrix4x4f& mat) noexcept;

	// PLUS

	vectornf_view_t& operator+=(const vectornf_view_t& view
	) noexcept;
	vectornf_view_t& operator+=(const matrixnf_view_t& view
	) noexcept;
	vectornf_view_t& operator+=(const vector1f& vec) noexcept;
	vectornf_view_t& operator+=(const vector2f& vec) noexcept;
	vectornf_view_t& operator+=(const vector3f& vec) noexcept;
	vectornf_view_t& operator+=(const vector4f& vec) noexcept;
	vectornf_view_t& operator+=(const matrix2x2f& mat) noexcept;
	vectornf_view_t& operator+=(const matrix3x3f& mat) noexcept;
	vectornf_view_t& operator+=(const matrix4x4f& mat) noexcept;

	// MINUS

	vectornf_view_t& operator-=(const vectornf_view_t& view
	) noexcept;
	vectornf_view_t& operator-=(const matrixnf_view_t& view
	) noexcept;
	vectornf_view_t& operator-=(const vector1f& vec) noexcept;
	vectornf_view_t& operator-=(const vector2f& vec) noexcept;
	vectornf_view_t& operator-=(const vector3f& vec) noexcept;
	vectornf_view_t& operator-=(const vector4f& vec) noexcept;
	vectornf_view_t& operator-=(const matrix2x2f& mat) noexcept;
	vectornf_view_t& operator-=(const matrix3x3f& mat) noexcept;
	vectornf_view_t& operator-=(const matrix4x4f& mat) noexcept;

	// MUL

	vectornf_view_t& operator*=(const vectornf_view_t& view
	) noexcept;
	vectornf_view_t& operator*=(const matrixnf_view_t& view
	) noexcept;
	vectornf_view_t& operator*=(const vector1f& vec) noexcept;
	vectornf_view_t& operator*=(const vector2f& vec) noexcept;
	vectornf_view_t& operator*=(const vector3f& vec) noexcept;
	vectornf_view_t& operator*=(const vector4f& vec) noexcept;
	vectornf_view_t& operator*=(const matrix2x2f& mat) noexcept;
	vectornf_view_t& operator*=(const matrix3x3f& mat) noexcept;
	vectornf_view_t& operator*=(const matrix4x4f& mat) noexcept;

	// DIV

	vectornf_view_t& operator/=(const vectornf_view_t& view
	) noexcept;
	vectornf_view_t& operator/=(const matrixnf_view_t& view
	) noexcept;
	vectornf_view_t& operator/=(const vector1f& vec) noexcept;
	vectornf_view_t& operator/=(const vector2f& vec) noexcept;
	vectornf_view_t& operator/=(const vector3f& vec) noexcept;
	vectornf_view_t& operator/=(const vector4f& vec) noexcept;
	vectornf_view_t& operator/=(const matrix2x2f& mat) noexcept;
	vectornf_view_t& operator/=(const matrix3x3f& mat) noexcept;
	vectornf_view_t& operator/=(const matrix4x4f& mat) noexcept;

	float operator[](math_id_t row_id) const noexcept;
	float& operator[](math_id_t row_id) noexcept;

	math_id_t size_of(void) const noexcept;
	math_id_t get_column_count(void) const noexcept;
	math_id_t get_row_count(void) const noexcept;

	float* data(void) noexcept;
	const float* data(void) const noexcept;

private:
	float _m_default;
	math_id_t m_row_count;
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK