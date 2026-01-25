#include "../include/kotek_std_math_matrixnf_view.h"

#include "../include/koteK_std_math_vectornf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vectornf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_matrix_2x2_f.h"
#include "../include/kotek_std_math_matrix_3x3_f.h"
#include "../include/kotek_std_math_matrix_4x4_f.h"

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
	if (view.get_column_count() > 4 || view.get_row_count() > 4)
	{
		KOTEK_ASSERT(
			false,
			"not yet impl, todo: provide vectornf and matrixnf "
			"impls"
		);
	}
	else
	{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
		KOTEK_ASSERT(
			this->get_row_count() >= view.get_row_count(),
			"out-of-range"
		);
		KOTEK_ASSERT(
			this->get_column_count() >= view.get_column_count(),
			"out-of-range"
		);

		if (this->get_row_count() >= view.get_row_count())
		{
			if (this->get_column_count() >=
			    view.get_row_count())
			{
				for (math_id_t i = 0; i < view.get_row_count();
				     ++i)
				{
					this->c(i) += view;
				}
			}
		}
#else
		KOTEK_ASSERT(
			this->get_row_count() == view.get_row_count(),
			"broadcasting is not enabled thus a such operation "
			"where mxn + 1xk is not defined operation in "
			"linear algebra!"
		);

		KOTEK_ASSERT(
			this->get_column_count() == view.get_row_count(),
			"broadcasting is not enabled thus a such operation "
			"where mxn + 1xk is not defined operation in "
			"linear algebra!"
		);

		if (this->get_row_count() == view.get_row_count())
		{
			for (math_id_t i = 0; i < view.get_row_count(); ++i)
			{
				this->c(i) += view;
			}
		}
#endif
	}

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrixnf_view_t& view
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == view.get_column_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	KOTEK_ASSERT(
		this->get_row_count() == view.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 2:
	{
		matrix2x2f left(*this);
		matrix2x2f right(view);

		left += right;

		this->c(0).x() = left.e(0, 0);
		this->c(0).y() = left.e(0, 1);

		this->c(1).x() = left.e(1, 0);
		this->c(1).y() = left.e(1, 1);

		break;
	}
	case 3:
	{
		matrix3x3f left(*this);
		matrix3x3f right(view);

		left += right;

		this->c(0).x() = left.e(0, 0);
		this->c(0).y() = left.e(0, 1);
		this->c(0).z() = left.e(0, 2);

		this->c(1).x() = left.e(1, 0);
		this->c(1).y() = left.e(1, 1);
		this->c(1).z() = left.e(1, 2);

		this->c(2).x() = left.e(2, 0);
		this->c(2).y() = left.e(2, 1);
		this->c(2).z() = left.e(2, 2);

		break;
	}
	case 4:
	{
		matrix4x4f left(*this);
		matrix4x4f right(view);

		left += right;

		this->c(0).x() = left.e(0, 0);
		this->c(0).y() = left.e(0, 1);
		this->c(0).z() = left.e(0, 2);
		this->c(0).w() = left.e(0, 3);

		this->c(1).x() = left.e(1, 0);
		this->c(1).y() = left.e(1, 1);
		this->c(1).z() = left.e(1, 2);
		this->c(2).w() = left.e(1, 3);

		this->c(2).x() = left.e(2, 0);
		this->c(2).y() = left.e(2, 1);
		this->c(2).z() = left.e(2, 2);
		this->c(2).w() = left.e(2, 3);

		this->c(3).x() = left.e(3, 0);
		this->c(3).y() = left.e(3, 1);
		this->c(3).z() = left.e(3, 2);
		this->c(3).w() = left.e(3, 3);

		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector1f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->m_row_count >= vec.get_row_count(), "out of range"
	);

	if (this->m_row_count >= vec.get_row_count())
	{
		this->c(0) += vec;
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting!"
	);

	KOTEK_ASSERT(
		this->get_row_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == vec.get_row_count() &&
	    this->get_column_count() == vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector2f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->m_row_count >= vec.get_row_count(), "out of range"
	);

	if (this->m_row_count >= vec.get_row_count())
	{
		this->c(0) += vec;
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting!"
	);

	KOTEK_ASSERT(
		this->get_row_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == vec.get_row_count() &&
	    this->get_column_count() == vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector3f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->m_row_count >= vec.get_row_count(), "out of range"
	);

	if (this->m_row_count >= vec.get_row_count())
	{
		this->c(0) += vec;
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting!"
	);

	KOTEK_ASSERT(
		this->get_row_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == vec.get_row_count() &&
	    this->get_column_count() == vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator+=(const vector4f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->m_row_count >= vec.get_row_count(), "out of range"
	);

	if (this->m_row_count >= vec.get_row_count())
	{
		this->c(0) += vec;
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting!"
	);

	KOTEK_ASSERT(
		this->get_row_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == vec.get_row_count() &&
	    this->get_column_count() == vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrix2x2f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->m_row_count >= mat.get_row_count(), "out-of-range"
	);

	if (this->m_column_count >= mat.get_column_count())
	{
		if (this->m_row_count >= mat.get_row_count())
		{
			matrix2x2f casted(*this);
			casted += mat;
			this->c(0).x() = casted[0][0];
			this->c(0).y() = casted[0][1];
			this->c(1).x() = casted[1][0];
			this->c(1).y() = casted[1][1];
		}
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == mat.get_column_count(),
		"strict linear algebra rule, otherwise enable "
	    "broadcasting"
	);

	KOTEK_ASSERT(
		this->get_row_count() == mat.get_row_count(),
		"strict linear algebra rule, otherwise enable "
	    "broadcasting"
	);

	if (this->get_row_count() == mat.get_row_count() &&
	    this->get_column_count() == mat.get_column_count())
	{
		matrix2x2f casted(*this);
		casted += mat;

		this->c(0).x() = casted[0][0];
		this->c(0).y() = casted[0][1];

		this->c(1).x() = casted[1][0];
		this->c(1).y() = casted[1][1];
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrix3x3f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->m_row_count >= mat.get_row_count(), "out-of-range"
	);

	if (this->m_column_count >= mat.get_column_count())
	{
		if (this->m_row_count >= mat.get_row_count())
		{
			matrix2x2f casted(*this);
			casted += mat;
			this->c(0).x() = casted[0][0];
			this->c(0).y() = casted[0][1];
			this->c(1).x() = casted[1][0];
			this->c(1).y() = casted[1][1];
		}
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == mat.get_column_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	KOTEK_ASSERT(
		this->get_row_count() == mat.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == mat.get_row_count() &&
	    this->get_column_count() == mat.get_column_count())
	{
		matrix3x3f casted(*this);
		casted += mat;

		this->c(0).x() = casted[0][0];
		this->c(0).y() = casted[0][1];
		this->c(0).z() = casted[0][2];

		this->c(1).x() = casted[1][0];
		this->c(1).y() = casted[1][1];
		this->c(1).z() = casted[1][2];

		this->c(2).x() = casted[2][0];
		this->c(2).y() = casted[2][1];
		this->c(2).z() = casted[2][2];
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator+=(const matrix4x4f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->m_column_count >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->m_row_count >= mat.get_row_count(), "out-of-range"
	);

	if (this->m_column_count >= mat.get_column_count())
	{
		if (this->m_row_count >= mat.get_row_count())
		{
			matrix2x2f casted(*this);
			casted += mat;
			this->c(0).x() = casted[0][0];
			this->c(0).y() = casted[0][1];
			this->c(1).x() = casted[1][0];
			this->c(1).y() = casted[1][1];
		}
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == mat.get_column_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	KOTEK_ASSERT(
		this->get_row_count() == mat.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == mat.get_row_count() &&
	    this->get_column_count() == mat.get_column_count())
	{
		matrix4x4f casted(*this);
		casted += mat;

		this->c(0).x() = casted[0][0];
		this->c(0).y() = casted[0][1];
		this->c(0).z() = casted[0][2];
		this->c(0).w() = casted[0][3];

		this->c(1).x() = casted[1][0];
		this->c(1).y() = casted[1][1];
		this->c(1).z() = casted[1][2];
		this->c(1).w() = casted[1][3];

		this->c(2).x() = casted[2][0];
		this->c(2).y() = casted[2][1];
		this->c(2).z() = casted[2][2];
		this->c(2).w() = casted[2][3];

		this->c(3).x() = casted[3][0];
		this->c(3).y() = casted[3][1];
		this->c(3).z() = casted[3][2];
		this->c(3).w() = casted[3][3];
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const vectornf_view_t& view
) noexcept
{
	if (view.get_column_count() > 4 || view.get_row_count() > 4)
	{
		KOTEK_ASSERT(
			false,
			"not yet impl, todo: provide vectornf and matrixnf "
			"impls"
		);
	}
	else
	{
		KOTEK_ASSERT(
			this->get_row_count() >= view.get_row_count(),
			"out-of-range"
		);
		KOTEK_ASSERT(
			this->get_column_count() >= view.get_column_count(),
			"out-of-range"
		);

		if (this->get_row_count() >= view.get_row_count())
		{
			this->c(0) -= view;
		}
	}

	return *this;
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

vectornf_view_t matrixnf_view_t::operator[](math_id_t column_id
) noexcept
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