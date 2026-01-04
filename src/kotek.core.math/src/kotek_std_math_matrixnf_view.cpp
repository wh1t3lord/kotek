#include "../include/kotek_std_math_matrixnf_view.h"

#include "../include/koteK_std_math_vectornf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vectornf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

matrixnf_view_t::matrixnf_view_t(
	float* p_values, math_id_t column_count, math_id_t row_count
) :
	_m_default(0.0f), m_column_count(column_count),
	m_row_count(row_count), m_p_values(p_values)
{
	KOTEK_ASSERT(column_count > 0, "valid data");
	KOTEK_ASSERT(row_count > 0, "valid data");
	KOTEK_ASSERT(p_values, "valid data");
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const vectornf_view_t& view
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrixnf_view_t& view
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector1f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector2f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector3f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector4f& vec
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrix2x2f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrix3x3f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrix4x4f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const vectornf_view_t& view
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrixnf_view_t& view
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector1f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector2f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector3f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector4f& vec
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrix2x2f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrix3x3f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrix4x4f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const vectornf_view_t& view
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrixnf_view_t& view
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector1f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector2f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector3f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector4f& vec
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrix2x2f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrix3x3f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrix4x4f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const vectornf_view_t& view
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrixnf_view_t& view
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector1f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector2f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector3f& vec
) noexcept
{
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector4f& vec
) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrix2x2f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrix3x3f& mat) noexcept
{
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrix4x4f& mat) noexcept
{
}

vectornf_view_t matrixnf_view_t::c(math_id_t column_id) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: provide impl for column base access
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vectornf_view_t result;

	KOTEK_ASSERT(this->m_p_values, "valid data");
	KOTEK_ASSERT(this->m_column_count > 0, "valid data");
	KOTEK_ASSERT(this->m_row_count > 0, "valid data");

	if (this->m_column_count > 0 && this->m_row_count > 0)
	{
		if (column_id > this->m_column_count)
			column_id = this->m_column_count;

		math_id_t id = column_id * this->m_row_count;

		result = vectornf_view_t(
			&this->m_p_values[id], this->m_row_count
		);
	}

	return result;
#endif
}

vectornf_const_view_t matrixnf_view_t::c(math_id_t column_id
) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: provide impl for column base access
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	vectornf_const_view_t result;

	KOTEK_ASSERT(this->m_p_values, "valid data");
	KOTEK_ASSERT(this->m_column_count > 0, "valid data");
	KOTEK_ASSERT(this->m_row_count > 0, "valid data");

	if (this->m_column_count > 0 && this->m_row_count > 0)
	{
		if (column_id > this->m_column_count)
			column_id = this->m_column_count;

		math_id_t id = column_id * this->m_row_count;

		result = vectornf_const_view_t(
			&this->m_p_values[id], this->m_row_count
		);
	}

	return result;
#endif
}

void matrixnf_view_t::set(
	float* p_data, math_id_t element_count
) noexcept
{
	KOTEK_ASSERT(p_data, "valid data");
	KOTEK_ASSERT(element_count > 0, "valid data");

	if (p_data && element_count > 0)
	{
		KOTEK_ASSERT(this->m_p_values, "valid data");
		KOTEK_ASSERT(this->m_column_count > 0, "valid data");
		KOTEK_ASSERT(this->m_row_count > 0, "valid data");

		if (this->m_p_values && this->m_column_count > 0 &&
		    this->m_row_count > 0)
		{
		}
	}
}

void matrixnf_view_t::set(
	float* p_data, math_id_t column_id, math_id_t row_id
) noexcept
{
	KOTEK_ASSERT(p_data, "valid data");
	KOTEK_ASSERT(column_id > 0, "valid data");
	KOTEK_ASSERT(row_id > 0, "valid data");

	if (p_data && column_id > 0 && row_id > 0)
	{
		KOTEK_ASSERT(this->m_p_values, "valid data");
		KOTEK_ASSERT(this->m_column_count > 0, "valid data");
		KOTEK_ASSERT(this->m_row_count > 0, "valid data");

		if (this->m_p_values && this->m_column_count > 0 &&
		    this->m_row_count > 0)
		{
		}
	}
}

void matrixnf_view_t::set(
	math_id_t column_id, float* p_data, math_id_t element_count
) noexcept
{
	KOTEK_ASSERT(p_data, "valid data");
	KOTEK_ASSERT(column_id > 0, "valid data");
	KOTEK_ASSERT(element_count > 0, "valid data");
	KOTEK_ASSERT(
		column_id < this->m_column_count, "out-of-range"
	);

	if (p_data && column_id > 0 && element_count > 0)
	{
		KOTEK_ASSERT(this->m_p_values, "valid data");
		KOTEK_ASSERT(this->m_column_count > 0, "valid data");
		KOTEK_ASSERT(this->m_row_count > 0, "valid data");

		if (this->m_p_values && this->m_column_count > 0 &&
		    this->m_row_count > 0)
		{
		}
	}
}

void matrixnf_view_t::set(const vectornf_view_t& view) noexcept
{
}

void matrixnf_view_t::set(const matrixnf_view_t& view) noexcept
{
}

void matrixnf_view_t::set(const vector1f& vec) noexcept {}

void matrixnf_view_t::set(const vector2f& vec) noexcept {}

void matrixnf_view_t::set(const vector3f& vec) noexcept {}

void matrixnf_view_t::set(const vector4f& vec) noexcept {}

void matrixnf_view_t::set(const matrix2x2f& mat) noexcept {}

void matrixnf_view_t::set(const matrix3x3f& mat) noexcept {}

void matrixnf_view_t::set(const matrix4x4f& mat) noexcept {}

math_id_t matrixnf_view_t::size_of(void) const noexcept
{
	return static_cast<math_id_t>(
		sizeof(float) * this->get_row_count() *
		this->get_column_count()
	);
}

math_id_t matrixnf_view_t::get_column_count(void) const noexcept
{
	return this->m_column_count;
}

math_id_t matrixnf_view_t::get_row_count(void) const noexcept
{
	return this->m_row_count;
}

vectornf_view_t
matrixnf_view_t::operator[](math_id_t column_id) noexcept
{
	return this->c(column_id);
}

vectornf_const_view_t
matrixnf_view_t::operator[](math_id_t column_id) const noexcept
{
	return this->c(column_id);
}

matrixnf_const_view_t::matrixnf_const_view_t(
	const float* p_values,
	math_id_t column_count,
	math_id_t row_count
) :
	_m_default(0.0f), m_column_count(column_count),
	m_row_count(row_count), m_p_values(p_values)
{
	KOTEK_ASSERT(p_values, "invalid data");
	KOTEK_ASSERT(column_count > 0, "invalid data");
	KOTEK_ASSERT(row_count > 0, "invalid data");
}

const float matrixnf_const_view_t::e(
	math_id_t column_id, math_id_t row_id
) const noexcept
{
	return this->c(column_id).e(0, row_id);
}

const float& matrixnf_const_view_t::e(
	math_id_t column_id, math_id_t row_id
) noexcept
{
	return this->c(column_id).e(0, row_id);
}

vectornf_const_view_t
matrixnf_const_view_t::c(math_id_t column_id) const noexcept
{
	KOTEK_ASSERT(this->m_p_values, "not initialized");
	KOTEK_ASSERT(
		column_id > this->m_column_count, "out-of-range"
	);

	if (column_id > this->get_column_count())
		column_id = this->get_column_count();

	return vectornf_const_view_t(
		&this->m_p_values[column_id * this->get_row_count()],
		this->get_row_count()
	);
}

vectornf_const_view_t
matrixnf_const_view_t::operator[](math_id_t column_id
) const noexcept
{
	return this->c(column_id);
}

const float* matrixnf_const_view_t::data(void) const noexcept
{
	return this->m_p_values;
}

math_id_t matrixnf_const_view_t::size_of(void) const noexcept
{
	return static_cast<math_id_t>(
		sizeof(float) * this->get_column_count() *
		this->get_row_count()
	);
}

math_id_t matrixnf_const_view_t::get_column_count(void
) const noexcept
{
	return this->m_column_count;
}

math_id_t matrixnf_const_view_t::get_row_count(void
) const noexcept
{
	return this->m_row_count;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK