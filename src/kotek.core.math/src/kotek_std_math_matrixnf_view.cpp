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
		KOTEK_ASSERT(
			this->get_row_count() == 2, "expected quad matrix"
		);

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
		KOTEK_ASSERT(
			this->get_row_count() == 3, "expected quad matrix"
		);

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
		KOTEK_ASSERT(
			this->get_row_count() == 4, "expected quad matrix"
		);

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
	default:
	{
		KOTEK_ASSERT(false, "unhanled case");
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
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
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
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
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
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
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
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) += vec;
		}
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
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->get_row_count() >= mat.get_row_count(),
		"out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count())
	{
		if (this->get_row_count() >= mat.get_row_count())
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
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->m_row_count >= mat.get_row_count(), "out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count())
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
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->m_row_count >= mat.get_row_count(), "out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count())
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
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= view.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= view.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= view.get_row_count())
	{
		for (math_id_t i = 0; i < view.get_row_count(); ++i)
		{
			this->c(i) -= view;
		}
	}
#else
	KOTEK_ASSERT(
		this->get_column_count() == view.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting!"
	);

	KOTEK_ASSERT(
		this->get_row_count() == view.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	if (this->get_row_count() == view.get_row_count() &&
	    this->get_column_count() == view.get_row_count())
	{
		for (math_id_t i = 0; i < view.get_row_count(); ++i)
		{
			this->c(i) -= view;
		}
	}

#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrixnf_view_t& view
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
		KOTEK_ASSERT(
			this->get_row_count() == 2, "expected quad matrix"
		);

		matrix2x2f left(*this);
		matrix2x2f right(view);

		left -= right;

		this->c(0).x() = left.e(0, 0);
		this->c(0).y() = left.e(0, 1);

		this->c(1).x() = left.e(1, 0);
		this->c(1).y() = left.e(1, 1);

		break;
	}
	case 3:
	{
		KOTEK_ASSERT(
			this->get_row_count() == 3, "expected quad matrix"
		);

		matrix3x3f left(*this);
		matrix3x3f right(view);

		left -= right;

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
		KOTEK_ASSERT(
			this->get_row_count() == 4, "expected quad matrix"
		);

		matrix4x4f left(*this);
		matrix4x4f right(view);

		left -= right;

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
	default:
	{
		KOTEK_ASSERT(false, "unhanled case");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector1f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) -= vec;
		}
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
			this->c(i) -= vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector2f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) -= vec;
		}
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
			this->c(i) -= vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector3f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) -= vec;
		}
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
			this->c(i) -= vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator-=(const vector4f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= vec.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= vec.get_row_count(),
		"out of range"
	);

	if (this->get_row_count() >= vec.get_row_count())
	{
		for (math_id_t i = 0; i < vec.get_row_count(); ++i)
		{
			this->c(i) -= vec;
		}
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
			this->c(i) -= vec;
		}
	}

#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrix2x2f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->get_row_count() >= mat.get_row_count(),
		"out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count())
	{
		if (this->get_row_count() >= mat.get_row_count())
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
		KOTEK_ASSERT(
			this->get_row_count() == 2,
			"expected quad matrix otherwise provide "
			"implementation and dimension of a such matrix!"
		);

		matrix2x2f casted(*this);
		casted -= mat;

		this->c(0).x() = casted[0][0];
		this->c(0).y() = casted[0][1];

		this->c(1).x() = casted[1][0];
		this->c(1).y() = casted[1][1];
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator-=(const matrix3x3f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->m_row_count >= mat.get_row_count(), "out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count())
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
		KOTEK_ASSERT(
			this->get_row_count() == 3,
			"expected quad matrix otherwise provide "
			"implementation and dimension of a such matrix!"
		);

		matrix3x3f casted(*this);
		casted -= mat;

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
matrixnf_view_t::operator-=(const matrix4x4f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	KOTEK_ASSERT(
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->get_row_count() >= mat.get_row_count(),
		"out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count())
	{
		if (this->get_row_count() >= mat.get_row_count())
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
		KOTEK_ASSERT(
			this->get_row_count() == 4,
			"expected quad matrix otherwise provide "
			"implementation and dimension of a such matrix!"
		);

		matrix4x4f casted(*this);
		casted -= mat;

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
matrixnf_view_t::operator*=(const vectornf_view_t& view
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == view.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	// todo: think about it because our matrix that was a view
	// now becomes a vector due to matrix x vector
	// multiplication
	switch (this->get_column_count())
	{
	case 2:
	{
		KOTEK_ASSERT(
			this->get_row_count() == 2,
			"expected quad matrix otherwise provide "
			"implementation and dimension of a such matrix!"
		);

		matrix2x2f casted(*this);

		const vector2f& result = casted * view;

		this->m_column_count = 1;
		this->m_row_count = 2;

		this->e(0, 0) = result.x();
		this->e(0, 1) = result.y();

		break;
	}
	case 3:
	{
		KOTEK_ASSERT(
			this->get_row_count() == 3,
			"expected quad matrix otherwise provide "
			"implementation and dimension of a such matrix!"
		);

		matrix3x3f casted(*this);

		const vector3f& result = casted * view;

		this->m_column_count = 1;
		this->m_row_count = 3;

		this->e(0, 0) = result.x();
		this->e(0, 1) = result.y();
		this->e(0, 2) = result.z();

		break;
	}
	case 4:
	{
		KOTEK_ASSERT(
			this->get_row_count() == 4,
			"expected quad matrix otherwise provide "
			"implementation and dimension of a such matrix!"
		);

		matrix4x4f casted(*this);

		const vector4f& result = casted * view;

		this->m_column_count = 1;
		this->m_row_count = 4;

		this->e(0, 0) = result.x();
		this->e(0, 1) = result.y();
		this->e(0, 2) = result.z();
		this->e(0, 3) = result.w();

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "unhandled situation");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrixnf_view_t& view
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: is it even can be broadcasted??
#else
	KOTEK_ASSERT(
		this->get_row_count() == view.get_column_count(),
		"strict linear algebra rules"
	);

	if (this->get_row_count() == view.get_column_count())
	{
		switch (this->get_row_count())
		{
		case 2:
		{
			KOTEK_ASSERT(
				this->get_column_count() == 2,
				"expected quad matrix otherwise provide impl "
				"for a such matrix dimension!"
			);

			matrix2x2f left(*this);
			matrix2x2f right(view);

			left *= right;

			this->e(0, 0) = left.e(0, 0);
			this->e(0, 1) = left.e(0, 1);
			this->e(1, 0) = left.e(1, 0);
			this->e(1, 1) = left.e(1, 1);

			break;
		}
		case 3:
		{
			KOTEK_ASSERT(
				this->get_column_count() == 3,
				"expected quad matrix otherwise provide impl "
				"for a such matrix dimension!"
			);

			matrix3x3f left(*this);
			matrix3x3f right(view);

			left *= right;

			this->e(0, 0) = left.e(0, 0);
			this->e(0, 1) = left.e(0, 1);
			this->e(0, 2) = left.e(0, 2);

			this->e(1, 0) = left.e(1, 0);
			this->e(1, 1) = left.e(1, 1);
			this->e(1, 2) = left.e(1, 2);

			this->e(2, 0) = left.e(2, 0);
			this->e(2, 1) = left.e(2, 1);
			this->e(2, 2) = left.e(2, 2);

			break;
		}
		case 4:
		{
			KOTEK_ASSERT(
				this->get_column_count() == 4,
				"expected quad matrix otherwise provide impl "
				"for a such matrix dimension!"
			);

			matrix4x4f left(*this);
			matrix4x4f right(view);

			left *= right;

			this->e(0, 0) = left.e(0, 0);
			this->e(0, 1) = left.e(0, 1);
			this->e(0, 2) = left.e(0, 2);
			this->e(0, 3) = left.e(0, 3);

			this->e(1, 0) = left.e(1, 0);
			this->e(1, 1) = left.e(1, 1);
			this->e(1, 2) = left.e(1, 2);
			this->e(1, 3) = left.e(1, 3);

			this->e(2, 0) = left.e(2, 0);
			this->e(2, 1) = left.e(2, 1);
			this->e(2, 2) = left.e(2, 2);
			this->e(2, 3) = left.e(2, 3);

			break;
		}
		default:
		{
			KOTEK_ASSERT(false, "unhandled situation");
			break;
		}
		}
	}
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector1f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 1:
	{
		this->e(0, 0) *= vec.x();

		this->m_row_count = vec.get_row_count();
		this->m_column_count = 1;

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat1x1");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector2f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 2:
	{
		KOTEK_ASSERT(
			this->get_row_count() == vec.get_row_count(),
			"expected quad 2x2 mat, otherwise provide impl for "
			"different dimension"
		);

		matrix2x2f casted(*this);

		const vector2f& res = casted * vec;

		this->e(0, 0) = res.x();
		this->e(0, 1) = res.y();

		this->m_row_count = vec.get_row_count();
		this->m_column_count = 1;

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat2x2");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector3f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 3:
	{
		KOTEK_ASSERT(
			this->get_row_count() == vec.get_row_count(),
			"expected quad 3x3 mat, otherwise provide impl for "
			"different dimension"
		);

		matrix3x3f casted(*this);

		const vector3f& res = casted * vec;

		this->e(0, 0) = res.x();
		this->e(0, 1) = res.y();
		this->e(0, 2) = res.z();

		this->m_row_count = vec.get_row_count();
		this->m_column_count = 1;

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat1x1");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator*=(const vector4f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == vec.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 4:
	{
		KOTEK_ASSERT(
			this->get_row_count() == vec.get_row_count(),
			"expected quad 4x4 mat, otherwise provide impl for "
			"different dimension"
		);

		matrix4x4f casted(*this);

		const vector4f& res = casted * vec;

		this->e(0, 0) = res.x();
		this->e(0, 1) = res.y();
		this->e(0, 2) = res.z();
		this->e(0, 3) = res.w();

		this->m_row_count = vec.get_row_count();
		this->m_column_count = 1;

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat1x1");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrix2x2f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == mat.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 2:
	{
		KOTEK_ASSERT(
			this->get_row_count() == mat.get_row_count(),
			"expected quad 2x2 matrix, otherwise provide impl "
			"for different dimension"
		);

		matrix2x2f casted(*this);

		casted *= mat;

		this->e(0, 0) = casted.e(0, 0);
		this->e(0, 1) = casted.e(0, 1);

		this->e(1, 0) = casted.e(1, 0);
		this->e(1, 1) = casted.e(1, 1);

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat2x2");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrix3x3f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == mat.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 3:
	{
		KOTEK_ASSERT(
			this->get_row_count() == mat.get_row_count(),
			"expected quad 3x3 matrix, otherwise provide impl "
			"for different dimension"
		);

		matrix3x3f casted(*this);

		casted *= mat;

		this->e(0, 0) = casted.e(0, 0);
		this->e(0, 1) = casted.e(0, 1);
		this->e(0, 2) = casted.e(0, 2);

		this->e(1, 0) = casted.e(1, 0);
		this->e(1, 1) = casted.e(1, 1);
		this->e(1, 2) = casted.e(1, 2);

		this->e(2, 0) = casted.e(2, 0);
		this->e(2, 1) = casted.e(2, 1);
		this->e(2, 2) = casted.e(2, 2);

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat3x3");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator*=(const matrix4x4f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() == mat.get_row_count(),
		"strict linear algebra rule, otherwise enable "
		"broadcasting"
	);

	switch (this->get_column_count())
	{
	case 4:
	{
		KOTEK_ASSERT(
			this->get_row_count() == mat.get_row_count(),
			"expected quad 4x4 matrix, otherwise provide impl "
			"for different dimension"
		);

		matrix4x4f casted(*this);

		casted *= mat;

		this->e(0, 0) = casted.e(0, 0);
		this->e(0, 1) = casted.e(0, 1);
		this->e(0, 2) = casted.e(0, 2);
		this->e(0, 3) = casted.e(0, 3);

		this->e(1, 0) = casted.e(1, 0);
		this->e(1, 1) = casted.e(1, 1);
		this->e(1, 2) = casted.e(1, 2);
		this->e(1, 3) = casted.e(1, 3);

		this->e(2, 0) = casted.e(2, 0);
		this->e(2, 1) = casted.e(2, 1);
		this->e(2, 2) = casted.e(2, 2);
		this->e(2, 3) = casted.e(2, 3);

		this->e(3, 0) = casted.e(3, 0);
		this->e(3, 1) = casted.e(3, 1);
		this->e(3, 2) = casted.e(3, 2);
		this->e(3, 3) = casted.e(3, 3);

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "expected mat3x3");
		break;
	}
	}
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const vectornf_view_t& view
) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrixnf_view_t& view
) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector1f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector2f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector3f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t& matrixnf_view_t::operator/=(const vector4f& vec
) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrix2x2f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrix3x3f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
}

matrixnf_view_t&
matrixnf_view_t::operator/=(const matrix4x4f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
	#error todo: impl
#else
	KOTEK_ASSERT(false, "undefined linear algebra operator");
#endif

	return *this;
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

void matrixnf_view_t::set(
	const vectornf_view_t& view, math_id_t column_id
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		column_id < this->get_column_count(), "out-of-range"
	);

	if (column_id < this->get_column_count())
	{
		KOTEK_ASSERT(
			this->c(column_id).get_row_count() ==
				view.get_row_count(),
			"out-of-range"
		);

		if (this->c(column_id).get_row_count() ==
		    view.get_row_count())
		{
			for (math_id_t i = 0; i < view.get_row_count(); ++i)
			{
				this->c(column_id).e(0, i) = view.e(0, i);
			}
		}
	}
#endif
}

void matrixnf_view_t::set(const matrixnf_view_t& view) noexcept
{
}

void matrixnf_view_t::set(
	const vector1f& vec, math_id_t column_id
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		column_id < this->get_column_count(), "out-of-range"
	);

	if (column_id < this->get_column_count())
	{
		KOTEK_ASSERT(
			this->c(column_id).get_row_count() >=
				vec.get_row_count(),
			"out-of-range"
		);

		if (this->c(column_id).get_row_count() >=
		    vec.get_row_count())
		{
			this->c(column_id).e(0, 0) = vec.e(0, 0);
		}
	}
#endif
}

void matrixnf_view_t::set(
	const vector2f& vec, math_id_t column_id
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		column_id < this->get_column_count(), "out-of-range"
	);

	if (column_id < this->get_column_count())
	{
		KOTEK_ASSERT(
			this->c(column_id).get_row_count() >=
				vec.get_row_count(),
			"out-of-range"
		);

		if (this->c(column_id).get_row_count() >=
		    vec.get_row_count())
		{
			this->c(column_id).e(0, 0) = vec.e(0, 0);
			this->c(column_id).e(0, 1) = vec.e(0, 1);
		}
	}
#endif
}

void matrixnf_view_t::set(
	const vector3f& vec, math_id_t column_id
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		column_id < this->get_column_count(), "out-of-range"
	);

	if (column_id < this->get_column_count())
	{
		KOTEK_ASSERT(
			this->c(column_id).get_row_count() >=
				vec.get_row_count(),
			"out-of-range"
		);

		if (this->c(column_id).get_row_count() >=
		    vec.get_row_count())
		{
			this->c(column_id).e(0, 0) = vec.e(0, 0);
			this->c(column_id).e(0, 1) = vec.e(0, 1);
			this->c(column_id).e(0, 2) = vec.e(0, 2);
		}
	}
#endif
}

void matrixnf_view_t::set(
	const vector4f& vec, math_id_t column_id
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		column_id < this->get_column_count(), "out-of-range"
	);

	if (column_id < this->get_column_count())
	{
		KOTEK_ASSERT(
			this->c(column_id).get_row_count() >=
				vec.get_row_count(),
			"out-of-range"
		);

		if (this->c(column_id).get_row_count() >=
		    vec.get_row_count())
		{
			this->c(column_id).e(0, 0) = vec.e(0, 0);
			this->c(column_id).e(0, 1) = vec.e(0, 1);
			this->c(column_id).e(0, 2) = vec.e(0, 2);
			this->c(column_id).e(0, 3) = vec.e(0, 3);
		}
	}
#endif
}

void matrixnf_view_t::set(const matrix2x2f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);
	KOTEK_ASSERT(
		this->get_row_count() >= mat.get_row_count(),
		"out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count() &&
	    this->get_row_count() >= mat.get_row_count())
	{
		this->e(0, 0) = mat.e(0, 0);
		this->e(0, 1) = mat.e(0, 1);
		this->e(1, 0) = mat.e(1, 0);
		this->e(1, 1) = mat.e(1, 1);
	}
#endif
}

void matrixnf_view_t::set(const matrix3x3f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_row_count() >= mat.get_row_count(),
		"out-of-range"
	);

	if (this->get_row_count() >= mat.get_row_count() &&
	    this->get_column_count() >= mat.get_column_count())
	{
		this->e(0, 0) = mat.e(0, 0);
		this->e(0, 1) = mat.e(0, 1);
		this->e(0, 2) = mat.e(0, 2);

		this->e(1, 0) = mat.e(1, 0);
		this->e(1, 1) = mat.e(1, 1);
		this->e(1, 2) = mat.e(1, 2);

		this->e(2, 0) = mat.e(2, 0);
		this->e(2, 1) = mat.e(2, 1);
		this->e(2, 2) = mat.e(2, 2);
	}
#endif
}

void matrixnf_view_t::set(const matrix4x4f& mat) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_BROADCASTING
	#error todo: impl
#else
	KOTEK_ASSERT(
		this->get_row_count() >= mat.get_row_count(),
		"out-of-range"
	);

	KOTEK_ASSERT(
		this->get_column_count() >= mat.get_column_count(),
		"out-of-range"
	);

	if (this->get_column_count() >= mat.get_column_count() &&
	    this->get_row_count() >= mat.get_row_count())
	{
		this->e(0, 0) = mat.e(0, 0);
		this->e(0, 1) = mat.e(0, 1);
		this->e(0, 2) = mat.e(0, 2);
		this->e(0, 3) = mat.e(0, 3);

		this->e(1, 0) = mat.e(1, 0);
		this->e(1, 1) = mat.e(1, 1);
		this->e(1, 2) = mat.e(1, 2);
		this->e(1, 3) = mat.e(1, 3);

		this->e(2, 0) = mat.e(2, 0);
		this->e(2, 1) = mat.e(2, 1);
		this->e(2, 2) = mat.e(2, 2);
		this->e(2, 3) = mat.e(2, 3);

		this->e(3, 0) = mat.e(3, 0);
		this->e(3, 1) = mat.e(3, 1);
		this->e(3, 2) = mat.e(3, 2);
		this->e(3, 3) = mat.e(3, 3);
	}
#endif
}

math_id_t matrixnf_view_t::size_of(void) const noexcept
{
	return static_cast<math_id_t>(
		sizeof(float) * this->get_row_count() *
		this->get_column_count()
	);
}

float matrixnf_view_t::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->c(column_id).e(0, row_id);
}

float& matrixnf_view_t::e(math_id_t column_id, math_id_t row_id
) noexcept
{
	return this->c(column_id).e(0, row_id);
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