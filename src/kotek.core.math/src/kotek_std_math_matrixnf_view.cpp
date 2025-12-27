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

vectornf_view_t matrixnf_view_t::c(math_id_t column_id
) const noexcept
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
	}

	return result;
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK