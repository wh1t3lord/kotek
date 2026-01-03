#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrixnf_view_t
{
	matrixnf_view_t(
		float* p_values,
		math_id_t column_count,
		math_id_t row_count
	);

	float
	e(math_id_t column_id, math_id_t row_id) const noexcept;
	float& e(math_id_t column_id, math_id_t row_id) noexcept;

	vectornf_view_t c(math_id_t column_id) noexcept;
	vectornf_const_view_t c(math_id_t column_id) const noexcept;


	void set(float* p_data, math_id_t element_count) noexcept;
	void
	set(float* p_data, math_id_t column_id, math_id_t row_id
	) noexcept;
	void
	set(math_id_t column_id,
	    float* p_data,
	    math_id_t element_count) noexcept;
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

	matrixnf_view_t& operator+=(const vectornf_view_t& view
	) noexcept;
	matrixnf_view_t& operator+=(const matrixnf_view_t& view
	) noexcept;
	matrixnf_view_t& operator+=(const vector1f& vec) noexcept;
	matrixnf_view_t& operator+=(const vector2f& vec) noexcept;
	matrixnf_view_t& operator+=(const vector3f& vec) noexcept;
	matrixnf_view_t& operator+=(const vector4f& vec) noexcept;
	matrixnf_view_t& operator+=(const matrix2x2f& mat) noexcept;
	matrixnf_view_t& operator+=(const matrix3x3f& mat) noexcept;
	matrixnf_view_t& operator+=(const matrix4x4f& mat) noexcept;

	// MINUS

	matrixnf_view_t& operator-=(const vectornf_view_t& view
	) noexcept;
	matrixnf_view_t& operator-=(const matrixnf_view_t& view
	) noexcept;
	matrixnf_view_t& operator-=(const vector1f& vec) noexcept;
	matrixnf_view_t& operator-=(const vector2f& vec) noexcept;
	matrixnf_view_t& operator-=(const vector3f& vec) noexcept;
	matrixnf_view_t& operator-=(const vector4f& vec) noexcept;
	matrixnf_view_t& operator-=(const matrix2x2f& mat) noexcept;
	matrixnf_view_t& operator-=(const matrix3x3f& mat) noexcept;
	matrixnf_view_t& operator-=(const matrix4x4f& mat) noexcept;


	// MULTIPLY

	matrixnf_view_t& operator*=(const vectornf_view_t& view
	) noexcept;
	matrixnf_view_t& operator*=(const matrixnf_view_t& view
	) noexcept;
	matrixnf_view_t& operator*=(const vector1f& vec) noexcept;
	matrixnf_view_t& operator*=(const vector2f& vec) noexcept;
	matrixnf_view_t& operator*=(const vector3f& vec) noexcept;
	matrixnf_view_t& operator*=(const vector4f& vec) noexcept;
	matrixnf_view_t& operator*=(const matrix2x2f& mat) noexcept;
	matrixnf_view_t& operator*=(const matrix3x3f& mat) noexcept;
	matrixnf_view_t& operator*=(const matrix4x4f& mat) noexcept;



	// DIVISION

	matrixnf_view_t& operator/=(const vectornf_view_t& view
	) noexcept;
	matrixnf_view_t& operator/=(const matrixnf_view_t& view
	) noexcept;
	matrixnf_view_t& operator/=(const vector1f& vec) noexcept;
	matrixnf_view_t& operator/=(const vector2f& vec) noexcept;
	matrixnf_view_t& operator/=(const vector3f& vec) noexcept;
	matrixnf_view_t& operator/=(const vector4f& vec) noexcept;
	matrixnf_view_t& operator/=(const matrix2x2f& mat) noexcept;
	matrixnf_view_t& operator/=(const matrix3x3f& mat) noexcept;
	matrixnf_view_t& operator/=(const matrix4x4f& mat) noexcept;


	float* data(void) noexcept;
	const float* data(void) const noexcept;

	math_id_t size_of(void) const noexcept;
	math_id_t get_column_count(void) const noexcept;
	math_id_t get_row_count(void) const noexcept;

private:
	float _m_default;
	math_id_t m_column_count;
	math_id_t m_row_count;
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK