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

vector1f_view_t::vector1f_view_t(float* p_values) :
	_m_default(0.0f), m_p_values(p_values)
{
}

float vector1f_view_t::x(void) const noexcept
{
	if (this->m_p_values == nullptr)
		return 0.0f;

	return this->m_p_values[0];
}

float& vector1f_view_t::x(void) noexcept
{
	if (this->m_p_values == nullptr)
		return _m_default;

	return this->m_p_values[0];
}

float vector1f_view_t::operator[](size_t row_id) const noexcept
{
	KOTEK_ASSERT(row_id == 0, "send reasonable data");

	KOTEK_ASSERT(
		this->m_p_values,
		"must be initialized, data corruptiion?"
	);

	if (this->m_p_values == nullptr)
		return 0.0f;

	if (row_id > 0)
		row_id = 0;

	return this->m_p_values[row_id];
}

float& vector1f_view_t::operator[](size_t row_id) noexcept
{
	KOTEK_ASSERT(row_id == 0, "send reasonable data");

	KOTEK_ASSERT(
		this->m_p_values,
		"must be initialized, data corruptiion?"
	);

	if (this->m_p_values == nullptr)
		return _m_default;

	if (row_id > 0)
		row_id = 0;

	return this->m_p_values[row_id];
}

size_t vector1f_view_t::size_of(void) const noexcept
{
	return get_column_count() * sizeof(float) * get_row_count();
}

size_t vector1f_view_t::get_column_count(void) const noexcept
{
	return 1;
}

size_t vector1f_view_t::get_row_count(void) const noexcept
{
	return 1;
}

float vector1f_view_t::c0(size_t row_id) const noexcept
{
	return this->operator[](row_id);
}

float& vector1f_view_t::c0(size_t row_id) noexcept
{
	return this->operator[](row_id);
}

vector1f_view_t
vector1f_view_t::c0(void) const noexcept
{
	return vector1f_view_t(this->m_p_values);
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK