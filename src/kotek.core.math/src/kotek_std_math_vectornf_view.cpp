#include "../include/kotek_std_math_vectornf_view.h"

#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vectornf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

vectornf_view_t::vectornf_view_t(
	float* p_values, math_id_t row_count
) :
	_m_default(0.0f), m_row_count(row_count),
	m_p_values(p_values)
{
	KOTEK_ASSERT(m_row_count > 0, "pass valid data");
	KOTEK_ASSERT(p_values, "data must be valid!");
}

vectornf_view_t::vectornf_view_t() :
	_m_default(0.0f), m_row_count(0), m_p_values(nullptr)
{
}

float vectornf_view_t::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->operator[](row_id);
}

float& vectornf_view_t::e(
	math_id_t column_id, math_id_t row_id
) noexcept
{
	return this->operator[](row_id);
}

vectornf_view_t vectornf_view_t::c(math_id_t column_id
) const noexcept
{
	return *this;
}

void vectornf_view_t::set(
	float* p_data, math_id_t element_count
) noexcept
{
	KOTEK_ASSERT(p_data, "data must be valid");
	KOTEK_ASSERT(element_count > 0, "can't be null");
	KOTEK_ASSERT(
		this->m_row_count <= element_count, "overwrite memory!"
	);

	if (p_data && this->m_row_count <= element_count)
	{
		std::memcpy(
			this->m_p_values,
			p_data,
			sizeof(float) * element_count
		);
	}
}

void vectornf_view_t::set(const vectornf_view_t& view) noexcept
{
	KOTEK_ASSERT(view.data(), "data must be valid");
	KOTEK_ASSERT(view.get_row_count() > 0, "can't be null");
	KOTEK_ASSERT(
		this->m_row_count <= view.get_row_count(),
		"overwrite memory!"
	);

	if (view.data() &&
	    this->m_row_count <= view.get_row_count())
	{
		std::memcpy(
			this->m_p_values,
			view.data(),
			sizeof(float) * view.get_row_count()
		);
	}
}

void vectornf_view_t::set(const matrixnf_view_t& view) noexcept
{
}

void vectornf_view_t::set(const vector1f& vec) noexcept
{
	KOTEK_ASSERT(this->m_p_values, "data must be valid");
	KOTEK_ASSERT(this->m_row_count > 0, "data must be valid");

	if (this->m_p_values)
	{
		if (this->m_row_count > 0)
		{
			this->m_p_values[0] = vec.e(0, 0);
		}
	}
}

void vectornf_view_t::set(const vector2f& vec) noexcept
{
	KOTEK_ASSERT(this->m_p_values, "data must be valid");
	KOTEK_ASSERT(this->m_row_count > 0, "data must be valid");

	if (this->m_p_values)
	{
		if (this->m_row_count > 0)
		{
		}
	}
}

void vectornf_view_t::set(const vector3f& vec) noexcept {}

void vectornf_view_t::set(const vector4f& vec) noexcept {}

void vectornf_view_t::set(const matrix2x2f& mat) noexcept {}

void vectornf_view_t::set(const matrix3x3f& mat) noexcept {}

void vectornf_view_t::set(const matrix4x4f& mat) noexcept {}

float* vectornf_view_t::data(void) noexcept
{
	return this->m_p_values;
}

const float* vectornf_view_t::data(void) const noexcept
{
	return this->m_p_values;
}

float vectornf_view_t::operator[](math_id_t row_id
) const noexcept
{
	KOTEK_ASSERT(this->m_p_values, "data must be valid");

	if (this->m_p_values == nullptr)
		return 0.0f;

	KOTEK_ASSERT(row_id < this->m_row_count, "invalid row");

	if (row_id > this->m_row_count)
		row_id = 0;

	return this->m_p_values[row_id];
}

float& vectornf_view_t::operator[](math_id_t row_id) noexcept
{
	KOTEK_ASSERT(this->m_p_values, "data must be valid");

	if (this->m_p_values == nullptr)
		return _m_default;

	KOTEK_ASSERT(row_id < this->m_row_count, "invalid row");

	if (row_id > this->m_row_count)
		row_id = 0;

	return this->m_p_values[row_id];
}

vectornf_view_t&
vectornf_view_t::operator+=(const vectornf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator+=(const matrixnf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator+=(const vector1f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator+=(const vector2f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator+=(const vector3f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator+=(const vector4f& vec
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator+=(const matrix2x2f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator+=(const matrix3x3f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator+=(const matrix4x4f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator-=(const vectornf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator-=(const matrixnf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator-=(const vector1f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator-=(const vector2f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator-=(const vector3f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator-=(const vector4f& vec
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator-=(const matrix2x2f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator-=(const matrix3x3f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator-=(const matrix4x4f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator*=(const vectornf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator*=(const matrixnf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator*=(const vector1f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator*=(const vector2f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator*=(const vector3f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator*=(const vector4f& vec
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator*=(const matrix2x2f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator*=(const matrix3x3f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator*=(const matrix4x4f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator/=(const vectornf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator/=(const matrixnf_view_t& view
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator/=(const vector1f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator/=(const vector2f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator/=(const vector3f& vec
) noexcept
{
	return *this;
}

vectornf_view_t& vectornf_view_t::operator/=(const vector4f& vec
) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator/=(const matrix2x2f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator/=(const matrix3x3f& mat) noexcept
{
	return *this;
}

vectornf_view_t&
vectornf_view_t::operator/=(const matrix4x4f& mat) noexcept
{
	return *this;
}

float vectornf_view_t::x(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 1,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 1)
		{
			return this->m_p_values[0];
		}
	}

	return _m_default;
}

float& vectornf_view_t::x(void) noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 1,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 2)
		{
			return this->m_p_values[0];
		}
	}

	return _m_default;
}

float vectornf_view_t::y(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 2,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 2)
		{
			return this->m_p_values[1];
		}
	}

	return _m_default;
}

float& vectornf_view_t::y(void) noexcept
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 2,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 2)
		{
			return this->m_p_values[1];
		}
	}

	return _m_default;
}

float vectornf_view_t::z(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 3,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 3)
		{
			return this->m_p_values[2];
		}
	}

	return _m_default;
}

float& vectornf_view_t::z(void) noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 3,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 3)
		{
			return this->m_p_values[2];
		}
	}

	return _m_default;
}

float vectornf_view_t::w(void) const noexcept
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 4,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 4)
		{
			return this->m_p_values[3];
		}
	}

	return _m_default;
}

float& vectornf_view_t::w(void) noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 4,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 4)
		{
			return this->m_p_values[3];
		}
	}

	return _m_default;
}

vectornf_const_view_t::vectornf_const_view_t() :
	_m_default(0.0f), m_row_count(0), m_p_values(nullptr)
{
}

vectornf_const_view_t::vectornf_const_view_t(
	const float* p_values, math_id_t row_count
) :
	_m_default(0.0f), m_row_count(row_count),
	m_p_values(p_values)
{
	KOTEK_ASSERT(m_row_count > 0, "pass valid data");
	KOTEK_ASSERT(p_values, "data must be valid!");
}

const float vectornf_const_view_t::e(
	math_id_t column_id, math_id_t row_id
) const noexcept
{
	return this->operator[](row_id);
}

const float& vectornf_const_view_t::e(
	math_id_t column_id, math_id_t row_id
) noexcept
{
	return this->operator[](row_id);
}

vectornf_const_view_t
vectornf_const_view_t::c(math_id_t column_id) const noexcept
{
	return *this;
}

float vectornf_const_view_t::x(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(this->m_row_count >= 1, "initialized or correct dimension?");

	if (this->m_p_values)
	{
		if (this->m_row_count >= 1)
		{
			return this->m_p_values[0];
		}
	}

	return _m_default;
}

float vectornf_const_view_t::y(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(this->m_row_count >= 2, "initialized or correct dimension?");

	if (this->m_p_values)
	{
		if (this->m_row_count >= 2)
		{
			return this->m_p_values[1];
		}
	}

	return _m_default;
}

float vectornf_const_view_t::z(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(this->m_row_count >= 3, "initialized or correct dimension?");

	if (this->m_p_values)
	{
		if (this->m_row_count >= 3)
		{
			return this->m_p_values[2];
		}
	}

	return _m_default;
}

float vectornf_const_view_t::w(void) const noexcept 
{
	KOTEK_ASSERT(this->m_p_values, "initialized?");
	KOTEK_ASSERT(
		this->m_row_count >= 4,
		"initialized or correct dimension?"
	);

	if (this->m_p_values)
	{
		if (this->m_row_count >= 4)
		{
			return this->m_p_values[3];
		}
	}

	return _m_default;
}


const float vectornf_const_view_t::operator[](math_id_t row_id
) const noexcept
{
	KOTEK_ASSERT(this->m_p_values, "data must be valid");

	if (this->m_p_values == nullptr)
		return 0.0f;

	KOTEK_ASSERT(row_id < this->m_row_count, "invalid row");

	if (row_id > this->m_row_count)
		row_id = 0;

	return this->m_p_values[row_id];
}

const float& vectornf_const_view_t::operator[](math_id_t row_id
) noexcept
{
	KOTEK_ASSERT(this->m_p_values, "data must be valid");

	if (this->m_p_values == nullptr)
		return 0.0f;

	KOTEK_ASSERT(row_id < this->m_row_count, "invalid row");

	if (row_id > this->m_row_count)
		row_id = 0;

	return this->m_p_values[row_id];
}

math_id_t vectornf_const_view_t::size_of(void) const noexcept {}

math_id_t vectornf_const_view_t::get_column_count(void
) const noexcept
{
	return 1;
}

math_id_t vectornf_const_view_t::get_row_count(void
) const noexcept
{
	return this->m_row_count;
}

const float* vectornf_const_view_t::data(void) const noexcept
{
	return this->m_p_values;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK