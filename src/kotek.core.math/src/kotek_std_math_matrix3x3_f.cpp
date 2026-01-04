#include "../include/kotek_std_math_matrix_3x3_f.h"

#include "../include/kotek_std_math_matrix_2x2_f.h"
#include "../include/kotek_std_math_matrix_4x4_f.h"

#include "../include/kotek_std_math_vectornf_view.h"
#include "../include/kotek_std_math_vectornf_const_view.h"
#include "../include/kotek_std_math_matrixnf_view.h"
#include "../include/kotek_std_math_matrixnf_const_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_functions_vector.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

matrix3x3f::matrix3x3f(
	float c0r0,
	float c0r1,
	float c0r2,
	float c1r0,
	float c1r1,
	float c1r2,
	float c2r0,
	float c2r1,
	float c2r2
) : m_base(c0r0, c0r1, c0r2, c1r0, c1r1, c1r2, c2r0, c2r1, c2r2)
{
}
matrix3x3f::matrix3x3f(const base_mat3x3_t& data) : m_base(data)
{
}
matrix3x3f::matrix3x3f(const matrix3x3f& data) :
	m_base(data.m_base)
{
}

matrix3x3f::matrix3x3f(const matrixnf_view_t& view)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	KOTEK_ASSERT(
		view.get_column_count() >= get_column_count(),
		"wrong dimension"
	);

	KOTEK_ASSERT(
		view.get_row_count() >= get_row_count(),
		"wrong dimension"
	);

	if (view.get_column_count() >= get_column_count() &&
	    view.get_row_count() >= get_row_count())
	{
		this->m_base[0] = vector3f(view.c(0)).Get_Base();
		this->m_base[1] = vector3f(view.c(1)).Get_Base();
		this->m_base[2] = vector3f(view.c(2)).Get_Base();
	}
#else
	KOTEK_ASSERT(
		view.get_column_count() == get_column_count(),
		"wrong dimension"
	);

	KOTEK_ASSERT(
		view.get_row_count() == get_row_count(),
		"wrong dimension"
	);

	if (view.get_column_count() == get_column_count() &&
	    view.get_row_count() == get_row_count())
	{
		this->m_base[0] = vector3f(view.c(0)).Get_Base();
		this->m_base[1] = vector3f(view.c(1)).Get_Base();
		this->m_base[2] = vector3f(view.c(2)).Get_Base();
	}
#endif
}

matrix3x3f::matrix3x3f(const matrixnf_const_view_t& view)
{
#ifdef KOTEK_USE_MATH_LIBRARY_IMPLICIT_CASTING
	KOTEK_ASSERT(
		view.get_column_count() >= get_column_count(),
		"wrong dimension"
	);

	KOTEK_ASSERT(
		view.get_row_count() >= get_row_count(),
		"wrong dimension"
	);

	if (view.get_column_count() >= get_column_count() &&
	    view.get_row_count() >= get_row_count())
	{
		this->m_base[0] = vector3f(view.c(0)).Get_Base();
		this->m_base[1] = vector3f(view.c(1)).Get_Base();
		this->m_base[2] = vector3f(view.c(2)).Get_Base();
	}
#else
	KOTEK_ASSERT(
		view.get_column_count() == get_column_count(),
		"wrong dimension"
	);

	KOTEK_ASSERT(
		view.get_row_count() == get_row_count(),
		"wrong dimension"
	);

	if (view.get_column_count() == get_column_count() &&
	    view.get_row_count() == get_row_count())
	{
		this->m_base[0] = vector3f(view.c(0)).Get_Base();
		this->m_base[1] = vector3f(view.c(1)).Get_Base();
		this->m_base[2] = vector3f(view.c(2)).Get_Base();
	}
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
matrix3x3f(const DirectX::XMMATRIX& data)
{
	DirectX::XMStoreFloat3x3(&this->m_base, data);
}
#endif

matrix3x3f::matrix3x3f(void) : m_base{} {}

matrix3x3f::~matrix3x3f(void) = default;

matrix3x3f& matrix3x3f::operator=(const matrix3x3f& data)
{
	this->m_base = data.m_base;
	return *this;
}

matrix3x3f& matrix3x3f::operator=(const base_mat3x3_t& data)
{
	this->m_base = data;
	return *this;
}

matrix3x3f& matrix3x3f::operator=(const matrixnf_view_t& view)
{
	return this->operator=(matrix3x3f(view));
}

matrix3x3f&
matrix3x3f::operator=(const matrixnf_const_view_t& view)
{
	return this->operator=(matrix3x3f(view));
}

matrix3x3f& matrix3x3f::operator+=(const matrix3x3f& data
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._21
		)
	);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._31
		)
	);

	row_original_0 =
		DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 =
		DirectX::XMVectorAdd(row_original_1, row_argument_1);
	row_original_2 =
		DirectX::XMVectorAdd(row_original_2, row_argument_2);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
		row_original_2
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base += data.m_base;
#endif
	return *this;
}

matrix3x3f& matrix3x3f::operator+=(const base_mat3x3_t& data
) noexcept
{
	return this->operator+=(data);
}

matrix3x3f& matrix3x3f::operator+=(const matrixnf_view_t& view
) noexcept
{
	return this->operator+=(matrix3x3f(view));
}

matrix3x3f&
matrix3x3f::operator+=(const matrixnf_const_view_t& view
) noexcept
{
	return this->operator+=(matrix3x3f(view));
}

matrix3x3f& matrix3x3f::operator-=(const matrix3x3f& data
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._21
		)
	);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._31
		)
	);

	row_original_0 = DirectX::XMVectorSubtract(
		row_original_0, row_argument_0
	);
	row_original_1 = DirectX::XMVectorSubtract(
		row_original_1, row_argument_1
	);
	row_original_2 = DirectX::XMVectorSubtract(
		row_original_2, row_argument_2
	);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
		row_original_2
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base -= data.m_base;
#endif
	return *this;
}

matrix3x3f& matrix3x3f::operator-=(const base_mat3x3_t& data
) noexcept
{
	return this->operator-=(data);
}

matrix3x3f& matrix3x3f::operator-=(const matrixnf_view_t& view
) noexcept
{
	return this->operator-=(matrix3x3f(view));
}

matrix3x3f&
matrix3x3f::operator-=(const matrixnf_const_view_t& view
) noexcept
{
	return this->operator-=(matrix3x3f(view));
}

matrix3x3f& matrix3x3f::operator*=(const matrix3x3f& data
) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX m1 = *this;
	DirectX::XMMATRIX m2 = data;

	auto result = DirectX::XMMatrixMultiply(m1, m2);

	DirectX::XMStoreFloat3x3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= data.m_base;
#endif

	return *this;
}

matrix3x3f& matrix3x3f::operator*=(const base_mat3x3_t& data
) noexcept
{
	return this->operator*=(data);
}

matrix3x3f& matrix3x3f::operator*=(const matrixnf_view_t& view
) noexcept
{
	return this->operator*=(matrix3x3f(view));
}

matrix3x3f&
matrix3x3f::operator*=(const matrixnf_const_view_t& view
) noexcept
{
	return this->operator*=(matrix3x3f(view));
}

matrix3x3f& matrix3x3f::operator*=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, value);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, value);
	row_original_2 =
		DirectX::XMVectorScale(row_original_2, value);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
		row_original_2
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base *= value;
#endif

	return *this;
}

#ifdef KOTEK_USE_MATH_USER_MATRIX_DIVISION_IMPLEMENTATION_ENABLED
matrix3x3f& matrix3x3f::operator/=(const matrix3x3f& data
) noexcept
{
	KOTEK_ASSERT(
		false,
		"formally it is undefined function in mathematics, "
		"if it is needed "
		"provide own version of a such operation"
	);
	return *this;
}

matrix3x3f& matrix3x3f::operator/=(const matrixnf_view_t& view
) noexcept
{
	return this->operator/=(matrix3x3f(view));
}

matrix3x3f&
matrix3x3f::operator/=(const matrixnf_const_view_t& view
) noexcept
{
	return this->operator/=(matrix3x3f(view));
}

#endif

matrix3x3f& matrix3x3f::operator/=(float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	float factor = 1.f / value;

	row_original_0 =
		DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 =
		DirectX::XMVectorScale(row_original_1, factor);
	row_original_2 =
		DirectX::XMVectorScale(row_original_2, factor);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
		row_original_0
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
		row_original_1
	);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
		row_original_2
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	this->m_base /= value;
#endif

	return *this;
}

matrix3x3f matrix3x3f::operator+() const noexcept
{
	return *this;
}

matrix3x3f matrix3x3f::operator-() const noexcept
{
	matrix3x3f result;
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	row_original_0 = DirectX::XMVectorNegate(row_original_0);
	row_original_1 = DirectX::XMVectorNegate(row_original_1);
	row_original_2 = DirectX::XMVectorNegate(row_original_2);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.m_base._11
	    ),
		row_original_0
	);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.m_base._21
	    ),
		row_original_1
	);

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.m_base._31
	    ),
		row_original_2
	);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	result = -this->m_base;
#endif
	return result;
}

bool matrix3x3f::operator==(const matrix3x3f& data
) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._21
		)
	);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._31
		)
	);

	bool is_equal_0 =
		DirectX::XMVector3Equal(row_original_0, row_argument_0);
	bool is_equal_1 =
		DirectX::XMVector3Equal(row_original_1, row_argument_1);
	bool is_equal_2 =
		DirectX::XMVector3Equal(row_original_2, row_argument_2);

	return (is_equal_0 && is_equal_1 && is_equal_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base == data.m_base;
#endif
}

bool matrix3x3f::operator!=(const matrix3x3f& data) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._11
		)
	);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._21
		)
	);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&this->m_base._31
		)
	);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._11
		)
	);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._21
		)
	);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
		reinterpret_cast<const DirectX::XMFLOAT3*>(
			&data.m_base._31
		)
	);

	bool is_equal_0 = DirectX::XMVector3NotEqual(
		row_original_0, row_argument_0
	);
	bool is_equal_1 = DirectX::XMVector3NotEqual(
		row_original_1, row_argument_1
	);
	bool is_equal_2 = DirectX::XMVector3NotEqual(
		row_original_2, row_argument_2
	);

	return (is_equal_0 || is_equal_1 || is_equal_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return this->m_base != data.m_base;
#endif
}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
operator DirectX::XMMATRIX(void) const noexcept
{
	return DirectX::XMLoadFloat3x3(&this->m_base);
}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

float matrix3x3f::e(math_id_t column_id, math_id_t row_id)
	const noexcept
{
	return this->c(column_id)[row_id];
}

float&
matrix3x3f::e(math_id_t column_id, math_id_t row_id) noexcept
{
	return this->c(column_id)[row_id];
}

vectornf_view_t matrix3x3f::c(math_id_t column_id) noexcept
{
	if (column_id >= get_column_count())
		column_id = get_column_count() - 1;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vectornf_view_t(
		&this->m_base[column_id][0], get_row_count()
	);
#endif
}

vectornf_const_view_t matrix3x3f::c(math_id_t column_id
) const noexcept
{
	if (column_id >= get_column_count())
		column_id = get_column_count() - 1;

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	#error todo: impl
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return vectornf_const_view_t(
		&this->m_base[column_id][0], get_row_count()
	);
#endif
}

vectornf_view_t
matrix3x3f::operator[](math_id_t column_id) noexcept
{
	return this->c(column_id);
}

vectornf_const_view_t matrix3x3f::operator[](math_id_t column_id
) const noexcept
{
	return this->c(column_id);
}

inline float* matrix3x3f::data(void) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &this->m_base.m[0][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return &this->m_base[0][0];
#else
	#error todo: provide implementation
#endif
}

inline const float* matrix3x3f::data(void) const noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	return &this->m_base.m[0][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return &this->m_base[0][0];
#else
	#error todo: provide implementation
#endif
}

constexpr math_id_t matrix3x3f::size_of(void) const noexcept
{
	static_assert(
		sizeof(float[3][3]) == sizeof(m_base) &&
		"we gurantee that base type is equal to "
		"float[3][3] by size"
	);
	return static_cast<math_id_t>(sizeof(float[3][3]));
}

constexpr math_id_t matrix3x3f::get_column_count(void
) const noexcept
{
	return static_cast<math_id_t>(3);
}

constexpr math_id_t matrix3x3f::get_row_count(void
) const noexcept
{
	return static_cast<math_id_t>(3);
}

matrix3x3f& matrix3x3f::Set_Base(const base_mat3x3_t& data
) noexcept
{
	this->m_base = data;
	return *this;
}

base_mat3x3_t& matrix3x3f::Get_Base(void) noexcept
{
	return this->m_base;
}
const base_mat3x3_t& matrix3x3f::Get_Base(void) const noexcept
{
	return this->m_base;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK